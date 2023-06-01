#include "Motors.h"

typedef struct {
    u8 enable;//�ܿ���
    u8 lq_enable;
    u8 lh_enable;
    u8 rq_enable;
    u8 rh_enable;
    u8 lq_duty;
    u8 lh_duty;
    u8 rq_duty;
    u8 rh_duty;
} MotorCfg;

static void Motors_config(MotorCfg cfg) {
    PWMx_InitDefine		PWMx_InitStructure;
    // ������
    PWMx_InitStructure.PWM_Period   		= PERIOD;	//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime 		= 0;								//��������������, 0~255
    PWMx_InitStructure.PWM_EnoSelect		= 0;//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWMx_InitStructure.PWM_PS_SW    		= 0;//�л��˿�

    //////////////// LQ
    if(cfg.lq_enable) {
        PWMx_InitStructure.PWM_EnoSelect		|= ENO4P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		|= ENO4N;
        PWMx_InitStructure.PWM_PS_SW    		|= PWM4_SW_P16_P17;//�л��˿�
    } else {
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO4P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO4N;
        PWMx_InitStructure.PWM_PS_SW    		&= ~PWM4_SW_P16_P17;//�л��˿�
    }
    PWMx_InitStructure.PWM_CC4Enable   = cfg.lq_enable ? ENABLE : DISABLE;//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    PWMx_InitStructure.PWM_CC4NEnable  = cfg.lq_enable ? ENABLE : DISABLE;//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
    // pwm4
    PWMx_InitStructure.PWM4_Mode    		=	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM4_SetPriority	= Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    PWMx_InitStructure.PWM4_Duty    		= cfg.lq_duty * PERIOD / 100;//PWM4ռ�ձ�ʱ��, 0~Period

    //////////////// RQ
    if(cfg.rq_enable) {
        PWMx_InitStructure.PWM_EnoSelect		|= ENO3P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		|= ENO3N;
        PWMx_InitStructure.PWM_PS_SW    		|= PWM3_SW_P14_P15;//�л��˿�
    } else {
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO3P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO3N;
        PWMx_InitStructure.PWM_PS_SW    		&= ~PWM3_SW_P14_P15;//�л��˿�
    }
    PWMx_InitStructure.PWM_CC3Enable   = cfg.rq_enable ? ENABLE : DISABLE;//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    PWMx_InitStructure.PWM_CC3NEnable  = cfg.rq_enable ? ENABLE : DISABLE;//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
    // pwm3
    PWMx_InitStructure.PWM3_Mode    		=	CCMRn_PWM_MODE2;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM3_SetPriority	= Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    PWMx_InitStructure.PWM3_Duty    		= cfg.rq_duty * PERIOD / 100;//PWM4ռ�ձ�ʱ��, 0~Period

    //////////////// LH
    if(cfg.lh_enable) {
        PWMx_InitStructure.PWM_EnoSelect		|= ENO1P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		|= ENO1N;
        PWMx_InitStructure.PWM_PS_SW    		|= PWM1_SW_P20_P21;//�л��˿�
    } else {
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO1P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO1N;
        PWMx_InitStructure.PWM_PS_SW    		&= ~PWM1_SW_P20_P21;//�л��˿�
    }
    PWMx_InitStructure.PWM_CC1Enable   = cfg.lh_enable ? ENABLE : DISABLE;//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    PWMx_InitStructure.PWM_CC1NEnable  = cfg.lh_enable ? ENABLE : DISABLE;//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
    // pwm1
    PWMx_InitStructure.PWM1_Mode    		=	CCMRn_PWM_MODE2;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM1_SetPriority	= Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    PWMx_InitStructure.PWM1_Duty    		= cfg.lh_duty * PERIOD / 100;//PWM4ռ�ձ�ʱ��, 0~Period

    //////////////// RH
    if(cfg.rh_enable) {
        PWMx_InitStructure.PWM_EnoSelect		|= ENO2P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		|= ENO2N;
        PWMx_InitStructure.PWM_PS_SW    		|= PWM2_SW_P22_P23;//�л��˿�
    } else {
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO2P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_EnoSelect		&= ~ENO2N;
        PWMx_InitStructure.PWM_PS_SW    		&= ~PWM2_SW_P22_P23;//�л��˿�
    }
    PWMx_InitStructure.PWM_CC2Enable   = cfg.rh_enable ? ENABLE : DISABLE;//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    PWMx_InitStructure.PWM_CC2NEnable  = cfg.rh_enable ? ENABLE : DISABLE;//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
    // pwm2
    PWMx_InitStructure.PWM2_Mode    		=	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM2_SetPriority	= Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    PWMx_InitStructure.PWM2_Duty    		= cfg.rh_duty * PERIOD / 100;//PWM4ռ�ձ�ʱ��, 0~Period

    ///////////////// PWM��������
    PWMx_InitStructure.PWM_MainOutEnable= cfg.enable ? ENABLE : DISABLE;				//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = cfg.enable ? ENABLE : DISABLE;				//ʹ�ܼ�����, ENABLE,DISABLE

    PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB
}

// 0 - 100
static u8 speed2duty(u8 speed, u8 direction) {
	//direction: 0back 1forward
	if(direction) {
		// forward
		// speed 		duty
		// 0				50
		// 50				25
		// 100			0
		return 50 - speed / 2;
	} else {
		// backward
		// speed 		duty
		// 0				50
		// 50				75
		// 100			100
		return 50 + speed / 2;
	}
}

void Motors_init() {
    MOTORS_PIN_INIT();
}

// ǰ��

void Motors_forward(u8 speed) {
    // �ĸ�������ǰת��
    MotorCfg cfg;
    cfg.enable = 1;//�ܿ���
    cfg.lq_enable = 1;
    cfg.lh_enable = 1;
    cfg.rq_enable = 1;
    cfg.rh_enable = 1;
    cfg.lq_duty = speed2duty(speed, 1);
    cfg.lh_duty = speed2duty(speed, 1);
    cfg.rq_duty = speed2duty(speed, 1);
    cfg.rh_duty = speed2duty(speed, 1);
    Motors_config(cfg);
}
// ����
void Motors_backward(u8 speed) {
    MotorCfg cfg;
    cfg.enable = 1;//�ܿ���
    cfg.lq_enable = 1;
    cfg.lh_enable = 1;
    cfg.rq_enable = 1;
    cfg.rh_enable = 1;
    cfg.lq_duty = speed2duty(speed, 0);
    cfg.lh_duty = speed2duty(speed, 0);
    cfg.rq_duty = speed2duty(speed, 0);
    cfg.rh_duty = speed2duty(speed, 0);
    Motors_config(cfg);
}
void Motors_left(u8 speed) {
    MotorCfg cfg;
    cfg.enable = 1;//�ܿ���
    cfg.lq_enable = 1;
    cfg.lh_enable = 1;
    cfg.rq_enable = 1;
    cfg.rh_enable = 1;
    cfg.lq_duty = speed2duty(0, 1);
    cfg.lh_duty = speed2duty(0, 1);
    cfg.rq_duty = speed2duty(speed, 1);
    cfg.rh_duty = speed2duty(speed, 1);
    Motors_config(cfg);
}
void Motors_right(u8 speed) {
    MotorCfg cfg;
    cfg.enable = 1;//�ܿ���
    cfg.lq_enable = 1;
    cfg.lh_enable = 1;
    cfg.rq_enable = 1;
    cfg.rh_enable = 1;
    cfg.lq_duty = speed2duty(speed, 1);
    cfg.lh_duty = speed2duty(speed, 1);
    cfg.rq_duty = speed2duty(0, 1);
    cfg.rh_duty = speed2duty(0, 1);
    Motors_config(cfg);
}
void Motors_around(u8 speed) {
    MotorCfg cfg;
    cfg.enable = 1;//�ܿ���
    cfg.lq_enable = 1;
    cfg.lh_enable = 1;
    cfg.rq_enable = 1;
    cfg.rh_enable = 1;
    cfg.lq_duty = speed2duty(speed, 1);
    cfg.lh_duty = speed2duty(speed, 1);
    cfg.rq_duty = speed2duty(speed, 0);
    cfg.rh_duty = speed2duty(speed, 0);
    Motors_config(cfg);
}

// ֹͣ
void Motors_stop() {
    MotorCfg cfg;
    cfg.enable = 0;//�ܿ���
    cfg.lq_enable = 0;
    cfg.lh_enable = 0;
    cfg.rq_enable = 0;
    cfg.rh_enable = 0;
    cfg.lq_duty = 0;
    cfg.lh_duty = 0;
    cfg.rq_duty = 0;
    cfg.rh_duty = 0;
    Motors_config(cfg);
}