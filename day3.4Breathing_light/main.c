#include "config.h"
#include "GPIO.h"
#include "timer.h"
/*
LED������
*/
//����/�滻
#define LED3 P15
#define LED_SW P45
	
	u8 freq = 10;
	u8 duty = 1;
	u8 cont = 0;
	u8 total=0;
	
//GPIO��ʼ��
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//��ʼ��
}

//timer��ʼ��
void TIMER_config(void) {
    TIM_InitTypeDef        TIM_InitStructure;                        //�ṹ����
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;    //ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
    TIM_InitStructure.TIM_Priority    = Priority_0;            //ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    TIM_InitStructure.TIM_Interrupt = ENABLE;                    //�ж��Ƿ�����,   ENABLE��DISABLE
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;        //ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    TIM_InitStructure.TIM_ClkOut    = DISABLE;                //�Ƿ������������, ENABLE��DISABLE
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);        //��ֵ,>367
    TIM_InitStructure.TIM_Run       = ENABLE;                    //�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
    Timer_Inilize(Timer0,&TIM_InitStructure);                    //��ʼ��Timer0      Timer0,Timer1,Timer2,Timer3,Timer4
}
void timer0_call(){
	//LED3 = !LED3;
	if(cont < duty){
		LED3 = 0;
	}else{
		LED3 = 1;
	}
	cont++;
	if(cont == freq){
		cont = 0;
	}
	if(total == 100){
		duty++;
		total = 0;
	}
	total++;
	if(duty > 10){
		duty = 0;
	}
}

int main() {
    //����
    GPIO_config();
		TIMER_config();
    //�ж��ܿ���
    EA=1;

    LED_SW = 0;
    LED3 = 0;
	
    while(1) {
       
    }
}