#ifndef __KEY_H__
#define __KEY_H__

#include "config.h"

#define KEY		P37

//�͵�ƽ
#define KEY_DOWN	0
//�ߵ�ƽ
#define KEY_UP		1
#define KEY_PIN_INIT() {P3M0 &= ~0x80; P3M1 &= ~0x80;}


void Key_init();
void Key_scan();


extern void Key_on_keyup();
extern void Key_on_keydown();

#endif