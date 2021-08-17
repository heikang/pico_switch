#ifndef _CORE1_H_
#define _CORE1_H_

extern char core1buf[100];
extern volatile uint8_t core1flag;

void core1_entry(void);

#endif
