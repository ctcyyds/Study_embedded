#include "Buzzer.h"

u16 HZS[] = {
    1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};

void Buzzer_init()
{
    BUZZER_PIN_INIT();
}

void Buzzer_music(u8 note)
{ // ȷ��PWM������
    // ȷ��PWM��ռ�ձ�
    // note --> hz
    u16 hz = HZS[note - 1];
    u16 PERIOD = (MAIN_Fosc / hz - 1);
    PWMx_InitDefine PWMx_InitStructure;
    // ������
    PWMx_InitStructure.PWM_Period =PERIOD; // ����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;                  // ��������������, 0~255
    PWMx_InitStructure.PWM_EnoSelect = ENO5P;             // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWMx_InitStructure.PWM_PS_SW = PWM5_SW_P00;           // �л��˿�
    // ����PWM�˿����� PWM6
    PWMx_InitStructure.PWM5_Mode = CCMRn_PWM_MODE1; // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM5_Duty = PERIOD / 2;      // PWM6ռ�ձ�ʱ��, 0~Period

    // PWM6
    PWMx_InitStructure.PWM_CC5Enable = ENABLE; // ����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE

    // PWM��������
    PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // �����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable = ENABLE;    // ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);  // ��ʼ��PWM,  PWMA,PWMB
}