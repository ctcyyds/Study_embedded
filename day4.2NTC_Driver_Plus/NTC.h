/*
������������
*/
#ifndef __NTC_H__
#define __NTC_H__
//STC8Hƽ̨�Ŀ⺯��
#include "ADC.h"


//�����õ���P04
#define NTC_PIN P04
#define NTC_CHN 12
//����״̬Ϊ��������
#define NTC_PIN_INIT() {P0M1 |= 0x10,	P0M0 &= ~ 0x10;}

//��ͬоƬ���Ĵ�
u16 NTC_Get_ADCResult(u8 chn);

//��ʼ������
void NTC_init();


//�ṩ�¶Ȼ�ȡ�ķ�����������������������ֵ
int NTC_get_temperature();




#endif