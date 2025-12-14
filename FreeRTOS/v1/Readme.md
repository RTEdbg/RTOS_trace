## FreeRTOS trace v1

This folder contains a version of FreeRTOS trace, that contains support for all FreeRTOS trace macros.

You only need to include the following files in your project:

* `rte_FreeRTOS_trace.c` (copy it to the RTEdbg folder)
* `rte_FreeRTOS_trace.h` (copy it to the RTEdbg/Inc folder)
* `rte_FreeRTOS_trace_fmt.h` (copy it to the RTEdbg/Fmt folder)

For details, see the document **[RTEdbg trace macro integration guide for FreeRTOS](../RTEdbg_trace_macro_integration_guide_FreeRTOS.adoc)**.

**Note:** The files `rte_FreeRTOS_trace2_fmt.h` and `rte_FreeRTOS_trace2.h` in the `Expert` folder are intended for programmers developing FreeRTOS. Therefore, do not include them for normal projects. See the section `section traceENTER / traceRETURN Macro Support` in **[RTOS Trace Customization and Porting](../../RTOS_trace_customization_and_porting.adoc)** for details.