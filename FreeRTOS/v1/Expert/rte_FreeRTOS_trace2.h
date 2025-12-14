/*
 * Copyright (c) Branko Premzel.
 *
 * SPDX-License-Identifier: MIT
 */

/*******************************************************************************
 * @file    rte_FreeRTOS_trace2.h
 * @author  Branko Premzel
 * @brief   FreeRTOS-specific traceENTER_/traceRETURN_ macros for RTEdbg tracing.
 *          It must be included at the end of "FreeRTOSConfig.h", after the
 *          #include "rte_FreeRTOS_trace2.h".
 *          This file is generally only required for developers working on
 *          FreeRTOS itself. It is not necessary to include it for routine
 *          testing in FreeRTOS-based projects.
 * @note    Supports FreeRTOS versions starting from v11.0.
 * @note    Assumes little-endian architecture and 8-bit char type.
 ******************************************************************************/

#ifndef RTE_FREERTOS_TRACE2_H
#define RTE_FREERTOS_TRACE2_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "rtedbg.h"
#include "rte_FreeRTOS_trace2_fmt.h"


#ifndef RTE_TRACE_RTOS_IO
#define RTE_TRACE_RTOS_IO   0       // 1 - Enable the traceENTER_/traceEXIT_ macros
#endif

/* Fallback to F_RTOS_TASKS message filter if the filter is not defined. */
#if !defined F_RTOS_TRACE_IO
#define F_RTOS_TRACE_IO  F_RTOS_TASKS
#endif

#if RTE_FREERTOS_VERSION < 110000
#error "FreeRTOS versions older than v11 are not supported."
#endif

#ifndef RTE_FREERTOS_TRACE_H
#error "This file must be included after the rte_FreeRTOS_trace.h"
#endif


/***
 * Macro definitions for the FreeRTOS trace using the RTEdbg toolkit - ENTER/RETURN hooks.
 */

#if RTE_TRACE_RTOS_IO == 1

#define traceENTER_xEventGroupCreateStatic(pxEventGroupBuffer) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CREATE_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxEventGroupBuffer))

#define traceRETURN_xEventGroupCreateStatic(pxEventBits) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CREATE_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxEventBits))

#define traceENTER_xEventGroupCreate() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_CREATE_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xEventGroupCreate(pxEventBits) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CREATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxEventBits))

#define traceENTER_xEventGroupSync(xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait) \
    RTE_MSG4(MSG4_RTOS_EVENT_GROUP_SYNC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxBitsToSet), (uint32_t)(uxBitsToWaitFor), (uint32_t)(xTicksToWait))

#define traceRETURN_xEventGroupSync(uxReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_SYNC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_xEventGroupWaitBits(xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait) \
    RTE_MSG5(MSG5_RTOS_EVENT_GROUP_WAIT_BITS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxBitsToWaitFor), (uint32_t)(xClearOnExit), (uint32_t)(xWaitForAllBits), \
             (uint32_t)(xTicksToWait))

#define traceRETURN_xEventGroupWaitBits(uxReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_WAIT_BITS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_xEventGroupClearBits(xEventGroup, uxBitsToClear) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_CLEAR_BITS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxBitsToClear))

#define traceRETURN_xEventGroupClearBits(uxReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CLEAR_BITS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_xEventGroupClearBitsFromISR(xEventGroup, uxBitsToClear) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_CLEAR_BITS_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xEventGroup), (uint32_t)(uxBitsToClear))

#define traceRETURN_xEventGroupClearBitsFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CLEAR_BITS_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xEventGroupGetBitsFromISR(xEventGroup) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_GET_BITS_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup))

#define traceRETURN_xEventGroupGetBitsFromISR(uxReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_GET_BITS_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_xEventGroupSetBits(xEventGroup, uxBitsToSet) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_SET_BITS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxBitsToSet))

#define traceRETURN_xEventGroupSetBits(uxEventBits) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_SET_BITS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxEventBits))

#define traceENTER_vEventGroupDelete(xEventGroup) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_DELETE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup))

#define traceRETURN_vEventGroupDelete() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_DELETE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xEventGroupGetStaticBuffer(xEventGroup, ppxEventGroupBuffer) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_GET_STATIC_BUFFER_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xEventGroup), (uint32_t)(ppxEventGroupBuffer))

#define traceRETURN_xEventGroupGetStaticBuffer(xReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_GET_STATIC_BUFFER_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xReturn))

#define traceENTER_vEventGroupSetBitsCallback(pvEventGroup, ulBitsToSet) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_SET_BITS_CALLBACK_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pvEventGroup), (uint32_t)(ulBitsToSet))

#define traceRETURN_vEventGroupSetBitsCallback() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_SET_BITS_CALLBACK_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vEventGroupClearBitsCallback(pvEventGroup, ulBitsToClear) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_CLEAR_BITS_CALLBACK_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pvEventGroup), (uint32_t)(ulBitsToClear))

#define traceRETURN_vEventGroupClearBitsCallback() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_CLEAR_BITS_CALLBACK_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xEventGroupSetBitsFromISR(xEventGroup, uxBitsToSet, pxHigherPriorityTaskWoken) \
    RTE_MSG3(MSG3_RTOS_EVENT_GROUP_SET_BITS_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxBitsToSet), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xEventGroupSetBitsFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_SET_BITS_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_uxEventGroupGetNumber(xEventGroup) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_GET_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup))

#define traceRETURN_uxEventGroupGetNumber(xReturn) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_GET_NUMBER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vEventGroupSetNumber(xEventGroup, uxEventGroupNumber) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_SET_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xEventGroup), \
             (uint32_t)(uxEventGroupNumber))

#define traceRETURN_vEventGroupSetNumber() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_SET_NUMBER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskCreateStatic(pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, \
                                     puxStackBuffer, pxTaskBuffer) \
    RTE_MSG7(MSG7_RTOS_TASK_CREATE_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskCode), \
             (uint32_t)(pcName), (uint32_t)(uxStackDepth), (uint32_t)(pvParameters), \
             (uint32_t)(uxPriority), (uint32_t)(puxStackBuffer), (uint32_t)(pxTaskBuffer))

#define traceRETURN_xTaskCreateStatic(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateStaticAffinitySet(pxTaskCode, pcName, uxStackDepth, pvParameters, \
                                                uxPriority, puxStackBuffer, pxTaskBuffer, uxCoreAffinityMask) \
    RTE_MSG8(MSG8_RTOS_TASK_CREATE_STATIC_AFFINITY_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskCode), \
             (uint32_t)(pcName), (uint32_t)(uxStackDepth), \
             (uint32_t)(pvParameters), (uint32_t)(uxPriority), (uint32_t)(puxStackBuffer), \
             (uint32_t)(pxTaskBuffer), (uint32_t)(uxCoreAffinityMask))

#define traceRETURN_xTaskCreateStaticAffinitySet(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_STATIC_AFFINITY_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateRestrictedStatic(pxTaskDefinition, pxCreatedTask) \
    RTE_MSG2(MSG2_RTOS_TASK_CREATE_RESTRICTED_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskDefinition), \
             (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreateRestrictedStatic(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_RESTRICTED_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateRestrictedStaticAffinitySet(pxTaskDefinition, uxCoreAffinityMask, pxCreatedTask) \
    RTE_MSG3(MSG3_RTOS_TASK_CREATE_RESTRICTED_STATIC_AFFINITY_SET_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pxTaskDefinition), (uint32_t)(uxCoreAffinityMask), (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreateRestrictedStaticAffinitySet(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_RESTRICTED_STATIC_AFFINITY_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateRestricted(pxTaskDefinition, pxCreatedTask) \
    RTE_MSG2(MSG2_RTOS_TASK_CREATE_RESTRICTED_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskDefinition), \
             (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreateRestricted(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_RESTRICTED_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateRestrictedAffinitySet(pxTaskDefinition, uxCoreAffinityMask, pxCreatedTask) \
    RTE_MSG3(MSG3_RTOS_TASK_CREATE_RESTRICTED_AFFINITY_SET_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pxTaskDefinition), (uint32_t)(uxCoreAffinityMask), (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreateRestrictedAffinitySet(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_RESTRICTED_AFFINITY_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreate(pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, pxCreatedTask) \
    RTE_MSG6(MSG6_RTOS_TASK_CREATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskCode), \
             (uint32_t)(pcName), (uint32_t)(uxStackDepth), \
             (uint32_t)(pvParameters), (uint32_t)(uxPriority), (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreate(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCreateAffinitySet(pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, \
                                          uxCoreAffinityMask, pxCreatedTask) \
    RTE_MSG7(MSG7_RTOS_TASK_CREATE_AFFINITY_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskCode), \
             (uint32_t)(pcName), (uint32_t)(uxStackDepth), (uint32_t)(pvParameters), \
             (uint32_t)(uxPriority), (uint32_t)(uxCoreAffinityMask), (uint32_t)(pxCreatedTask))

#define traceRETURN_xTaskCreateAffinitySet(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE_AFFINITY_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskDelete(xTaskToDelete) \
    RTE_MSG1(MSG1_RTOS_TASK_DELETE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToDelete))

#define traceRETURN_vTaskDelete() \
    RTE_MSG0(MSG0_RTOS_TASK_DELETE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskDelayUntil(pxPreviousWakeTime, xTimeIncrement) \
    RTE_MSG2(MSG2_RTOS_TASK_DELAY_UNTIL_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxPreviousWakeTime), \
             (uint32_t)(xTimeIncrement))

#define traceRETURN_xTaskDelayUntil(xShouldDelay) \
    RTE_MSG1(MSG1_RTOS_TASK_DELAY_UNTIL_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xShouldDelay))

#define traceENTER_vTaskDelay(xTicksToDelay) \
    RTE_MSG1(MSG1_RTOS_TASK_DELAY_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTicksToDelay))

#define traceRETURN_vTaskDelay() \
    RTE_MSG0(MSG0_RTOS_TASK_DELAY_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_eTaskGetState(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_STATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_eTaskGetState(eReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_STATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(eReturn))

#define traceENTER_uxTaskPriorityGet(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_PRIORITY_GET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskPriorityGet(uxReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_PRIORITY_GET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxTaskPriorityGetFromISR(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_PRIORITY_GET_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskPriorityGetFromISR(uxReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_PRIORITY_GET_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxTaskBasePriorityGet(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_BASE_PRIORITY_GET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskBasePriorityGet(uxReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_BASE_PRIORITY_GET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxTaskBasePriorityGetFromISR(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_BASE_PRIORITY_GET_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskBasePriorityGetFromISR(uxReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_BASE_PRIORITY_GET_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_vTaskPrioritySet(xTask, uxNewPriority) \
    RTE_MSG2(MSG2_RTOS_TASK_PRIORITY_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(uxNewPriority))

#define traceRETURN_vTaskPrioritySet() \
    RTE_MSG0(MSG0_RTOS_TASK_PRIORITY_SET_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskCoreAffinitySet(xTask, uxCoreAffinityMask) \
    RTE_MSG2(MSG2_RTOS_TASK_CORE_AFFINITY_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(uxCoreAffinityMask))

#define traceRETURN_vTaskCoreAffinitySet() \
    RTE_MSG0(MSG0_RTOS_TASK_CORE_AFFINITY_SET_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskCoreAffinityGet(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_CORE_AFFINITY_GET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_vTaskCoreAffinityGet(uxCoreAffinityMask) \
    RTE_MSG1(MSG1_RTOS_TASK_CORE_AFFINITY_GET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxCoreAffinityMask))

#define traceENTER_vTaskPreemptionDisable(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_PREEMPTION_DISABLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_vTaskPreemptionDisable() \
    RTE_MSG0(MSG0_RTOS_TASK_PREEMPTION_DISABLE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskPreemptionEnable(xTask) \
    RTE_MSG1(MSG1_RTOS_TASK_PREEMPTION_ENABLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_vTaskPreemptionEnable() \
    RTE_MSG0(MSG0_RTOS_TASK_PREEMPTION_ENABLE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskSuspend(xTaskToSuspend) \
    RTE_MSG1(MSG1_RTOS_TASK_SUSPEND_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToSuspend))

#define traceRETURN_vTaskSuspend() \
    RTE_MSG0(MSG0_RTOS_TASK_SUSPEND_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskResume(xTaskToResume) \
    RTE_MSG1(MSG1_RTOS_TASK_RESUME_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToResume))

#define traceRETURN_vTaskResume() \
    RTE_MSG0(MSG0_RTOS_TASK_RESUME_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskResumeFromISR(xTaskToResume) \
    RTE_MSG1(MSG1_RTOS_TASK_RESUME_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToResume))

#define traceRETURN_xTaskResumeFromISR(xYieldRequired) \
    RTE_MSG1(MSG1_RTOS_TASK_RESUME_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xYieldRequired))

#define traceENTER_vTaskStartScheduler() \
    RTE_MSG0(MSG0_RTOS_START_SCHEDULER_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskStartScheduler() \
    RTE_MSG0(MSG0_RTOS_START_SCHEDULER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskEndScheduler() \
    RTE_MSG0(MSG0_RTOS_END_SCHEDULER_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskEndScheduler() \
    RTE_MSG0(MSG0_RTOS_END_SCHEDULER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskSuspendAll() \
    RTE_MSG0(MSG0_RTOS_SUSPEND_ALL_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskSuspendAll() \
    RTE_MSG0(MSG0_RTOS_SUSPEND_ALL_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskResumeAll() \
    RTE_MSG0(MSG0_RTOS_RESUME_ALL_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskResumeAll(xAlreadyYielded) \
    RTE_MSG1(MSG1_RTOS_RESUME_ALL_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xAlreadyYielded))

#define traceENTER_xTaskGetTickCount() \
    RTE_MSG0(MSG0_RTOS_GET_TICK_COUNT_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskGetTickCount(xTicks) \
    RTE_MSG1(MSG1_RTOS_GET_TICK_COUNT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xTicks))

#define traceENTER_xTaskGetTickCountFromISR() \
    RTE_MSG0(MSG0_RTOS_GET_TICK_COUNT_FROM_ISR_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskGetTickCountFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_TICK_COUNT_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_uxTaskGetNumberOfTasks() \
    RTE_MSG0(MSG0_RTOS_GET_NUMBER_OF_TASKS_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_uxTaskGetNumberOfTasks(uxCurrentNumberOfTasks) \
    RTE_MSG1(MSG1_RTOS_GET_NUMBER_OF_TASKS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxCurrentNumberOfTasks))

#define traceENTER_pcTaskGetName(xTaskToQuery) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_NAME_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToQuery))

#define traceRETURN_pcTaskGetName(pcTaskName) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_NAME_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pcTaskName))

#define traceENTER_xTaskGetHandle(pcNameToQuery) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_HANDLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pcNameToQuery))

#define traceRETURN_xTaskGetHandle(pxTCB) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_HANDLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxTCB))

#define traceENTER_xTaskGetStaticBuffers(xTask, ppuxStackBuffer, ppxTaskBuffer) \
    RTE_MSG3(MSG3_RTOS_TASK_GET_STATIC_BUFFERS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(ppuxStackBuffer), (uint32_t)(ppxTaskBuffer))

#define traceRETURN_xTaskGetStaticBuffers(xReturn) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_STATIC_BUFFERS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, pulTotalRunTime) \
    RTE_MSG3(MSG3_RTOS_TASK_GET_SYSTEM_STATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTaskStatusArray), \
             (uint32_t)(uxArraySize), (uint32_t)(pulTotalRunTime))

#define traceRETURN_uxTaskGetSystemState(uxTask) \
    RTE_MSG1(MSG1_RTOS_TASK_GET_SYSTEM_STATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxTask))

#if (configNUMBER_OF_CORES == 1)
#ifndef traceENTER_xTaskGetIdleTaskHandle
#define traceENTER_xTaskGetIdleTaskHandle() \
    RTE_MSG0(MSG0_RTOS_GET_IDLE_TASK_HANDLE_ENTER, F_RTOS_TRACE_IO)
#endif
#endif

#if (configNUMBER_OF_CORES == 1)
#ifndef traceRETURN_xTaskGetIdleTaskHandle
#define traceRETURN_xTaskGetIdleTaskHandle(xIdleTaskHandle) \
    RTE_MSG1(MSG1_RTOS_GET_IDLE_TASK_HANDLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xIdleTaskHandle))
#endif
#endif

#define traceENTER_xTaskGetIdleTaskHandleForCore(xCoreID) \
    RTE_MSG1(MSG1_RTOS_GET_IDLE_TASK_HANDLE_FOR_CORE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xCoreID))

#define traceRETURN_xTaskGetIdleTaskHandleForCore(xIdleTaskHandle) \
    RTE_MSG1(MSG1_RTOS_GET_IDLE_TASK_HANDLE_FOR_CORE_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xIdleTaskHandle))

#define traceENTER_vTaskStepTick(xTicksToJump) \
    RTE_MSG1(MSG1_RTOS_STEP_TICK_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTicksToJump))

#define traceRETURN_vTaskStepTick() \
    RTE_MSG0(MSG0_RTOS_STEP_TICK_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskCatchUpTicks(xTicksToCatchUp) \
    RTE_MSG1(MSG1_RTOS_CATCH_UP_TICKS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTicksToCatchUp))

#define traceRETURN_xTaskCatchUpTicks(xYieldOccurred) \
    RTE_MSG1(MSG1_RTOS_CATCH_UP_TICKS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xYieldOccurred))

#define traceENTER_xTaskAbortDelay(xTask) \
    RTE_MSG1(MSG1_RTOS_ABORT_DELAY_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_xTaskAbortDelay(xReturn) \
    RTE_MSG1(MSG1_RTOS_ABORT_DELAY_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskIncrementTick() \
    RTE_MSG0(MSG0_RTOS_INCREMENT_TICK_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskIncrementTick(xSwitchRequired) \
    RTE_MSG1(MSG1_RTOS_INCREMENT_TICK_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xSwitchRequired))

#define traceENTER_vTaskSetApplicationTaskTag(xTask, pxHookFunction) \
    RTE_MSG2(MSG2_RTOS_SET_APPLICATION_TASK_TAG_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(pxHookFunction))

#define traceRETURN_vTaskSetApplicationTaskTag() \
    RTE_MSG0(MSG0_RTOS_SET_APPLICATION_TASK_TAG_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskGetApplicationTaskTag(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_APPLICATION_TASK_TAG_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_xTaskGetApplicationTaskTag(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_APPLICATION_TASK_TAG_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskGetApplicationTaskTagFromISR(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_APPLICATION_TASK_TAG_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_xTaskGetApplicationTaskTagFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_APPLICATION_TASK_TAG_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskCallApplicationTaskHook(xTask, pvParameter) \
    RTE_MSG2(MSG2_RTOS_CALL_APPLICATION_TASK_HOOK_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(pvParameter))

#define traceRETURN_xTaskCallApplicationTaskHook(xReturn) \
    RTE_MSG1(MSG1_RTOS_CALL_APPLICATION_TASK_HOOK_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskSwitchContext() \
    RTE_MSG0(MSG0_RTOS_SWITCH_CONTEXT_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskSwitchContext() \
    RTE_MSG0(MSG0_RTOS_SWITCH_CONTEXT_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskPlaceOnEventList(pxEventList, xTicksToWait) \
    RTE_MSG2(MSG2_RTOS_PLACE_ON_EVENT_LIST_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxEventList), \
             (uint32_t)(xTicksToWait))

#define traceRETURN_vTaskPlaceOnEventList() \
    RTE_MSG0(MSG0_RTOS_PLACE_ON_EVENT_LIST_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskPlaceOnUnorderedEventList(pxEventList, xItemValue, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_PLACE_ON_UNORDERED_EVENT_LIST_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxEventList), \
             (uint32_t)(xItemValue), (uint32_t)(xTicksToWait))

#define traceRETURN_vTaskPlaceOnUnorderedEventList() \
    RTE_MSG0(MSG0_RTOS_PLACE_ON_UNORDERED_EVENT_LIST_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskPlaceOnEventListRestricted(pxEventList, xTicksToWait, xWaitIndefinitely) \
    RTE_MSG3(MSG3_RTOS_PLACE_ON_EVENT_LIST_RESTRICTED_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pxEventList), (uint32_t)(xTicksToWait), (uint32_t)(xWaitIndefinitely))

#define traceRETURN_vTaskPlaceOnEventListRestricted() \
    RTE_MSG0(MSG0_RTOS_PLACE_ON_EVENT_LIST_RESTRICTED_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskRemoveFromEventList(pxEventList) \
    RTE_MSG1(MSG1_RTOS_REMOVE_FROM_EVENT_LIST_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxEventList))

#define traceRETURN_xTaskRemoveFromEventList(xReturn) \
    RTE_MSG1(MSG1_RTOS_REMOVE_FROM_EVENT_LIST_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskRemoveFromUnorderedEventList(pxEventListItem, xItemValue) \
    RTE_MSG2(MSG2_RTOS_REMOVE_FROM_UNORDERED_EVENT_LIST_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pxEventListItem), (uint32_t)(xItemValue))

#define traceRETURN_vTaskRemoveFromUnorderedEventList() \
    RTE_MSG0(MSG0_RTOS_REMOVE_FROM_UNORDERED_EVENT_LIST_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskSetTimeOutState(pxTimeOut) \
    RTE_MSG1(MSG1_RTOS_SET_TIME_OUT_STATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTimeOut))

#define traceRETURN_vTaskSetTimeOutState() \
    RTE_MSG0(MSG0_RTOS_SET_TIME_OUT_STATE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskInternalSetTimeOutState(pxTimeOut) \
    RTE_MSG1(MSG1_RTOS_INTERNAL_SET_TIME_OUT_STATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTimeOut))

#define traceRETURN_vTaskInternalSetTimeOutState() \
    RTE_MSG0(MSG0_RTOS_INTERNAL_SET_TIME_OUT_STATE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskCheckForTimeOut(pxTimeOut, pxTicksToWait) \
    RTE_MSG2(MSG2_RTOS_CHECK_FOR_TIME_OUT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxTimeOut), \
             (uint32_t)(pxTicksToWait))

#define traceRETURN_xTaskCheckForTimeOut(xReturn) \
    RTE_MSG1(MSG1_RTOS_CHECK_FOR_TIME_OUT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskMissedYield() \
    RTE_MSG0(MSG0_RTOS_MISSED_YIELD_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskMissedYield() \
    RTE_MSG0(MSG0_RTOS_MISSED_YIELD_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxTaskGetTaskNumber(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_TASK_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskGetTaskNumber(uxReturn) \
    RTE_MSG1(MSG1_RTOS_GET_TASK_NUMBER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_vTaskSetTaskNumber(xTask, uxHandle) \
    RTE_MSG2(MSG2_RTOS_SET_TASK_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(uxHandle))

#define traceRETURN_vTaskSetTaskNumber() \
    RTE_MSG0(MSG0_RTOS_SET_TASK_NUMBER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_eTaskConfirmSleepModeStatus() \
    RTE_MSG0(MSG0_RTOS_CONFIRM_SLEEP_MODE_STATUS_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_eTaskConfirmSleepModeStatus(eReturn) \
    RTE_MSG1(MSG1_RTOS_CONFIRM_SLEEP_MODE_STATUS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(eReturn))

#define traceENTER_vTaskSetThreadLocalStoragePointer(xTaskToSet, xIndex, pvValue) \
    RTE_MSG3(MSG3_RTOS_SET_THREAD_LOCAL_STORAGE_POINTER_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xTaskToSet), (uint32_t)(xIndex), (uint32_t)(pvValue))

#define traceRETURN_vTaskSetThreadLocalStoragePointer() \
    RTE_MSG0(MSG0_RTOS_SET_THREAD_LOCAL_STORAGE_POINTER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_pvTaskGetThreadLocalStoragePointer(xTaskToQuery, xIndex) \
    RTE_MSG2(MSG2_RTOS_GET_THREAD_LOCAL_STORAGE_POINTER_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xTaskToQuery), (uint32_t)(xIndex))

#define traceRETURN_pvTaskGetThreadLocalStoragePointer(pvReturn) \
    RTE_MSG1(MSG1_RTOS_GET_THREAD_LOCAL_STORAGE_POINTER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pvReturn))

#define traceENTER_vTaskAllocateMPURegions(xTaskToModify, pxRegions) \
    RTE_MSG2(MSG2_RTOS_ALLOCATE_MPU_REGIONS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToModify), \
             (uint32_t)(pxRegions))

#define traceRETURN_vTaskAllocateMPURegions() \
    RTE_MSG0(MSG0_RTOS_ALLOCATE_MPU_REGIONS_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskGetInfo(xTask, pxTaskStatus, xGetFreeStackSpace, eState) \
    RTE_MSG4(MSG4_RTOS_TASK_GET_INFO_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(pxTaskStatus), (uint32_t)(xGetFreeStackSpace), (uint32_t)(eState))

#define traceRETURN_vTaskGetInfo() \
    RTE_MSG0(MSG0_RTOS_TASK_GET_INFO_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxTaskGetStackHighWaterMark2(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_STACK_HIGH_WATER_MARK2_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskGetStackHighWaterMark2(uxReturn) \
    RTE_MSG1(MSG1_RTOS_GET_STACK_HIGH_WATER_MARK2_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxTaskGetStackHighWaterMark(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_STACK_HIGH_WATER_MARK_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_uxTaskGetStackHighWaterMark(uxReturn) \
    RTE_MSG1(MSG1_RTOS_GET_STACK_HIGH_WATER_MARK_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_xTaskGetCurrentTaskHandle() \
    RTE_MSG0(MSG0_RTOS_GET_CURRENT_TASK_HANDLE_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskGetCurrentTaskHandle(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_CURRENT_TASK_HANDLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskGetCurrentTaskHandleForCore(xCoreID) \
    RTE_MSG1(MSG1_RTOS_GET_CURRENT_TASK_HANDLE_FOR_CORE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xCoreID))

#define traceRETURN_xTaskGetCurrentTaskHandleForCore(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_CURRENT_TASK_HANDLE_FOR_CORE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskGetSchedulerState() \
    RTE_MSG0(MSG0_RTOS_GET_SCHEDULER_STATE_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_xTaskGetSchedulerState(xReturn) \
    RTE_MSG1(MSG1_RTOS_GET_SCHEDULER_STATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskPriorityInherit(pxMutexHolder) \
    RTE_MSG1(MSG1_RTOS_PRIORITY_INHERIT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxMutexHolder))

#define traceRETURN_xTaskPriorityInherit(xReturn) \
    RTE_MSG1(MSG1_RTOS_PRIORITY_INHERIT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskPriorityDisinherit(pxMutexHolder) \
    RTE_MSG1(MSG1_RTOS_PRIORITY_DISINHERIT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxMutexHolder))

#define traceRETURN_xTaskPriorityDisinherit(xReturn) \
    RTE_MSG1(MSG1_RTOS_PRIORITY_DISINHERIT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskPriorityDisinheritAfterTimeout(pxMutexHolder, uxHighestPriorityWaitingTask) \
    RTE_MSG2(MSG2_RTOS_PRIORITY_DISINHERIT_AFTER_TIMEOUT_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pxMutexHolder), (uint32_t)(uxHighestPriorityWaitingTask))

#define traceRETURN_vTaskPriorityDisinheritAfterTimeout() \
    RTE_MSG0(MSG0_RTOS_PRIORITY_DISINHERIT_AFTER_TIMEOUT_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskYieldWithinAPI() \
    RTE_MSG0(MSG0_RTOS_YIELD_WITHIN_API_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskYieldWithinAPI() \
    RTE_MSG0(MSG0_RTOS_YIELD_WITHIN_API_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskEnterCritical() \
    RTE_MSG0(MSG0_RTOS_ENTER_CRITICAL_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskEnterCritical() \
    RTE_MSG0(MSG0_RTOS_ENTER_CRITICAL_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskEnterCriticalFromISR() \
    RTE_MSG0(MSG0_RTOS_ENTER_CRITICAL_FROM_ISR_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskEnterCriticalFromISR(uxSavedInterruptStatus) \
    RTE_MSG1(MSG1_RTOS_ENTER_CRITICAL_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(uxSavedInterruptStatus))

#define traceENTER_vTaskExitCritical() \
    RTE_MSG0(MSG0_RTOS_EXIT_CRITICAL_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vTaskExitCritical() \
    RTE_MSG0(MSG0_RTOS_EXIT_CRITICAL_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskExitCriticalFromISR(uxSavedInterruptStatus) \
    RTE_MSG1(MSG1_RTOS_EXIT_CRITICAL_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(uxSavedInterruptStatus))

#define traceRETURN_vTaskExitCriticalFromISR() \
    RTE_MSG0(MSG0_RTOS_EXIT_CRITICAL_FROM_ISR_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskListTasks(pcWriteBuffer, uxBufferLength) \
    RTE_MSG2(MSG2_RTOS_LIST_TASKS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pcWriteBuffer), \
             (uint32_t)(uxBufferLength))

#define traceRETURN_vTaskListTasks() \
    RTE_MSG0(MSG0_RTOS_LIST_TASKS_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vTaskGetRunTimeStatistics(pcWriteBuffer, uxBufferLength) \
    RTE_MSG2(MSG2_RTOS_GET_RUN_TIME_STATISTICS_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(pcWriteBuffer), (uint32_t)(uxBufferLength))

#define traceRETURN_vTaskGetRunTimeStatistics() \
    RTE_MSG0(MSG0_RTOS_GET_RUN_TIME_STATISTICS_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxTaskResetEventItemValue() \
    RTE_MSG0(MSG0_RTOS_RESET_EVENT_ITEM_VALUE_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_uxTaskResetEventItemValue(uxReturn) \
    RTE_MSG1(MSG1_RTOS_RESET_EVENT_ITEM_VALUE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_pvTaskIncrementMutexHeldCount() \
    RTE_MSG0(MSG0_RTOS_INCREMENT_MUTEX_HELD_COUNT_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_pvTaskIncrementMutexHeldCount(pxTCB) \
    RTE_MSG1(MSG1_RTOS_INCREMENT_MUTEX_HELD_COUNT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxTCB))

#define traceENTER_ulTaskGenericNotifyTake(uxIndexToWaitOn, xClearCountOnExit, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_GENERIC_NOTIFY_TAKE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxIndexToWaitOn), \
             (uint32_t)(xClearCountOnExit), (uint32_t)(xTicksToWait))

#define traceRETURN_ulTaskGenericNotifyTake(ulReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_TAKE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulReturn))

#define traceENTER_xTaskGenericNotifyWait(uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, \
                                          pulNotificationValue, xTicksToWait) \
    RTE_MSG5(MSG5_RTOS_GENERIC_NOTIFY_WAIT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxIndexToWaitOn), \
             (uint32_t)(ulBitsToClearOnEntry), (uint32_t)(ulBitsToClearOnExit), \
             (uint32_t)(pulNotificationValue), (uint32_t)(xTicksToWait))

#define traceRETURN_xTaskGenericNotifyWait(xReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_WAIT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskGenericNotify(xTaskToNotify, uxIndexToNotify, ulValue, eAction, \
                                      pulPreviousNotificationValue) \
    RTE_MSG5(MSG5_RTOS_GENERIC_NOTIFY_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToNotify), \
             (uint32_t)(uxIndexToNotify), (uint32_t)(ulValue), (uint32_t)(eAction), \
             (uint32_t)(pulPreviousNotificationValue))

#define traceRETURN_xTaskGenericNotify(xReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTaskGenericNotifyFromISR(xTaskToNotify, uxIndexToNotify, ulValue, eAction, \
                                             pulPreviousNotificationValue, pxHigherPriorityTaskWoken) \
    RTE_MSG6(MSG6_RTOS_GENERIC_NOTIFY_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTaskToNotify), \
             (uint32_t)(uxIndexToNotify), (uint32_t)(ulValue), (uint32_t)(eAction), \
             (uint32_t)(pulPreviousNotificationValue), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xTaskGenericNotifyFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vTaskGenericNotifyGiveFromISR(xTaskToNotify, uxIndexToNotify, pxHigherPriorityTaskWoken) \
    RTE_MSG3(MSG3_RTOS_GENERIC_NOTIFY_GIVE_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xTaskToNotify), (uint32_t)(uxIndexToNotify), \
             (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_vTaskGenericNotifyGiveFromISR() \
    RTE_MSG0(MSG0_RTOS_GENERIC_NOTIFY_GIVE_FROM_ISR_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xTaskGenericNotifyStateClear(xTask, uxIndexToClear) \
    RTE_MSG2(MSG2_RTOS_GENERIC_NOTIFY_STATE_CLEAR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(uxIndexToClear))

#define traceRETURN_xTaskGenericNotifyStateClear(xReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_STATE_CLEAR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_ulTaskGenericNotifyValueClear(xTask, uxIndexToClear, ulBitsToClear) \
    RTE_MSG3(MSG3_RTOS_GENERIC_NOTIFY_VALUE_CLEAR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask), \
             (uint32_t)(uxIndexToClear), (uint32_t)(ulBitsToClear))

#define traceRETURN_ulTaskGenericNotifyValueClear(ulReturn) \
    RTE_MSG1(MSG1_RTOS_GENERIC_NOTIFY_VALUE_CLEAR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulReturn))

#define traceENTER_ulTaskGetRunTimeCounter(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_RUN_TIME_COUNTER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_ulTaskGetRunTimeCounter(ulRunTimeCounter) \
    RTE_MSG1(MSG1_RTOS_GET_RUN_TIME_COUNTER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulRunTimeCounter))

#define traceENTER_ulTaskGetRunTimePercent(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_RUN_TIME_PERCENT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_ulTaskGetRunTimePercent(ulReturn) \
    RTE_MSG1(MSG1_RTOS_GET_RUN_TIME_PERCENT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulReturn))

#define traceENTER_ulTaskGetIdleRunTimeCounter() \
    RTE_MSG0(MSG0_RTOS_GET_IDLE_RUN_TIME_COUNTER_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_ulTaskGetIdleRunTimeCounter(ulReturn) \
    RTE_MSG1(MSG1_RTOS_GET_IDLE_RUN_TIME_COUNTER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulReturn))

#define traceENTER_ulTaskGetIdleRunTimePercent() \
    RTE_MSG0(MSG0_RTOS_GET_IDLE_RUN_TIME_PERCENT_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_ulTaskGetIdleRunTimePercent(ulReturn) \
    RTE_MSG1(MSG1_RTOS_GET_IDLE_RUN_TIME_PERCENT_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ulReturn))

#define traceENTER_xTaskGetMPUSettings(xTask) \
    RTE_MSG1(MSG1_RTOS_GET_MPU_SETTINGS_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTask))

#define traceRETURN_xTaskGetMPUSettings(xMPUSettings) \
    RTE_MSG1(MSG1_RTOS_GET_MPU_SETTINGS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xMPUSettings))

#define traceENTER_xQueueGenericReset(xQueue, xNewQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_GENERIC_RESET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(xNewQueue))

#define traceRETURN_xQueueGenericReset(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_RESET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueGenericCreateStatic(uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType) \
    RTE_MSG5(MSG5_RTOS_QUEUE_GENERIC_CREATE_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxQueueLength), \
             (uint32_t)(uxItemSize), (uint32_t)(pucQueueStorage), (uint32_t)(pxStaticQueue), \
                     (uint32_t)(ucQueueType))

#define traceRETURN_xQueueGenericCreateStatic(pxNewQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_CREATE_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxNewQueue))

#define traceENTER_xQueueGenericGetStaticBuffers(xQueue, ppucQueueStorage, ppxStaticQueue) \
    RTE_MSG3(MSG3_RTOS_QUEUE_GENERIC_GET_STATIC_BUFFERS_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xQueue), (uint32_t)(ppucQueueStorage), (uint32_t)(ppxStaticQueue))

#define traceRETURN_xQueueGenericGetStaticBuffers(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_GET_STATIC_BUFFERS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueGenericCreate(uxQueueLength, uxItemSize, ucQueueType) \
    RTE_MSG3(MSG3_RTOS_QUEUE_GENERIC_CREATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxQueueLength), \
             (uint32_t)(uxItemSize), (uint32_t)(ucQueueType))

#define traceRETURN_xQueueGenericCreate(pxNewQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_CREATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxNewQueue))

#define traceENTER_xQueueCreateMutex(ucQueueType) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_MUTEX_ENTER, F_RTOS_TRACE_IO, (uint32_t)(ucQueueType))

#define traceRETURN_xQueueCreateMutex(xNewQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_MUTEX_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xNewQueue))

#define traceENTER_xQueueCreateMutexStatic(ucQueueType, pxStaticQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_CREATE_MUTEX_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(ucQueueType), \
             (uint32_t)(pxStaticQueue))

#define traceRETURN_xQueueCreateMutexStatic(xNewQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_MUTEX_STATIC_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xNewQueue))

#define traceENTER_xQueueGetMutexHolder(xSemaphore) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_MUTEX_HOLDER_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xSemaphore))

#define traceRETURN_xQueueGetMutexHolder(pxReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_MUTEX_HOLDER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxReturn))

#define traceENTER_xQueueGetMutexHolderFromISR(xSemaphore) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_MUTEX_HOLDER_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xSemaphore))

#define traceRETURN_xQueueGetMutexHolderFromISR(pxReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_MUTEX_HOLDER_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(pxReturn))

#define traceENTER_xQueueGiveMutexRecursive(xMutex) \
    RTE_MSG1(MSG1_RTOS_GIVE_MUTEX_RECURSIVE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xMutex))

#define traceRETURN_xQueueGiveMutexRecursive(xReturn) \
    RTE_MSG1(MSG1_RTOS_GIVE_MUTEX_RECURSIVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueTakeMutexRecursive(xMutex, xTicksToWait) \
    RTE_MSG2(MSG2_RTOS_TAKE_MUTEX_RECURSIVE_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xMutex), (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueTakeMutexRecursive(xReturn) \
    RTE_MSG1(MSG1_RTOS_TAKE_MUTEX_RECURSIVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueCreateCountingSemaphoreStatic(uxMaxCount, uxInitialCount, pxStaticQueue) \
    RTE_MSG3(MSG3_RTOS_QUEUE_CREATE_COUNTING_SEMAPHORE_STATIC_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(uxMaxCount), (uint32_t)(uxInitialCount), (uint32_t)(pxStaticQueue))

#define traceRETURN_xQueueCreateCountingSemaphoreStatic(xHandle) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_COUNTING_SEMAPHORE_STATIC_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xHandle))

#define traceENTER_xQueueCreateCountingSemaphore(uxMaxCount, uxInitialCount) \
    RTE_MSG2(MSG2_RTOS_QUEUE_CREATE_COUNTING_SEMAPHORE_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(uxMaxCount), (uint32_t)(uxInitialCount))

#define traceRETURN_xQueueCreateCountingSemaphore(xHandle) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_COUNTING_SEMAPHORE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xHandle))

#define traceENTER_xQueueGenericSend(xQueue, pvItemToQueue, xTicksToWait, xCopyPosition) \
    RTE_MSG4(MSG4_RTOS_QUEUE_GENERIC_SEND_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvItemToQueue), (uint32_t)(xTicksToWait), (uint32_t)(xCopyPosition))

#define traceRETURN_xQueueGenericSend(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_SEND_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueGenericSendFromISR(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition) \
    RTE_MSG4(MSG4_RTOS_QUEUE_GENERIC_SEND_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvItemToQueue), (uint32_t)(pxHigherPriorityTaskWoken), (uint32_t)(xCopyPosition))

#define traceRETURN_xQueueGenericSendFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GENERIC_SEND_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueGiveFromISR(xQueue, pxHigherPriorityTaskWoken) \
    RTE_MSG2(MSG2_RTOS_QUEUE_GIVE_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xQueueGiveFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GIVE_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueReceive(xQueue, pvBuffer, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_QUEUE_RECEIVE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer), (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueReceive(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_RECEIVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueSemaphoreTake(xQueue, xTicksToWait) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SEMAPHORE_TAKE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueSemaphoreTake(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SEMAPHORE_TAKE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueuePeek(xQueue, pvBuffer, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_QUEUE_PEEK_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer), (uint32_t)(xTicksToWait))

#define traceRETURN_xQueuePeek(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_PEEK_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueReceiveFromISR(xQueue, pvBuffer, pxHigherPriorityTaskWoken) \
    RTE_MSG3(MSG3_RTOS_QUEUE_RECEIVE_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xQueueReceiveFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_RECEIVE_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueuePeekFromISR(xQueue, pvBuffer) \
    RTE_MSG2(MSG2_RTOS_QUEUE_PEEK_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer))

#define traceRETURN_xQueuePeekFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_PEEK_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_uxQueueMessagesWaiting(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_MESSAGES_WAITING_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_uxQueueMessagesWaiting(uxReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_MESSAGES_WAITING_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxQueueSpacesAvailable(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SPACES_AVAILABLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_uxQueueSpacesAvailable(uxReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SPACES_AVAILABLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_uxQueueMessagesWaitingFromISR(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_MESSAGES_WAITING_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xQueue))

#define traceRETURN_uxQueueMessagesWaitingFromISR(uxReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_MESSAGES_WAITING_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxReturn))

#define traceENTER_vQueueDelete(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_DELETE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_vQueueDelete() \
    RTE_MSG0(MSG0_RTOS_QUEUE_DELETE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxQueueGetQueueNumber(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_uxQueueGetQueueNumber(uxQueueNumber) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_NUMBER_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxQueueNumber))

#define traceENTER_vQueueSetQueueNumber(xQueue, uxQueueNumber) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SET_QUEUE_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(uxQueueNumber))

#define traceRETURN_vQueueSetQueueNumber() \
    RTE_MSG0(MSG0_RTOS_QUEUE_SET_QUEUE_NUMBER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_ucQueueGetQueueType(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_TYPE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_ucQueueGetQueueType(ucQueueType) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_TYPE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ucQueueType))

#define traceENTER_uxQueueGetQueueItemSize(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_ITEM_SIZE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_uxQueueGetQueueItemSize(uxItemSize) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_ITEM_SIZE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxItemSize))

#define traceENTER_uxQueueGetQueueLength(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_LENGTH_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_uxQueueGetQueueLength(uxLength) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_QUEUE_LENGTH_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxLength))

#define traceENTER_xQueueIsQueueEmptyFromISR(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_IS_EMPTY_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_xQueueIsQueueEmptyFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_IS_EMPTY_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueIsQueueFullFromISR(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_IS_FULL_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_xQueueIsQueueFullFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_IS_FULL_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueCRSend(xQueue, pvItemToQueue, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_QUEUE_CR_SEND_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvItemToQueue), (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueCRSend(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CR_SEND_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueCRReceive(xQueue, pvBuffer, xTicksToWait) \
    RTE_MSG3(MSG3_RTOS_QUEUE_CR_RECEIVE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer), (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueCRReceive(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CR_RECEIVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueCRSendFromISR(xQueue, pvItemToQueue, xCoRoutinePreviouslyWoken) \
    RTE_MSG3(MSG3_RTOS_QUEUE_CR_SEND_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvItemToQueue), (uint32_t)(xCoRoutinePreviouslyWoken))

#define traceRETURN_xQueueCRSendFromISR(xCoRoutinePreviouslyWoken) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CR_SEND_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xCoRoutinePreviouslyWoken))

#define traceENTER_xQueueCRReceiveFromISR(xQueue, pvBuffer, pxCoRoutineWoken) \
    RTE_MSG3(MSG3_RTOS_QUEUE_CR_RECEIVE_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pvBuffer), (uint32_t)(pxCoRoutineWoken))

#define traceRETURN_xQueueCRReceiveFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CR_RECEIVE_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vQueueAddToRegistry(xQueue, pcQueueName) \
    RTE_MSG2(MSG2_RTOS_QUEUE_ADD_TO_REGISTRY_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue), \
             (uint32_t)(pcQueueName))

#define traceRETURN_vQueueAddToRegistry() \
    RTE_MSG0(MSG0_RTOS_QUEUE_ADD_TO_REGISTRY_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_pcQueueGetName(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_NAME_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_pcQueueGetName(pcReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_GET_NAME_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pcReturn))

#define traceENTER_vQueueUnregisterQueue(xQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_UNREGISTER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueue))

#define traceRETURN_vQueueUnregisterQueue() \
    RTE_MSG0(MSG0_RTOS_QUEUE_UNREGISTER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vQueueWaitForMessageRestricted(xQueue, xTicksToWait, xWaitIndefinitely) \
    RTE_MSG3(MSG3_RTOS_QUEUE_WAIT_FOR_MESSAGE_RESTRICTED_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xQueue), (uint32_t)(xTicksToWait), (uint32_t)(xWaitIndefinitely))

#define traceRETURN_vQueueWaitForMessageRestricted() \
    RTE_MSG0(MSG0_RTOS_QUEUE_WAIT_FOR_MESSAGE_RESTRICTED_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xQueueCreateSet(uxEventQueueLength) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxEventQueueLength))

#define traceRETURN_xQueueCreateSet(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxQueue))

#define traceENTER_xQueueCreateSetStatic(uxEventQueueLength) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_SET_STATIC_ENTER, F_RTOS_TRACE_IO, (uint32_t)(uxEventQueueLength))

#define traceRETURN_xQueueCreateSetStatic(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_SET_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pxQueue))

#define traceENTER_xQueueAddToSet(xQueueOrSemaphore, xQueueSet) \
    RTE_MSG2(MSG2_RTOS_QUEUE_ADD_TO_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueueOrSemaphore), \
             (uint32_t)(xQueueSet))

#define traceRETURN_xQueueAddToSet(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_ADD_TO_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueRemoveFromSet(xQueueOrSemaphore, xQueueSet) \
    RTE_MSG2(MSG2_RTOS_QUEUE_REMOVE_FROM_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueueOrSemaphore), \
             (uint32_t)(xQueueSet))

#define traceRETURN_xQueueRemoveFromSet(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_REMOVE_FROM_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueSelectFromSet(xQueueSet, xTicksToWait) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SELECT_FROM_SET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueueSet), \
             (uint32_t)(xTicksToWait))

#define traceRETURN_xQueueSelectFromSet(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SELECT_FROM_SET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xQueueSelectFromSetFromISR(xQueueSet) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SELECT_FROM_SET_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xQueueSet))

#define traceRETURN_xQueueSelectFromSetFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SELECT_FROM_SET_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xTimerCreateTimerTask() \
    RTE_MSG0(MSG0_RTOS_TIMER_CREATE_TIMER_TASK_ENTER, F_RTOS_TIMER)

#define traceRETURN_xTimerCreateTimerTask(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_CREATE_TIMER_TASK_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_xTimerCreate(pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, pxCallbackFunction) \
    RTE_MSG5(MSG5_RTOS_TIMER_CREATE_ENTER, F_RTOS_TIMER, (uint32_t)(pcTimerName), \
            (uint32_t)(xTimerPeriodInTicks), (uint32_t)(xAutoReload), (uint32_t)(pvTimerID), \
            (uint32_t)(pxCallbackFunction))

#define traceRETURN_xTimerCreate(pxNewTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_CREATE_RETURN, F_RTOS_TIMER, (uint32_t)(pxNewTimer))

#define traceENTER_xTimerCreateStatic(pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, \
                                      pxCallbackFunction, pxTimerBuffer) \
    RTE_MSG6(MSG6_RTOS_TIMER_CREATE_STATIC_ENTER, F_RTOS_TIMER, (uint32_t)(pcTimerName), \
            (uint32_t)(xTimerPeriodInTicks), (uint32_t)(xAutoReload), (uint32_t)(pvTimerID), \
                    (uint32_t)(pxCallbackFunction), (uint32_t)(pxTimerBuffer))

#define traceRETURN_xTimerCreateStatic(pxNewTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_CREATE_STATIC_RETURN, F_RTOS_TIMER, (uint32_t)(pxNewTimer))

#define traceENTER_xTimerGenericCommandFromTask(xTimer, xCommandID, xOptionalValue, \
                                                pxHigherPriorityTaskWoken, xTicksToWait) \
    RTE_MSG5(MSG5_RTOS_TIMER_GENERIC_COMMAND_FROM_TASK_ENTER, F_RTOS_TIMER, \
             (uint32_t)(xTimer), (uint32_t)(xCommandID), (uint32_t)(xOptionalValue), \
             (uint32_t)(pxHigherPriorityTaskWoken), (uint32_t)(xTicksToWait))

#define traceRETURN_xTimerGenericCommandFromTask(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GENERIC_COMMAND_FROM_TASK_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_xTimerGenericCommandFromISR(xTimer, xCommandID, xOptionalValue, \
                                               pxHigherPriorityTaskWoken, xTicksToWait) \
    RTE_MSG5(MSG5_RTOS_TIMER_GENERIC_COMMAND_FROM_ISR_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer), \
             (uint32_t)(xCommandID), (uint32_t)(xOptionalValue), (uint32_t)(pxHigherPriorityTaskWoken), \
             (uint32_t)(xTicksToWait))

#define traceRETURN_xTimerGenericCommandFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GENERIC_COMMAND_FROM_ISR_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_xTimerGetTimerDaemonTaskHandle() \
    RTE_MSG0(MSG0_RTOS_TIMER_GET_DAEMON_TASK_HANDLE_ENTER, F_RTOS_TIMER)

#define traceRETURN_xTimerGetTimerDaemonTaskHandle(xTimerTaskHandle) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_DAEMON_TASK_HANDLE_RETURN, F_RTOS_TIMER, (uint32_t)(xTimerTaskHandle))

#define traceENTER_xTimerGetPeriod(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_PERIOD_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_xTimerGetPeriod(xTimerPeriodInTicks) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_PERIOD_RETURN, F_RTOS_TIMER, (uint32_t)(xTimerPeriodInTicks))

#define traceENTER_vTimerSetReloadMode(xTimer, xAutoReload) \
    RTE_MSG2(MSG2_RTOS_TIMER_SET_RELOAD_MODE_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer), \
             (uint32_t)(xAutoReload))

#define traceRETURN_vTimerSetReloadMode() \
    RTE_MSG0(MSG0_RTOS_TIMER_SET_RELOAD_MODE_RETURN, F_RTOS_TIMER)

#define traceENTER_xTimerGetReloadMode(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_RELOAD_MODE_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_xTimerGetReloadMode(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_RELOAD_MODE_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_uxTimerGetReloadMode(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_UX_GET_RELOAD_MODE_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_uxTimerGetReloadMode(uxReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_UX_GET_RELOAD_MODE_RETURN, F_RTOS_TIMER, (uint32_t)(uxReturn))

#define traceENTER_xTimerGetExpiryTime(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_EXPIRY_TIME_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_xTimerGetExpiryTime(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_EXPIRY_TIME_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_xTimerGetStaticBuffer(xTimer, ppxTimerBuffer) \
    RTE_MSG2(MSG2_RTOS_TIMER_GET_STATIC_BUFFER_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer), \
             (uint32_t)(ppxTimerBuffer))

#define traceRETURN_xTimerGetStaticBuffer(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_STATIC_BUFFER_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_pcTimerGetName(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_NAME_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_pcTimerGetName(pcTimerName) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_NAME_RETURN, F_RTOS_TIMER, (uint32_t)(pcTimerName))

#define traceENTER_xTimerIsTimerActive(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_IS_ACTIVE_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_xTimerIsTimerActive(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_IS_ACTIVE_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_pvTimerGetTimerID(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_TIMER_ID_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_pvTimerGetTimerID(pvReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_TIMER_ID_RETURN, F_RTOS_TIMER, (uint32_t)(pvReturn))

#define traceENTER_vTimerSetTimerID(xTimer, pvNewID) \
    RTE_MSG2(MSG2_RTOS_TIMER_SET_TIMER_ID_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer), \
             (uint32_t)(pvNewID))

#define traceRETURN_vTimerSetTimerID() \
    RTE_MSG0(MSG0_RTOS_TIMER_SET_TIMER_ID_RETURN, F_RTOS_TIMER)

#define traceENTER_xTimerPendFunctionCallFromISR(xFunctionToPend, pvParameter1, ulParameter2, \
                                                 pxHigherPriorityTaskWoken) \
    RTE_MSG4(MSG4_RTOS_TIMER_PEND_FUNCTION_CALL_FROM_ISR_ENTER, F_RTOS_TIMER, (uint32_t)(xFunctionToPend), \
             (uint32_t)(pvParameter1), (uint32_t)(ulParameter2), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xTimerPendFunctionCallFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_PEND_FUNCTION_CALL_FROM_ISR_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_xTimerPendFunctionCall(xFunctionToPend, pvParameter1, ulParameter2, xTicksToWait) \
    RTE_MSG4(MSG4_RTOS_TIMER_PEND_FUNCTION_CALL_ENTER, F_RTOS_TIMER, (uint32_t)(xFunctionToPend), \
             (uint32_t)(pvParameter1), (uint32_t)(ulParameter2), (uint32_t)(xTicksToWait))

#define traceRETURN_xTimerPendFunctionCall(xReturn) \
    RTE_MSG1(MSG1_RTOS_TIMER_PEND_FUNCTION_CALL_RETURN, F_RTOS_TIMER, (uint32_t)(xReturn))

#define traceENTER_uxTimerGetTimerNumber(xTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_TIMER_NUMBER_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer))

#define traceRETURN_uxTimerGetTimerNumber(uxTimerNumber) \
    RTE_MSG1(MSG1_RTOS_TIMER_GET_TIMER_NUMBER_RETURN, F_RTOS_TIMER, (uint32_t)(uxTimerNumber))

#define traceENTER_vTimerSetTimerNumber(xTimer, uxTimerNumber) \
    RTE_MSG2(MSG2_RTOS_TIMER_SET_TIMER_NUMBER_ENTER, F_RTOS_TIMER, (uint32_t)(xTimer), \
             (uint32_t)(uxTimerNumber))

#define traceRETURN_vTimerSetTimerNumber() \
    RTE_MSG0(MSG0_RTOS_TIMER_SET_TIMER_NUMBER_RETURN, F_RTOS_TIMER)

#define traceENTER_xStreamBufferGenericCreate(xBufferSizeBytes, xTriggerLevelBytes, xStreamBufferType, \
                                              pxSendCompletedCallback, pxReceiveCompletedCallback) \
    RTE_MSG5(MSG5_RTOS_STREAM_BUFFER_GENERIC_CREATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xBufferSizeBytes), \
             (uint32_t)(xTriggerLevelBytes), (uint32_t)(xStreamBufferType), \
             (uint32_t)(pxSendCompletedCallback), (uint32_t)(pxReceiveCompletedCallback))

#define traceRETURN_xStreamBufferGenericCreate(pvAllocatedMemory) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GENERIC_CREATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(pvAllocatedMemory))

#define traceENTER_xStreamBufferGenericCreateStatic(xBufferSizeBytes, xTriggerLevelBytes, \
                                                    xStreamBufferType, pucStreamBufferStorageArea, \
                                                    pxStaticStreamBuffer, pxSendCompletedCallback, \
                                                    pxReceiveCompletedCallback) \
    RTE_MSG7(MSG7_RTOS_STREAM_BUFFER_GENERIC_CREATE_STATIC_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xBufferSizeBytes), (uint32_t)(xTriggerLevelBytes), (uint32_t)(xStreamBufferType), \
             (uint32_t)(pucStreamBufferStorageArea), (uint32_t)pxStaticStreamBuffer, \
             (uint32_t)pxSendCompletedCallback, (uint32_t)pxReceiveCompletedCallback)

#define traceRETURN_xStreamBufferGenericCreateStatic(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GENERIC_CREATE_STATIC_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferGetStaticBuffers(xStreamBuffer, ppucStreamBufferStorageArea, \
                                                 ppxStaticStreamBuffer) \
    RTE_MSG3(MSG3_RTOS_STREAM_BUFFER_GET_STATIC_BUFFERS_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer), (uint32_t)(ppucStreamBufferStorageArea), \
             (uint32_t)(ppxStaticStreamBuffer))

#define traceRETURN_xStreamBufferGetStaticBuffers(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_STATIC_BUFFERS_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vStreamBufferDelete(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_DELETE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_vStreamBufferDelete() \
    RTE_MSG0(MSG0_RTOS_STREAM_BUFFER_DELETE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xStreamBufferReset(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferReset(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferResetFromISR(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferResetFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferSetTriggerLevel(xStreamBuffer, xTriggerLevel) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SET_TRIGGER_LEVEL_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer), \
             (uint32_t)(xTriggerLevel))

#define traceRETURN_xStreamBufferSetTriggerLevel(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SET_TRIGGER_LEVEL_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferSpacesAvailable(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SPACES_AVAILABLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferSpacesAvailable(xSpace) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SPACES_AVAILABLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xSpace))

#define traceENTER_xStreamBufferBytesAvailable(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_BYTES_AVAILABLE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferBytesAvailable(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_BYTES_AVAILABLE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferSend(xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait) \
RTE_MSG4(MSG4_RTOS_STREAM_BUFFER_SEND_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer), \
         (uint32_t)(pvTxData), (uint32_t)(xDataLengthBytes), (uint32_t)(xTicksToWait))

#define traceRETURN_xStreamBufferSend(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SEND_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferSendFromISR(xStreamBuffer, pvTxData, xDataLengthBytes, \
                                            pxHigherPriorityTaskWoken) \
    RTE_MSG4(MSG4_RTOS_STREAM_BUFFER_SEND_FROM_ISR_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer), \
             (uint32_t)(pvTxData), (uint32_t)(xDataLengthBytes), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xStreamBufferSendFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SEND_FROM_ISR_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferReceive(xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait) \
    RTE_MSG4(MSG4_RTOS_STREAM_BUFFER_RECEIVE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer), \
             (uint32_t)(pvRxData), (uint32_t)(xBufferLengthBytes), (uint32_t)(xTicksToWait))

#define traceRETURN_xStreamBufferReceive(xReceivedLength) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RECEIVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReceivedLength))

#define traceENTER_xStreamBufferNextMessageLengthBytes(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_NEXT_MESSAGE_LENGTH_BYTES_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferNextMessageLengthBytes(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_NEXT_MESSAGE_LENGTH_BYTES_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xReturn))

#define traceENTER_xStreamBufferReceiveFromISR(xStreamBuffer, pvRxData, xBufferLengthBytes, \
                                               pxHigherPriorityTaskWoken) \
    RTE_MSG4(MSG4_RTOS_STREAM_BUFFER_RECEIVE_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer), (uint32_t)(pvRxData), (uint32_t)(xBufferLengthBytes), \
             (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xStreamBufferReceiveFromISR(xReceivedLength) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RECEIVE_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xReceivedLength))

#define traceENTER_xStreamBufferIsEmpty(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_IS_EMPTY_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferIsEmpty(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_IS_EMPTY_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferIsFull(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_IS_FULL_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_xStreamBufferIsFull(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_IS_FULL_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_xStreamBufferSendCompletedFromISR(xStreamBuffer, pxHigherPriorityTaskWoken) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SEND_COMPLETED_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xStreamBufferSendCompletedFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SEND_COMPLETED_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xReturn))

#define traceENTER_xStreamBufferReceiveCompletedFromISR(xStreamBuffer, pxHigherPriorityTaskWoken) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_RECEIVE_COMPLETED_FROM_ISR_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer), (uint32_t)(pxHigherPriorityTaskWoken))

#define traceRETURN_xStreamBufferReceiveCompletedFromISR(xReturn) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RECEIVE_COMPLETED_FROM_ISR_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(xReturn))

#define traceENTER_uxStreamBufferGetStreamBufferNotificationIndex(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_NOTIFICATION_INDEX_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer))

#define traceRETURN_uxStreamBufferGetStreamBufferNotificationIndex(uxNotificationIndex) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_NOTIFICATION_INDEX_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(uxNotificationIndex))

#define traceENTER_vStreamBufferSetStreamBufferNotificationIndex(xStreamBuffer, uxNotificationIndex) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SET_NOTIFICATION_INDEX_ENTER, F_RTOS_TRACE_IO, \
             (uint32_t)(xStreamBuffer), (uint32_t)(uxNotificationIndex))

#define traceRETURN_vStreamBufferSetStreamBufferNotificationIndex() \
    RTE_MSG0(MSG0_RTOS_STREAM_BUFFER_SET_NOTIFICATION_INDEX_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxStreamBufferGetStreamBufferNumber(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_uxStreamBufferGetStreamBufferNumber(uxStreamBufferNumber) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_NUMBER_RETURN, F_RTOS_TRACE_IO, \
             (uint32_t)(uxStreamBufferNumber))

#define traceENTER_vStreamBufferSetStreamBufferNumber(xStreamBuffer, uxStreamBufferNumber) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SET_NUMBER_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer), \
             (uint32_t)(uxStreamBufferNumber))

#define traceRETURN_vStreamBufferSetStreamBufferNumber() \
    RTE_MSG0(MSG0_RTOS_STREAM_BUFFER_SET_NUMBER_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_ucStreamBufferGetStreamBufferType(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_TYPE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xStreamBuffer))

#define traceRETURN_ucStreamBufferGetStreamBufferType(ucStreamBufferType) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_GET_TYPE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(ucStreamBufferType))

#define traceENTER_vListInitialise(pxList) \
    RTE_MSG1(MSG1_RTOS_LIST_INITIALISE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxList))

#define traceRETURN_vListInitialise() \
    RTE_MSG0(MSG0_RTOS_LIST_INITIALISE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vListInitialiseItem(pxItem) \
    RTE_MSG1(MSG1_RTOS_LIST_INITIALISE_ITEM_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxItem))

#define traceRETURN_vListInitialiseItem() \
    RTE_MSG0(MSG0_RTOS_LIST_INITIALISE_ITEM_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vListInsertEnd(pxList, pxNewListItem) \
    RTE_MSG2(MSG2_RTOS_LIST_INSERT_END_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxList), (uint32_t)(pxNewListItem))

#define traceRETURN_vListInsertEnd() \
    RTE_MSG0(MSG0_RTOS_LIST_INSERT_END_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vListInsert(pxList, pxNewListItem) \
    RTE_MSG2(MSG2_RTOS_LIST_INSERT_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxList), (uint32_t)(pxNewListItem))

#define traceRETURN_vListInsert() \
    RTE_MSG0(MSG0_RTOS_LIST_INSERT_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_uxListRemove(pxItemToRemove) \
    RTE_MSG1(MSG1_RTOS_LIST_REMOVE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxItemToRemove))

#define traceRETURN_uxListRemove(uxNumberOfItems) \
    RTE_MSG1(MSG1_RTOS_LIST_REMOVE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(uxNumberOfItems))

#define traceENTER_xCoRoutineCreate(pxCoRoutineCode, uxPriority, uxIndex) \
    RTE_MSG3(MSG3_RTOS_CO_ROUTINE_CREATE_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxCoRoutineCode), \
             (uint32_t)(uxPriority), (uint32_t)(uxIndex))

#define traceRETURN_xCoRoutineCreate(xReturn) \
    RTE_MSG1(MSG1_RTOS_CO_ROUTINE_CREATE_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#define traceENTER_vCoRoutineAddToDelayedList(xTicksToDelay, pxEventList) \
    RTE_MSG2(MSG2_RTOS_CO_ROUTINE_ADD_TO_DELAYED_LIST_ENTER, F_RTOS_TRACE_IO, (uint32_t)(xTicksToDelay), \
             (uint32_t)(pxEventList))

#define traceRETURN_vCoRoutineAddToDelayedList() \
    RTE_MSG0(MSG0_RTOS_CO_ROUTINE_ADD_TO_DELAYED_LIST_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_vCoRoutineSchedule() \
    RTE_MSG0(MSG0_RTOS_CO_ROUTINE_SCHEDULE_ENTER, F_RTOS_TRACE_IO)

#define traceRETURN_vCoRoutineSchedule() \
    RTE_MSG0(MSG0_RTOS_CO_ROUTINE_SCHEDULE_RETURN, F_RTOS_TRACE_IO)

#define traceENTER_xCoRoutineRemoveFromEventList(pxEventList) \
    RTE_MSG1(MSG1_RTOS_CO_ROUTINE_REMOVE_FROM_EVENT_LIST_ENTER, F_RTOS_TRACE_IO, (uint32_t)(pxEventList))

#define traceRETURN_xCoRoutineRemoveFromEventList(xReturn) \
    RTE_MSG1(MSG1_RTOS_CO_ROUTINE_REMOVE_FROM_EVENT_LIST_RETURN, F_RTOS_TRACE_IO, (uint32_t)(xReturn))

#endif // RTE_TRACE_RTOS_IO == 1

#ifdef __cplusplus
}
#endif

#endif  // RTE_FREERTOS_TRACE2_H

/*==== End of file ====*/
