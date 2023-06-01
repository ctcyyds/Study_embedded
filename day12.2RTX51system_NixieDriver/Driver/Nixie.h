#ifndef __NIXIE_H__
#define __NIXIE_H__

//���Ҫ����ֲ

#include "config.h"

// ����
#define NIX_DI	P44
// ���� byte
#define NIX_RCK  P43
// ��λ bit
#define NIX_SCK  P42

// ģʽ��pullup
#define NIXIE_PIN_INIT()	{P4M1 &= ~0x10,P4M0 &= ~0x10,P4M1 &= ~0x08,P4M0 &= ~0x08,P4M1 &= ~0x04,P4M0 &= ~0x04;}
//#define NOP2()	_nop_(),_nop_()

// ��ʼ��
void Nixie_init();

// ��ʾ����
// index: λ��
// dat: ����. �Ĵ���Ҫ�����ݣ��˵���֪��ƫ�
// dat: ��Ϊ��������ֵ���˵�ֵת�ɼĴ���Ҫ��ֵ
void Nixie_show(u8 index, u8 dat);


#endif