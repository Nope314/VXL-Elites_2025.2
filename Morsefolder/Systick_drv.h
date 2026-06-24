#ifndef SYSTICK_DRV_H
#define SYSTICK_DRV_H

#include <stdint.h>

extern volatile uint32_t millis;

void SysTick_DRV_Init(void);

#endif
