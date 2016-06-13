#include "sys.h"
#include "ucos_ii.h"
#include <stdlib.h>

static INT8U err = 0;
const INT8U TICK_TIME = 45;

sys_sem_t sys_sem_new(u8_t count)
{
	return OSSemCreate(count);
}

void sys_sem_signal(sys_sem_t sem)
{
	OSSemPost(sem);
}

u32_t sys_arch_sem_wait(sys_sem_t sem, u32_t timeout)
{
	timeout = (timeout + TICK_TIME - 1) / TICK_TIME;
	OSSemPend(sem, timeout, &err);
	if (OS_NO_ERR == err) return 0;
	else return SYS_ARCH_TIMEOUT;
}

void sys_sem_free(sys_sem_t sem)
{
	OSSemDel(sem, OS_DEL_ALWAYS, &err);
}

sys_mbox_t sys_mbox_new(int size)
{
	void **q_buff = (void **)malloc(size * sizeof(INT32U *));
	return OSQCreate(q_buff, size);
}

void sys_mbox_post(sys_mbox_t mbox, void *msg)
{
	OSQPost(mbox, msg);
}

err_t sys_mbox_trypost(sys_mbox_t mbox, void *msg)
{
	return OSQPost(mbox, msg);
}

u32_t sys_arch_mbox_fetch(sys_mbox_t mbox, void **msg, u32_t timeout)
{
	INT32U bin_time = 0;
	INT32U end_time = 0;
	INT32U time_consumed = 0;

	timeout = (timeout + TICK_TIME - 1) / TICK_TIME;
	bin_time = OSTimeGet();
	*msg = OSQPend(mbox, timeout, &err);

	if (err == OS_TIMEOUT)
	{
		return SYS_ARCH_TIMEOUT;
	}
	else
	{
		end_time = OSTimeGet();

		if (bin_time > end_time)  time_consumed = 0xffffffff - bin_time + end_time;
		else time_consumed = end_time - bin_time;

		time_consumed = (time_consumed < timeout) ? time_consumed :  timeout;

		return time_consumed * TICK_TIME;
	}
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t mbox, void **msg)
{
	*msg = OSQAccept(mbox, &err);
	if (OS_NO_ERR == err) return 0;
	else return SYS_MBOX_EMPTY;
}

void sys_mbox_free(sys_mbox_t mbox)
{
	OSQDel(mbox, OS_DEL_ALWAYS, &err);
}

struct sys_timeouts *sys_arch_timeouts(void)
{
	static struct sys_timeouts lwip_timeouts[OS_LOWEST_PRIO + 1] = {0};
	OS_TCB curr_task_pcb = {0};

	OSTaskQuery(OS_PRIO_SELF, &curr_task_pcb);
	return &lwip_timeouts[curr_task_pcb.OSTCBPrio];
}

sys_thread_t sys_thread_new(char *name, void (* thread)(void *arg), void *arg, int stack_size, int prio)
{
	INT8U *stack = (INT8U *)malloc(stack_size) + stack_size;
	return OSTaskCreate(thread, arg, (OS_STK *)stack, prio);
}

sys_prot_t sys_arch_protect(void)
{
	OS_CPU_SR  cpu_sr = 0;
	OS_ENTER_CRITICAL();
	return cpu_sr;
}

void sys_arch_unprotect(sys_prot_t cpu_sr)
{
	OS_EXIT_CRITICAL() ;
}

