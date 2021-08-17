#ifndef _CORE1_H_
#define _CORE1_H_


struct cpu1_task{
	void (*func)(void);
};

extern uint8_t flag; //0: no task , 1: task
extern struct cpu1_task task;

void core1_entry(void);

#endif
