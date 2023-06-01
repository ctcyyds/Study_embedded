#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "PWM.h"

//P0.1
#define PERIOD	(MAIN_Fosc / 1000 - 1)

void GPIO_config(void) {
    GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
    GPIO_InitStructure.Pin  = GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO,
    GPIO_InitStructure.Mode = GPIO_OUT_PP;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//��ʼ��
}

void PWM_config(void) {

    PWMx_InitDefine		PWMx_InitStructure;
    // ������
    // (MAIN_Fosc / 1000 - 1) ���ڼ���ֵ
    PWMx_InitStructure.PWM_Period   		= PERIOD;	//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime 		= 0;								//��������������, 0~255
    PWMx_InitStructure.PWM_EnoSelect		= ENO6P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWMx_InitStructure.PWM_PS_SW    		= PWM6_SW_P01;//�л��˿�

    // ����PWM�˿�����
    // pwm6
    PWMx_InitStructure.PWM6_Mode    		=	CCMRn_PWM_MODE2;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM6_Duty    		= 0;			//PWM4ռ�ձ�ʱ��, 0~Period

    // pwm6
    PWMx_InitStructure.PWM_CC6Enable   = ENABLE;				//����PWM6P���벶��/�Ƚ����,  ENABLE,DISABLE

    // PWM��������
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB

}

int main() {
    PWMx_Duty duty;
    u8 d = 0;// �ٷֱ�ֵ
    GPIO_config();
    PWM_config();
    EA = 1;

    while(1) {

        d ++;
				if(d >= 100) {
					d = 0;
				}
        // ռ�ձȡ����ߵ�ƽ�� ����ֵ�� ��0 - 100��
        duty.PWM6_Duty = d * PERIOD / 100 ;
        UpdatePwm(PWMB, &duty);
        delay_ms(10);
    }
}