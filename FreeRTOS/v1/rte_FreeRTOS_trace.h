/*
 * Copyright (c) Branko Premzel.
 *
 * SPDX-License-Identifier: MIT
 */

/*******************************************************************************
 * @file    rte_FreeRTOS_trace.h
 * @author  Branko Premzel
 * @brief   FreeRTOS-specific trace macros for RTEdbg tracing library.
 *          It must be included at the end of FreeRTOSConfig.h.
 * @note    Supports FreeRTOS versions from v9.0 up to at least v11.2.
 * @note    Assumes little-endian architecture and 8-bit char type.
 ******************************************************************************/

#ifndef RTE_FREERTOS_TRACE_H
#define RTE_FREERTOS_TRACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "rtedbg.h"
#include "rte_FreeRTOS_trace_fmt.h"     // Formatting definitions for the RTEdbg trace macros


/***
 * Enable/disable individual FreeRTOS trace groups.
 * Put the definitions in the configuration file rtedbg_config.h.
 * The default values are set below.
 *
 * By setting individual values to 0, groups of trace macros can be excluded 
 * from compilation. Place macros, such as #define RTE_TRACE_RTOS_MALLOC,
 * in the FreeRTOSConfig.h file — before the #include of this file.
 *
 * To free up filter numbers, you can also disable the corresponding filter
 * definitions in "rte_FreeRTOS_trace_fmt.h".
 */

#ifndef RTE_TRACE_RTOS_BASIC
#define RTE_TRACE_RTOS_BASIC     1      // Most important task, queue and notification trace macros
#endif
#ifndef RTE_TRACE_RTOS_TASKS
#define RTE_TRACE_RTOS_TASKS     0      // Task related events, including notifications
#endif
#ifndef RTE_TRACE_RTOS_MALLOC
#define RTE_TRACE_RTOS_MALLOC    0      // Malloc and free
#endif
#ifndef RTE_TRACE_RTOS_TIMER
#define RTE_TRACE_RTOS_TIMER     0      // Timer related events
#endif
#ifndef RTE_TRACE_RTOS_QUEUE
#define RTE_TRACE_RTOS_QUEUE     0      // Queue, semaphore, and mutex related events
#endif
#ifndef RTE_TRACE_RTOS_STREAMS
#define RTE_TRACE_RTOS_STREAMS   0      // Stream related events
#endif
#ifndef RTE_TRACE_RTOS_EXPERT
#define RTE_TRACE_RTOS_EXPERT    0      // Less important FreeRTOS events (for expert users)
#endif

/* Fallback to F_RTOS_TASKS message filter if a particular filter is not defined. */
#if !defined F_RTOS_MALLOC
#define F_RTOS_MALLOC  F_RTOS_BASIC
#endif

#if !defined F_RTOS_TIMER
#define F_RTOS_TIMER  F_RTOS_TASKS
#endif

#if !defined F_RTOS_QUEUE
#define F_RTOS_QUEUE  F_RTOS_TASKS 
#endif

#if !defined F_RTOS_STREAMS
#define F_RTOS_STREAMS  F_RTOS_TASKS 
#endif

#if !defined F_RTOS_EXPERT
#define F_RTOS_EXPERT   F_RTOS_TASKS
#endif


/* The FreeRTOS version has to be defined in the FreeRTOSConfig.h.
 * We can't use the tskKERNEL_VERSION_MAJOR and tskKERNEL_VERSION_MINOR values because
 * they're defined in task.h. This file can only be included after FreeRTOS.h, which is
 * a problem because FreeRTOSConfig.h (where we need them) is included inside FreeRTOS.h.
 */
#if !defined RTE_FREERTOS_VERSION
#error "Define RTE_FREERTOS_VERSION in rtedbg_config.h (e.g., 100403 for v10.04.03)"
#endif

#if RTE_FREERTOS_VERSION < 90000
#error "Trace for FreeRTOS version < v9.00.00 is not supported."
#endif

#if configQUEUE_REGISTRY_SIZE < 1
#define RTE_GET_QUEUE_NAME(x) get_hex_address((uint32_t)(x))
uint32_t get_hex_address(uint32_t value);
#else
#define RTE_GET_QUEUE_NAME(x) rtos_get_queue_name(x)
uint32_t rtos_get_queue_name(void * pxQueue);
#endif  // configQUEUE_REGISTRY_SIZE < 1

#if ( configUSE_TIMERS == 1 )
// (void *) is used to avoid the need to include various FreeRTOS headers in this file.
uint32_t rtos_get_timer_name(void * p_timer);
#endif

uint32_t string_to_uint32(const char* p_name);
uint32_t rtos_get_task_name(void * p_tcb);


/***
 * Macro definitions for the FreeRTOS trace using the RTEdbg toolkit.
 */

#if RTE_TRACE_RTOS_BASIC == 1
/* Called after a task has been selected to run.  pxCurrentTCB holds a pointer
 * to the task control block of the selected task. */
#define traceTASK_SWITCHED_IN() \
    RTE_MSG1(MSG1_RTOS_TASK_SWITCHED_IN, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB))
#endif  // RTE_TRACE_RTOS_BASIC == 1

#if RTE_TRACE_RTOS_EXPERT == 1
/* Called after all idle tasks and timer task (if enabled) have been created
 * successfully, just before the scheduler is started. */
#define traceSTARTING_SCHEDULER(xIdleTaskHandles) \
    RTE_MSG0(MSG0_RTOS_STARTING_SCHEDULER, F_RTOS_EXPERT)
#endif // RTE_TRACE_RTOS_EXPERT == 1


#if RTE_TRACE_RTOS_TASKS == 1
/* Called before stepping the tick count after waking from tickless idle sleep.  x = ticks to jump */
#define traceINCREASE_TICK_COUNT(x) \
    RTE_MSG1(MSG1_RTOS_INCREASE_TICK_COUNT, F_RTOS_TASKS, (uint32_t)(x))
	
/* Called immediately before entering tickless idle. */
#define traceLOW_POWER_IDLE_BEGIN() \
    RTE_MSG0(MSG0_RTOS_LOW_POWER_IDLE_BEGIN, F_RTOS_TASKS)

/* Called when returning to the Idle task after a tickless idle. */
#define traceLOW_POWER_IDLE_END() \
    RTE_MSG0(MSG0_RTOS_LOW_POWER_IDLE_END, F_RTOS_TASKS)
#endif  // RTE_TRACE_RTOS_TASKS == 1


#if RTE_TRACE_RTOS_EXPERT == 1
/* Called before a task has been selected to run.  pxCurrentTCB holds a pointer
 * to the task control block of the task being switched out.
 *
 * Note: The format directive for traceTASK_SWITCHED_IN remembers which task was
 * executed before, so it is not necessary to record the name of the executed task
 * with this macro.
 */
#define traceTASK_SWITCHED_OUT() \
    RTE_MSG1(MSG1_RTOS_TASK_SWITCHED_OUT, F_RTOS_EXPERT , rtos_get_task_name(pxCurrentTCB))
#endif // RTE_TRACE_RTOS_EXPERT == 1


#if RTE_TRACE_RTOS_TASKS == 1
/* Called when a task attempts to take a mutex that is already held by a
 * lower priority task.  pxTCBOfMutexHolder is a pointer to the TCB of the task
 * that holds the mutex.  uxInheritedPriority is the priority the mutex holder
 * will inherit (the priority of the task that is attempting to obtain the
 * muted. */
#define traceTASK_PRIORITY_INHERIT(pxTCBOfMutexHolder, uxInheritedPriority) \
    RTE_MSG2(MSG2_RTOS_TASK_PRIORITY_INHERIT, F_RTOS_TASKS, rtos_get_task_name(pxTCBOfMutexHolder), \
            (uint32_t)(uxInheritedPriority))

/* Called when a task releases a mutex, the holding of which had resulted in
 * the task inheriting the priority of a higher priority task.
 * pxTCBOfMutexHolder is a pointer to the TCB of the task that is releasing the
 * mutex.  uxOriginalPriority is the task's configured (base) priority. */
#define traceTASK_PRIORITY_DISINHERIT(pxTCBOfMutexHolder, uxOriginalPriority) \
    RTE_MSG2(MSG2_RTOS_TASK_PRIORITY_DISINHERIT, F_RTOS_TASKS, rtos_get_task_name(pxTCBOfMutexHolder), \
            (uint32_t)(uxOriginalPriority))

/* Task is about to block because it cannot read from a
 * queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
 * upon which the read was attempted.  pxCurrentTCB points to the TCB of the
 * task that attempted the read. */
#define traceBLOCKING_ON_QUEUE_RECEIVE(pxQueue) \
    RTE_MSG1(MSG1_RTOS_BLOCKING_ON_QUEUE_RECEIVE, F_RTOS_TASKS, RTE_GET_QUEUE_NAME(pxQueue))

/* Task is about to block because it cannot read from a
 * queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
 * upon which the read was attempted.  pxCurrentTCB points to the TCB of the
 * task that attempted the read. */
#define traceBLOCKING_ON_QUEUE_PEEK(pxQueue) \
    RTE_MSG1(MSG1_RTOS_BLOCKING_ON_QUEUE_PEEK, F_RTOS_TASKS, RTE_GET_QUEUE_NAME(pxQueue))

/* Task is about to block because it cannot write to a
 * queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
 * upon which the write was attempted.  pxCurrentTCB points to the TCB of the
 * task that attempted the write. 
 * xCopyPosition: 0 - queueSEND_TO_BACK, 1 - queueSEND_TO_FRONT, 2 - queueOVERWRITE */
#define traceBLOCKING_ON_QUEUE_SEND(pxQueue) \
    RTE_MSG2(MSG2_RTOS_BLOCKING_ON_QUEUE_SEND, F_RTOS_TASKS, \
            RTE_GET_QUEUE_NAME(pxQueue), (uint32_t)(xCopyPosition))
#endif  // RTE_TRACE_RTOS_TASKS == 1

/* The following event macros are embedded in the kernel API calls. */

#if RTE_TRACE_RTOS_EXPERT == 1
/* These macros were originally introduced for Segger SystemView FreeRTOS trace and are
 * not essential for the basic functionality of the current RTEdbg trace implementation.
 */
#define traceMOVED_TASK_TO_READY_STATE(pxTCB) \
    RTE_MSG1(MSG1_RTOS_MOVED_TASK_TO_READY_STATE, F_RTOS_EXPERT, rtos_get_task_name(pxTCB))

#define tracePOST_MOVED_TASK_TO_READY_STATE(pxTCB) \
    RTE_MSG1(MSG1_RTOS_POST_MOVED_TASK_TO_READY_STATE, F_RTOS_EXPERT, rtos_get_task_name(pxTCB))

#define traceMOVED_TASK_TO_DELAYED_LIST() \
    RTE_MSG1(MSG1_RTOS_MOVED_TASK_TO_DELAYED_LIST, F_RTOS_EXPERT, rtos_get_task_name(pxCurrentTCB))

#define traceMOVED_TASK_TO_OVERFLOW_DELAYED_LIST() \
    RTE_MSG1(MSG1_RTOS_MOVED_TASK_TO_OVERFLOW_DELAYED_LIST, F_RTOS_EXPERT, \
             rtos_get_task_name(pxCurrentTCB))
#endif  // RTE_TRACE_RTOS_EXPERT == 1


#if RTE_TRACE_RTOS_EXPERT == 1
#define traceQUEUE_REGISTRY_ADD(xQueue, pcQueueName) \
    RTE_MSG2(MSG2_RTOS_QUEUE_REGISTRY_ADD, F_RTOS_EXPERT , (uint32_t)xQueue, \
             string_to_uint32(pcQueueName))
#endif // RTE_TRACE_RTOS_EXPERT == 1


#if RTE_TRACE_RTOS_QUEUE == 1
#define traceQUEUE_CREATE(pxNewQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_CREATE, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxNewQueue), (uint32_t)ucQueueType)

/* ucQueueType: 0 - queueQUEUE_TYPE_BASE, 1 - queueQUEUE_TYPE_MUTEX, 
 * 2 - queueQUEUE_TYPE_COUNTING_SEMAPHORE, 3 - queueQUEUE_TYPE_BINARY_SEMAPHORE,
 * 4 - queueQUEUE_TYPE_RECURSIVE_MUTEX, 5 - queueQUEUE_TYPE_SET */
#define traceQUEUE_CREATE_FAILED(ucQueueType) \
    RTE_MSG1(MSG1_RTOS_QUEUE_CREATE_FAILED, F_RTOS_QUEUE, (uint32_t)(ucQueueType))

#define traceCREATE_MUTEX(pxNewQueue) \
    RTE_MSG1(MSG1_RTOS_CREATE_MUTEX, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxNewQueue))

#define traceCREATE_MUTEX_FAILED() \
    RTE_MSG0(MSG0_RTOS_CREATE_MUTEX_FAILED, F_RTOS_QUEUE)

#define traceGIVE_MUTEX_RECURSIVE(pxMutex) \
    RTE_MSG1(MSG1_RTOS_GIVE_MUTEX_RECURSIVE, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxMutex))

#define traceGIVE_MUTEX_RECURSIVE_FAILED(pxMutex) \
    RTE_MSG1(MSG1_RTOS_GIVE_MUTEX_RECURSIVE_FAILED, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxMutex))

#define traceTAKE_MUTEX_RECURSIVE(pxMutex) \
    RTE_MSG1(MSG1_RTOS_TAKE_MUTEX_RECURSIVE, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxMutex))

#define traceTAKE_MUTEX_RECURSIVE_FAILED(pxMutex) \
    RTE_MSG1(MSG1_RTOS_TAKE_MUTEX_RECURSIVE_FAILED, F_RTOS_QUEUE, RTE_GET_QUEUE_NAME(pxMutex))

#define traceCREATE_COUNTING_SEMAPHORE() \
    RTE_MSG3(MSG3_RTOS_CREATE_COUNTING_SEMAPHORE, F_RTOS_QUEUE, \
            (uint32_t)(xHandle), (uint32_t)(uxMaxCount), (uint32_t)(uxInitialCount))

#define traceCREATE_COUNTING_SEMAPHORE_FAILED() \
    RTE_MSG0(MSG0_RTOS_CREATE_COUNTING_SEMAPHORE_FAILED, F_RTOS_QUEUE)
#endif  // RTE_TRACE_RTOS_QUEUE == 1

#if RTE_TRACE_RTOS_BASIC == 1
/* xCopyPosition: 0 - queueSEND_TO_BACK, 1 - queueSEND_TO_FRONT, 2 - queueOVERWRITE 
 * Packed into 32 bits: xCopyPosition (4 bits, bits 28-31), xTicksToWait (28 bits, bits 0-27) */
#define traceQUEUE_SEND(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SEND, F_RTOS_BASIC, \
        RTE_GET_QUEUE_NAME(pxQueue), pxQueue->uxMessagesWaiting)

#define traceQUEUE_SEND_FAILED(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SEND_FAILED, F_RTOS_BASIC, \
             RTE_GET_QUEUE_NAME(pxQueue), \
             (((uint32_t)xTicksToWait > 0x0FFFFFFFU ? 0x0FFFFFFFU : (uint32_t)xTicksToWait) | \
             (((uint32_t)xCopyPosition & 0xFU) << 28U)))

#define traceQUEUE_RECEIVE(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_RECEIVE, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue), \
            (((uint32_t)((xTicksToWait > 0xFFFFU) ? 0xFFFFU : xTicksToWait)) | \
            (uint32_t)(((pxQueue->uxMessagesWaiting > 0xFFFFU) ? 0xFFFFU : pxQueue->uxMessagesWaiting) << 16U)))

#define traceQUEUE_PEEK(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_PEEK, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue), \
            (uint32_t)xTicksToWait)

#define traceQUEUE_PEEK_FAILED(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_PEEK_FAILED, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue), \
            (uint32_t)xTicksToWait)

#define traceQUEUE_PEEK_FROM_ISR(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_PEEK_FROM_ISR, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue))

#define traceQUEUE_RECEIVE_FAILED(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_RECEIVE_FAILED, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue), \
            (uint32_t)xTicksToWait)

#define traceQUEUE_SEND_FROM_ISR(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_SEND_FROM_ISR, F_RTOS_BASIC, \
             RTE_GET_QUEUE_NAME(pxQueue), pxQueue->uxMessagesWaiting)

#define traceQUEUE_SEND_FROM_ISR_FAILED(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_SEND_FROM_ISR_FAILED, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue))

#define traceQUEUE_RECEIVE_FROM_ISR(pxQueue) \
    RTE_MSG2(MSG2_RTOS_QUEUE_RECEIVE_FROM_ISR, F_RTOS_BASIC, \
             RTE_GET_QUEUE_NAME(pxQueue), pxQueue->uxMessagesWaiting)

#define traceQUEUE_RECEIVE_FROM_ISR_FAILED(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_RECEIVE_FROM_ISR_FAILED, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue))

#define traceQUEUE_DELETE(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_DELETE, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue))

#define traceQUEUE_PEEK_FROM_ISR_FAILED(pxQueue) \
    RTE_MSG1(MSG1_RTOS_QUEUE_PEEK_FROM_ISR_FAILED, F_RTOS_BASIC, RTE_GET_QUEUE_NAME(pxQueue))
#endif  // RTE_TRACE_RTOS_BASIC == 1


#if RTE_TRACE_RTOS_TASKS == 1    
#define traceTASK_CREATE(pxNewTCB) \
    RTE_MSG1(MSG1_RTOS_TASK_CREATE, F_RTOS_TASKS, rtos_get_task_name(pxNewTCB))

#define traceTASK_CREATE_FAILED() \
    RTE_MSG0(MSG0_RTOS_TASK_CREATE_FAILED, F_RTOS_TASKS)

#define traceTASK_DELETE(pxTaskToDelete) \
    RTE_MSG1(MSG1_RTOS_TASK_DELETE, F_RTOS_TASKS, rtos_get_task_name(pxTaskToDelete))
#endif  // RTE_TRACE_RTOS_TASKS == 1

#if RTE_TRACE_RTOS_BASIC == 1
#define traceTASK_DELAY_UNTIL(x) \
    RTE_MSG1(MSG1_RTOS_TASK_DELAY_UNTIL, F_RTOS_BASIC, (uint32_t)(x))

#define traceTASK_DELAY() \
    RTE_MSG1(MSG1_RTOS_TASK_DELAY, F_RTOS_BASIC, (uint32_t)xTicksToDelay)

#define traceTASK_PRIORITY_SET(pxTask, uxNewPriority) \
    RTE_MSG2(MSG2_RTOS_TASK_PRIORITY_SET, F_RTOS_BASIC, rtos_get_task_name(pxTask), \
            (uint32_t)(uxNewPriority))

#define traceTASK_SUSPEND(pxTaskToSuspend) \
    RTE_MSG1(MSG1_RTOS_TASK_SUSPEND, F_RTOS_BASIC, rtos_get_task_name(pxTaskToSuspend))

#define traceTASK_RESUME(pxTaskToResume) \
    RTE_MSG1(MSG1_RTOS_TASK_RESUME, F_RTOS_BASIC, rtos_get_task_name(pxTaskToResume))

#define traceTASK_RESUME_FROM_ISR(pxTaskToResume) \
    RTE_MSG1(MSG1_RTOS_TASK_RESUME_FROM_ISR, F_RTOS_BASIC, rtos_get_task_name(pxTaskToResume))
#endif  // RTE_TRACE_RTOS_BASIC == 1

#if RTE_TRACE_RTOS_TASKS == 1
#define traceTASK_INCREMENT_TICK(xTickCount) \
    RTE_MSG1(MSG1_RTOS_TASK_INCREMENT_TICK, F_RTOS_TASKS, (uint32_t)(xTickCount))
#endif  // RTE_TRACE_RTOS_TASKS == 1


#if ( configUSE_TIMERS == 1 )
#if RTE_TRACE_RTOS_TIMER == 1  
#define traceTIMER_CREATE(pxNewTimer) \
    RTE_MSG2(MSG2_RTOS_TIMER_CREATE, F_RTOS_TIMER, rtos_get_timer_name(pxNewTimer), \
            (uint32_t)xTimerPeriodInTicks)

#define traceTIMER_CREATE_FAILED() \
    RTE_MSG0(MSG0_RTOS_TIMER_CREATE_FAILED, F_RTOS_TIMER)

#define traceTIMER_COMMAND_SEND(pxTimer, xCommandID, xOptionalValue, xStatus) \
    RTE_EXT_MSG3_1(EXT_MSG3_1_RTOS_TIMER_COMMAND_SEND, F_RTOS_TIMER, rtos_get_timer_name(pxTimer), \
             (uint32_t)(xCommandID), (uint32_t)(xOptionalValue), (uint32_t)(xStatus))

#define traceTIMER_EXPIRED(pxTimer) \
    RTE_MSG1(MSG1_RTOS_TIMER_EXPIRED, F_RTOS_TIMER, rtos_get_timer_name(pxTimer))

#define traceTIMER_COMMAND_RECEIVED(pxTimer, xMessageID, xMessageValue) \
    RTE_MSG3(MSG3_RTOS_TIMER_COMMAND_RECEIVED, F_RTOS_TIMER, rtos_get_timer_name(pxTimer), \
            (uint32_t)(xMessageID), (uint32_t)(xMessageValue))
#endif  // RTE_TRACE_RTOS_TIMER == 1
#endif // ( configUSE_TIMERS == 1 )


#if RTE_TRACE_RTOS_MALLOC == 1
#define traceMALLOC(pvAddress, uiSize) \
    RTE_MSG2(MSG2_RTOS_MALLOC, F_RTOS_MALLOC, (uint32_t)(pvAddress), (uint32_t)(uiSize))

#define traceFREE(pvAddress, uiSize) \
    RTE_MSG2(MSG2_RTOS_FREE, F_RTOS_MALLOC, (uint32_t)(pvAddress), (uint32_t)(uiSize))
#endif  // RTE_TRACE_RTOS_MALLOC == 1


#if RTE_TRACE_RTOS_TASKS == 1    
#define traceEVENT_GROUP_CREATE(xEventGroup) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_CREATE, F_RTOS_TASKS, (uint32_t)(xEventGroup))

#define traceEVENT_GROUP_CREATE_FAILED() \
    RTE_MSG0(MSG0_RTOS_EVENT_GROUP_CREATE_FAILED, F_RTOS_TASKS)

#define traceEVENT_GROUP_SYNC_BLOCK(xEventGroup, uxBitsToSet, uxBitsToWaitFor) \
    RTE_MSG3(MSG3_RTOS_EVENT_GROUP_SYNC_BLOCK, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToSet), (uint32_t)(uxBitsToWaitFor))

#define traceEVENT_GROUP_SYNC_END(xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTimeoutOccurred) \
    RTE_MSG4(MSG4_RTOS_EVENT_GROUP_SYNC_END, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToSet), (uint32_t)(uxBitsToWaitFor), (uint32_t)(xTimeoutOccurred))

#define traceEVENT_GROUP_WAIT_BITS_BLOCK(xEventGroup, uxBitsToWaitFor) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_WAIT_BITS_BLOCK, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToWaitFor))

#define traceEVENT_GROUP_WAIT_BITS_END(xEventGroup, uxBitsToWaitFor, xTimeoutOccurred) \
    RTE_MSG3(MSG3_RTOS_EVENT_GROUP_WAIT_BITS_END, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToWaitFor), (uint32_t)(xTimeoutOccurred))

#define traceEVENT_GROUP_CLEAR_BITS(xEventGroup, uxBitsToClear) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_CLEAR_BITS, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToClear))

#define traceEVENT_GROUP_CLEAR_BITS_FROM_ISR(xEventGroup, uxBitsToClear) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_CLEAR_BITS_FROM_ISR, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToClear))

#define traceEVENT_GROUP_SET_BITS(xEventGroup, uxBitsToSet) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_SET_BITS, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToSet))

#define traceEVENT_GROUP_SET_BITS_FROM_ISR(xEventGroup, uxBitsToSet) \
    RTE_MSG2(MSG2_RTOS_EVENT_GROUP_SET_BITS_FROM_ISR, F_RTOS_TASKS, (uint32_t)(xEventGroup), \
            (uint32_t)(uxBitsToSet))

#define traceEVENT_GROUP_DELETE(xEventGroup) \
    RTE_MSG1(MSG1_RTOS_EVENT_GROUP_DELETE, F_RTOS_TASKS, (uint32_t)(xEventGroup))
#endif  // RTE_TRACE_RTOS_TASKS == 1


#if ( configUSE_TIMERS == 1 )
#if RTE_TRACE_RTOS_TIMER == 1
#define tracePEND_FUNC_CALL(xFunctionToPend, pvParameter1, ulParameter2, ret) \
    RTE_MSG4(MSG4_RTOS_PEND_FUNC_CALL, F_RTOS_TIMER, (uint32_t)(xFunctionToPend), \
            (uint32_t)(pvParameter1), (uint32_t)(ulParameter2), (uint32_t)(ret))

#define tracePEND_FUNC_CALL_FROM_ISR(xFunctionToPend, pvParameter1, ulParameter2, ret) \
    RTE_MSG4(MSG4_RTOS_PEND_FUNC_CALL_FROM_ISR, F_RTOS_TIMER, (uint32_t)(xFunctionToPend), \
            (uint32_t)(pvParameter1), (uint32_t)(ulParameter2), (uint32_t)(ret))
#endif  // RTE_TRACE_RTOS_TIMER == 1
#endif  // ( configUSE_TIMERS == 1 )


#if RTE_TRACE_RTOS_BASIC == 1
#if RTE_FREERTOS_VERSION >= 100400
/* Packed: uxIndexToWait (16 bits, bits 0-15), xClearCountOnExit (1 bit, bit 16) */
#define traceTASK_NOTIFY_TAKE_BLOCK(uxIndexToWait) \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY_TAKE_BLOCK1, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
            (uint32_t)(((uxIndexToWait) & 0xFFFFU) | (uint32_t)(xClearCountOnExit << 16U)), \
            (uint32_t)xTicksToWait)

/* Packed: uxIndexToWait (16 bits, bits 0-15), xClearCountOnExit (bits 16-31) */
#define traceTASK_NOTIFY_TAKE(uxIndexToWait) \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY_TAKE1, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
            (uint32_t)(((uxIndexToWait) & 0xFFFFU) | (uint32_t)(xClearCountOnExit << 16U)), \
            (uint32_t)xTicksToWait)

/* Packed: uxIndexToWait (8 bits, bits 24-31), xTicksToWait (24 bits, bits 0-23) */
#define traceTASK_NOTIFY_WAIT_BLOCK(uxIndexToWait) \
    RTE_MSG4(MSG4_RTOS_TASK_NOTIFY_WAIT_BLOCK1, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
             (uint32_t)((uxIndexToWait) & 0xFFU) | (((uint32_t)(xTicksToWait & 0x00FFFFFFU)) << 8U), \
            (uint32_t)ulBitsToClearOnEntry, (uint32_t)ulBitsToClearOnExit)

/* Packed: uxIndexToWait (8 bits, bits 24-31), xTicksToWait (24 bits, bits 0-23) */
#define traceTASK_NOTIFY_WAIT(uxIndexToWait) \
    RTE_MSG4(MSG4_RTOS_TASK_NOTIFY_WAIT1, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
            ((uint32_t)(uxIndexToWait) & 0xFFU) | (uint32_t)((xTicksToWait & 0x00FFFFFFU) << 8U), \
            (uint32_t)ulBitsToClearOnEntry, (uint32_t)ulBitsToClearOnExit)

/* Packed: uxIndexToNotify (16 bits, bits 16-31), eAction (16 bits, bits 0-15) */
#define traceTASK_NOTIFY(uxIndexToNotify) \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY1, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify), \
             ((uint32_t)(uxIndexToNotify) & 0xFFFFU) | (((uint32_t)(eAction & 0xFFFFU) << 16U)), \
             (uint32_t)ulValue)

/* Packed: uxIndexToNotify (16 bits, bits 16-31), eAction (16 bits, bits 0-15) */
#define traceTASK_NOTIFY_FROM_ISR(uxIndexToNotify) \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY_FROM_ISR1, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify), \
            ((uint32_t)(uxIndexToNotify) & 0xFFFFU) | (((uint32_t)(eAction & 0xFFFFU) << 16U)), \
             (uint32_t)ulValue)

#define traceTASK_NOTIFY_GIVE_FROM_ISR(uxIndexToNotify) \
    RTE_MSG2(MSG2_RTOS_TASK_NOTIFY_GIVE_FROM_ISR1, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify), \
            (uint32_t)(uxIndexToNotify))

#else   // RTE_FREERTOS_VERSION < 110000
/* Packed: xClearCountOnExit (1 bit, bit 31), xTicksToWait (31 bits, bits 0-30) */
#define traceTASK_NOTIFY_TAKE_BLOCK() \
    RTE_MSG2(MSG2_RTOS_TASK_NOTIFY_TAKE_BLOCK2, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
             ((uint32_t)(xClearCountOnExit & 1U)) | \
             (((uint32_t)xTicksToWait > 0x7FFFFFFFU ? 0x7FFFFFFFU : (uint32_t)xTicksToWait) << 1U))

/* Packed: xClearCountOnExit (1 bit, bit 31), xTicksToWait (31 bits, bits 0-30) */
#define traceTASK_NOTIFY_TAKE() \
    RTE_MSG2(MSG2_RTOS_TASK_NOTIFY_TAKE2, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
             (((uint32_t)xClearCountOnExit & 1U) | \
             (((uint32_t)xTicksToWait > 0x7FFFFFFFU ? 0x7FFFFFFFU : (uint32_t)xTicksToWait) << 1U)))

#define traceTASK_NOTIFY_WAIT_BLOCK() \
    RTE_MSG4(MSG4_RTOS_TASK_NOTIFY_WAIT_BLOCK2, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
            (uint32_t)xTicksToWait, (uint32_t)ulBitsToClearOnEntry, (uint32_t)ulBitsToClearOnExit)

#define traceTASK_NOTIFY_WAIT() \
    RTE_MSG4(MSG4_RTOS_TASK_NOTIFY_WAIT2, F_RTOS_BASIC, rtos_get_task_name(pxCurrentTCB), \
            (uint32_t)xTicksToWait, (uint32_t)ulBitsToClearOnEntry, (uint32_t)ulBitsToClearOnExit)

#define traceTASK_NOTIFY() \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY2, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify), \
            (uint32_t)eAction, (uint32_t)ulValue)

#define traceTASK_NOTIFY_FROM_ISR() \
    RTE_MSG3(MSG3_RTOS_TASK_NOTIFY_FROM_ISR2, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify), \
            (uint32_t)eAction, (uint32_t)ulValue)

#define traceTASK_NOTIFY_GIVE_FROM_ISR() \
    RTE_MSG1(MSG1_RTOS_TASK_NOTIFY_GIVE_FROM_ISR2, F_RTOS_BASIC, rtos_get_task_name(xTaskToNotify))
#endif  // RTE_FREERTOS_VERSION => 110000
#endif  // RTE_TRACE_RTOS_BASIC == 1


#if RTE_TRACE_RTOS_EXPERT == 1
#define traceISR_EXIT_TO_SCHEDULER() \
    RTE_MSG0(MSG0_RTOS_ISR_EXIT_TO_SCHEDULER, F_RTOS_EXPERT)

#define traceISR_EXIT() \
    RTE_MSG0(MSG0_RTOS_ISR_EXIT, F_RTOS_EXPERT)

#define traceISR_ENTER() \
    RTE_MSG0(MSG0_RTOS_ISR_ENTER, F_RTOS_EXPERT)
#endif // RTE_TRACE_RTOS_EXPERT == 1

#if configUSE_STREAM_BUFFERS == 1
#if RTE_TRACE_RTOS_STREAMS == 1
/* xStreamBufferType: 0 - sbTYPE_STREAM_BUFFER, 1 - sbTYPE_MESSAGE_BUFFER, 2 - sbTYPE_STREAM_BATCHING_BUFFER */
#define traceSTREAM_BUFFER_CREATE_FAILED(xStreamBufferType) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_CREATE_FAILED, F_RTOS_STREAMS, (uint32_t)(xStreamBufferType))

#define traceSTREAM_BUFFER_CREATE_STATIC_FAILED(xReturn, xStreamBufferType) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_CREATE_STATIC_FAILED, F_RTOS_STREAMS, \
            (uint32_t)(xStreamBufferType))

#define traceSTREAM_BUFFER_CREATE(pxStreamBuffer, xStreamBufferType) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_CREATE, F_RTOS_STREAMS, (uint32_t)(pxStreamBuffer), \
            (uint32_t)(xStreamBufferType))

#define traceSTREAM_BUFFER_DELETE(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_DELETE, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_RESET(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_RESET_FROM_ISR(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RESET_FROM_ISR, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceBLOCKING_ON_STREAM_BUFFER_SEND(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_BLOCKING_ON_STREAM_BUFFER_SEND, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_SEND(xStreamBuffer, xBytesSent) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SEND, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer), \
            (uint32_t)(xBytesSent))

#define traceSTREAM_BUFFER_SEND_FAILED(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_SEND_FAILED, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_SEND_FROM_ISR(xStreamBuffer, xBytesSent) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_SEND_FROM_ISR, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer), \
            (uint32_t)(xBytesSent))

#define traceBLOCKING_ON_STREAM_BUFFER_RECEIVE(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_BLOCKING_ON_STREAM_BUFFER_RECEIVE, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_RECEIVE(xStreamBuffer, xReceivedLength) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_RECEIVE, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer), \
            (uint32_t)(xReceivedLength))

#define traceSTREAM_BUFFER_RECEIVE_FAILED(xStreamBuffer) \
    RTE_MSG1(MSG1_RTOS_STREAM_BUFFER_RECEIVE_FAILED, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer))

#define traceSTREAM_BUFFER_RECEIVE_FROM_ISR(xStreamBuffer, xReceivedLength) \
    RTE_MSG2(MSG2_RTOS_STREAM_BUFFER_RECEIVE_FROM_ISR, F_RTOS_STREAMS, (uint32_t)(xStreamBuffer), \
            (uint32_t)(xReceivedLength))
#endif  // RTE_TRACE_RTOS_STREAMS == 1
#endif  // configUSE_STREAM_BUFFERS == 1

#ifdef __cplusplus
}
#endif

#endif  // RTE_FREERTOS_TRACE_H

/*==== End of file ====*/
