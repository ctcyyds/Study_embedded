#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "config.h"
#include "PWM.h"

#define BUZZER_PIN P00
// ���� Initialize,����Ϊ�������
#define BUZZER_PIN_INIT()            \
    {                                \
        P0M1 &= ~0x01, P0M0 |= 0x01; \
    }
// initialize
void Buzzer_init();

void Buzzer_music(u8 note);

#endif