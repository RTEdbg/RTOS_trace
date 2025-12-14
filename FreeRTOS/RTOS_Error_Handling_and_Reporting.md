# RTOS Error Handling and Reporting

This document presents a non-intrusive method for logging essential debugging information, specifically the identity of the function that invokes the RTOS error handler. It also demonstrates how to implement logging within FreeRTOS Trace Hook functions, specifically for reporting errors in critical scenarios such as stack overflow and allocation failures (e.g., malloc failure).

The description assumes familiarity with the basics of the **[RTEdbg toolkit](https://github.com/RTEdbg/RTEdbg)**.

## FreeRTOS Error Logging Example

Standard tracing in Real-Time Operating Systems (RTOS) typically focuses on normal operations, often providing poor or zero support for tracing special conditions or RTOS fatal errors. A dedicated tracing mechanism is therefore required for such critical errors. Using FreeRTOS as an example, we demonstrate how to include the logging of specific values that enable more precise localization of the cause of a kernel crash.

Different RTOS handle and report errors that can occur during kernel execution in various ways. With FreeRTOS, the `configASSERT` macro is provided for this purpose. `FreeRTOS.h` header file holds the default version - see the definition:
```
#ifndef configASSERT
	#define configASSERT( x )
	#define configASSERT_DEFINED 0
#else
	#define configASSERT_DEFINED 1
#endif
```
The default version does nothing, and because of this, the typical version is used as found in many `FreeRTOSConfig.h` files (it disables interrupts and then enters an infinite loop):
```
#define configASSERT( x ) if( ( x ) == pdFALSE ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
```
In this example, code execution halts without any error reporting. Only if we have debugger access to the embedded system is it possible to determine which part of the RTOS kernel the processor is stuck in an infinite loop. 

Code instrumentation with the **RTEdbg library** allows the data logging structure to be transmitted over any arbitrary interface or IoT connection to the host, where binary log data is decoded. It is then not necessary to guess the cause of the error since we have the info in which part of the kernel the `configASSERT()` was triggered. Below is an example (macro, function, and printf-style format ID definition) of how to solve the logging of the address from which the error logging function was called.

### configASSERT macro example
This macro calls the `Kernel_error()` function to log information about an error detected within the FreeRTOS kernel. Add this macro to your `FreeRTOSConfig.h` file or replace the existing one. Add the `Kernel_error()` function also.
```
#define configASSERT(x) if((x) == pdFALSE) { Kernel_error(); }
```

### Fatal error logging function example
```C
/**
  * @brief  This function is executed in case of internal kernel error.
  * @retval None
  */
void __attribute__((noinline)) __attribute__((__noreturn__)) Kernel_error(void)
{
    // Log the location from which this function has been called
    uint32_t link_reg = __get_LR();
        // Get the address of the function from which the `Error_handler()` was called.
        // Replace the __get_LR() function with another one compatible with your device and compiler if necessary
    RTE_MSG1(MSG1_KERNEL_ERROR, F_SYSTEM, link_reg - 5U)
    shutdown_the_system();      // Or endless loop in the early project design phase
}
```
The `configASSERT` macro is used extensively throughout FreeRTOS to check for the presence of fatal errors. This means that the function `Kernel_error()` will be called from many different locations (over 200 in the present FreeRTOS version). In order to distinguish which part of the kernel initiated the call, this function logs the value of the Program Counter (PC) as it was when the function was invoked.

For some processors, the return address is saved on the stack, while on ARM Cortex, it is saved in the LR (Link Register), and on RISC-V, it is saved in the **ra** (return address) register, and so on.In the example above, the `__get_LR()` function is used, which is suitable for processors with ARM Cortex M cores. Few other options are provided below. However, there is no standard method that would be suitable for all processor types and compilers.

**Format code for the RTE_MSG1() macro:**
```
// MSG1_KERNEL_ERROR "Kernel_error() called from address 0x%08X"
* And optionally put the same info to the RTOS_ERRORS file also. */
// >RTOS_ERRORS "%N %t Kernel_error() called from address 0x%08X\n"
```
**Example:** In the case where the `Main.log` file contains a record for the format code `MSG1_KERNEL_ERROR` and the address printed is 0x24002962. You have to look into the assembly list file (for GCC this is ProjectName.list) and search for this address. Using this information we then determine the name of the function in which the error was detected—in our case, that is `prvDeleteTCB()` in the example shown.

```
24002950 <prvDeleteTCB>:
    {
24002950:	b510      	push	{r4, lr}
24002952:	4604      	mov	r4, r0
            if( pxTCB->ucStaticallyAllocated == tskDYNAMICALLY_ALLOCATED_STACK_AND_TCB )
24002954:	f890 305d 	ldrb.w	r3, [r0, #93]	@ 0x5d
24002958:	b133      	cbz	r3, 24002968 <prvDeleteTCB+0x18>
            else if( pxTCB->ucStaticallyAllocated == tskSTATICALLY_ALLOCATED_STACK_ONLY )
2400295a:	2b01      	cmp	r3, #1
2400295c:	d00b      	beq.n	24002976 <prvDeleteTCB+0x26>
                configASSERT( pxTCB->ucStaticallyAllocated == tskSTATICALLY_ALLOCATED_STACK_AND_TCB );
2400295e:	2b02      	cmp	r3, #2
24002960:	d008      	beq.n	24002974 <prvDeleteTCB+0x24>
24002962:	f002 fc29 	bl	240051b8 <Kernel_error>
    }
24002966:	e005      	b.n	24002974 <prvDeleteTCB+0x24>
```

## Accessing the Link Register (LR) with Different Compilers for ARM Cortex M

Link register holds the return address. The observation that the `__get_LR()` function is **not universally available** across all listed toolchains (GCC, ARM v6/armcc, IAR) is correct. This is because it is a **compiler-specific intrinsic function** or a **vendor-provided utility**, not part of the standard C language.

For projects that must support all three compilers, the best practice is to use conditional compilation to select the correct approach based on the predefined compiler macros:
```c
#include <stdint.h>
/**
 @brief   Get Link Register
 @details Returns the current value of the Link Register (LR).
 @return  LR register value
*/
#if defined ( __ICCARM__ )
// __get_LR() is EWARM intrinsic function
#elif defined ( __CC_ARM )
register uint32_t __reglr  __ASM("lr");
__STATIC_INLINE uint32_t __get_LR(void)
{
    return(__reglr);
}
#elif defined ( __GNUC__ )
__STATIC_FORCEINLINE uint32_t __get_LR (void)
{
    register uint32_t result;
    __ASM volatile ("MOV %0, LR\n" : "=r" (result) );
    return(result);
}
#else  /* if defined( __ICCARM__ ) */
#error "Unknown compiler"
#endif /* if defined( __ICCARM__ ) */
```
For projects where you will use only one compiler, include only the corresponding part of the code above.

### Key Constraint (Why __get_LR() is non-standard)

Regardless of the method used, keep in mind that the value in the `LR` register is only meaningful if the register is read **immediately** upon function entry - before the current function calls another function.

**Note:** The function `__builtin_return_address(0)` does not have this problem but is not supported by many embedded system compilers.


## Compiler Built-in Function Alternative

GCC provides the non-standard **`__builtin_return_address(0)`** function. This is the closest equivalent to a standardized macro for this purpose. Such an implementation is also suitable for other processor families, e.g., RISC-V and not only for ARM-Cortex M. It is supported by some other embedded system compilers and not only the GCC.

```c
#include <stdint.h>

uint32_t get_lr(void)
{
    // 0 retrieves the return address of the current function.
    return (uint32_t)__builtin_return_address(0);
}
```

## Other Possibilities to Detect an Log FreeRTOS Errors

Programmer can implement **Error Hook Functions** and add error logging to them:

1. **vApplicationStackOverflowHook()** <br>
   The kernel calls it automatically when it detects a Stack Overflow for a task. This is a crucial mechanism for preventing undefined system behavior. <br>
   See also: **[FreeRTOS stack usage and stack overflow checking](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/09-Memory-management/02-Stack-usage-and-stack-overflow-checking)**

2. **vApplicationMallocFailedHook()** <br>
   Called when the memory allocation function (heap management) (e.g., `pvPortMalloc()` fails to allocate the requested memory. It is used to handle dynamic memory allocation errors. <br>
   See also: **[Hook Functions](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/12-Hook-functions)**

The **[FreeRTOS Trace Demo](https://github.com/RTEdbg/FreeRTOS-trace-demo)** contains sample code for the `vApplicationStackOverflowHook()` and `vApplicationMallocFailedHook()` functions. The code implements logging of diagnostic information using the functionality provided by the RTEdbg library.

-------
<br>

## Additional Documentation

1. **[RTEdbg Trace Macro Integration Guide for FreeRTOS](RTEdbg_trace_macro_integration_guide_FreeRTOS.adoc)**
2. **[FreeRTOS Trace Demo](https://github.com/RTEdbg/FreeRTOS-trace-demo)**
3. **[List of Exception Handler Demo Code](https://github.com/RTEdbg/RTEdbgDemo/blob/master/STM32H743/RTEdbg/Demo_code/Fault_handler.md)**.
