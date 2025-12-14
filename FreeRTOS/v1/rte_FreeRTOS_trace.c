/*
 * Copyright (c) Branko Premzel.
 *
 * SPDX-License-Identifier: MIT
 */

/*******************************************************************************
 * @file    rte_FreeRTOS_trace.c
 * @author  Branko Premzel
 * @brief   Supporting functions for the macros defined in "rte_FreeRTOS_trace.h".
 ******************************************************************************/

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#if ( configUSE_TIMERS == 1 )
#include "timers.h"
#endif

#if configMAX_TASK_NAME_LEN < 4
#error "Task name length must be >= 4"
#endif

/**
 * @brief Convert a 16-bit unsigned integer into a 4-character hexadecimal string.
 * The result is returned as a 32-bit unsigned integer, where the 4 ASCII
 * characters are packed in little-endian order.
 *
 * Example: uint16_to_hex4(0x1234) returns 0x34333231
 *
 * @param value  The 16-bit unsigned integer to convert.
 * @return       A 32-bit little endian value containing 4 ASCII hex characters.
 */

 static inline uint32_t uint16_to_hex4(uint16_t value) {
    // Hex lookup table (0-15 => '0'-'F')
    static const char hex_lut[16] = "0123456789ABCDEF";

    return  hex_lut[(value >> 12U) & 0xFU] |
           (hex_lut[(value >> 8U) & 0xFU] << 8U) |
           (hex_lut[(value >> 4U) & 0xFU] << 16U) |
           (hex_lut[value & 0xFU] << 24U);
}


/**
 * @brief Converts a null-terminated string to a 32-bit unsigned integer.
 *
 * This function takes a string of up to 4 characters and converts it into a
 * 32-bit unsigned integer by interpreting each character as a byte.
 *
 * @param p_name Pointer to a null-terminated string.
 * @return A 32-bit unsigned integer representing the string's byte values.
 */

uint32_t string_to_uint32(const char* p_name)
{
    uint32_t name = 0U;
    uint32_t shift = 0U;
    uint32_t max_chars = 4U;

    if (p_name == NULL)
    {
        return (uint32_t)('N' | ('U' << 8U) | ('L' << 16U) | ('L' << 24U));
    }

    do
    {
        uint32_t name_char = (uint32_t)*p_name;
        p_name++;

        if (name_char == 0U)
        {
            break;
        }

        name |= (name_char << shift);
        shift += 8U;
    }
    while(--max_chars != 0);

    return name;
}


 /**
  * @brief Get task name as a 32-bit value (first 4 chars, little-endian).
  * Packs the first four characters of a task's name into a 32-bit little-endian value.
  *
  * Handles three cases:
  * 1. Returns 'NULL' encoded if @p p_tcb is NULL.
  * 2. Returns the lower 16 bits of the TCB pointer as a placeholder if the name is undefined.
  * 3. Returns the first 4 characters of the task's name, packed as uint32_t (little-endian).
  *
  * @param  p_tcb    Pointer to the Task Control Block (TCB).
  * @return uint32_t The packed 32-bit name or placeholder value.
  */
 uint32_t rtos_get_task_name(void * p_tcb)
 {
     if (p_tcb == NULL)
     {
         return (uint32_t)('N' | ('U' << 8U) | ('L' << 16U) | ('L' << 24U));
     }

     const char* p_name = pcTaskGetName((TaskHandle_t)p_tcb);

     if (p_name == NULL)
     {
         // Pointer is truncated to 16 bits since the return value is 32 bit
         return uint16_to_hex4((uint16_t)((uint32_t)p_tcb & 0xFFFFU));
     }

     return string_to_uint32(p_name);
 }


#if configQUEUE_REGISTRY_SIZE == 0
/**
 * @brief Convert a 16-bit unsigned integer into a 4-character hexadecimal string.
 *        See the description of u16_to_hex4(value).
 *
 * @param value  The 16-bit unsigned integer to convert.
 * @return       A 32-bit little endian value containing 4 ASCII hex characters.
 */

uint32_t get_hex_address(uint32_t value)
{
    return uint16_to_hex4((uint16_t)value);
}

#else //  configQUEUE_REGISTRY_SIZE == 0

/**
 * @brief   Returns the name of the queue (if available).
 * @param   pxQueue     Pointer to the queue.
 * @return  Queue name (first 4 chars) or "????" if pointer to queue is NULL
 *          or hex address (lowest 16 bits) if name is not defined.
 *          Name is packed in little-endian order (first char in LSB).
 */

uint32_t rtos_get_queue_name(void * pxQueue)
{
    if (pxQueue == NULL)
    {
        return 0x3F3F3F3F;      // name = "????"
    }

    const char* p_name = pcQueueGetName((QueueHandle_t)pxQueue);

    if (p_name == NULL)
    {
        // Pointer is truncated to 16 bits since the return value is 32 bit
        return uint16_to_hex4((uint16_t)((uint32_t)pxQueue & 0xFFFFU));
    }

    return string_to_uint32(p_name);
}

#endif  // configQUEUE_REGISTRY_SIZE == 0


#if ( configUSE_TIMERS == 1 )
/**
 * @brief   Returns the name of the timer.
 * @param   tmrTimerControl     Pointer to the timer control struct.
 * @return  Timer name (first 4 chars) or "????" if pointer is NULL
 *          Name is packed in little-endian order (first char in LSB).
 */

uint32_t rtos_get_timer_name(void* p_timer)
{
    const TimerHandle_t xTimer = (const TimerHandle_t)p_timer;

    if (xTimer == NULL)
    {
        return 0x3F3F3F3F;      // name = "????"
    }

    const char* p_name = pcTimerGetName(xTimer);

    return string_to_uint32(p_name);
}
#endif // ( configUSE_TIMERS == 1 )


#if (tskKERNEL_VERSION_MAJOR != (RTE_FREERTOS_VERSION / 10000)) || (tskKERNEL_VERSION_MINOR != ((RTE_FREERTOS_VERSION / 100) % 100))
#error "The kernel version set in FreeRTOSConfig.h and in task.h are not consistent. Correct the version in FreeRTOSConfig.h."
#endif

/*==== End of file ====*/
