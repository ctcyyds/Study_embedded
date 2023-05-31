#include "config.h"
#include "GPIO.h"
#include "timer.h"
#include "UART.h"
#include "delay.h"
#include <stdio.h>
/*
1.���ڣ�ͨ��PC�����ڷ���Ϣ
2.����յ�0x01��timer�о�ȥ��ӡHello Word
3.����յ������ģ��Ͳ���ӡ
*/

u8 tmp=0x00;

//GPIO��ʼ��
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_3;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}

//UART��ʼ��
void UART_config(void) {
    COMx_InitDefine        COMx_InitStructure;                    //�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;    //ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;            //ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;            //������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;                //��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;            //�����ʼӱ�, ENABLE��DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;                //�ж�����,   ENABLE��DISABLE
    COMx_InitStructure.UART_Priority  = Priority_0;            //ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;    //�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);        //��ʼ������1 UART1,UART2,UART3,UART4
}

//Timer��ʼ��
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

//ʹ��Printf
char putchar (char dat){
	TX1_write2buff(dat);
}

void timer0_call() {
    if(tmp == 0x01) {
       // PrintString1("Hello Word\r\n"); // д�ַ���
			printf("Hello Word\r\n");
    }
}

int main() {
    u8 i;
    //����
    GPIO_config();
    UART_config();
    TIMER_config();

    //�ж��ܿ���
    EA=1;

    while(1) {
        delay_ms(10);
        //����PC��������Ϣ
        if(COM1.RX_TimeOut > 0)        //��ʱ����
        {
            if(--COM1.RX_TimeOut == 0)
            {
                if(COM1.RX_Cnt > 0)
                {
                    for(i=0; i<COM1.RX_Cnt; i++)    {
                        // TODO: RX1_Buffer[i]����ǽ��յ�����
                        // TODO: ��������߼�
                        tmp=RX1_Buffer[i];
                        TX1_write2buff(RX1_Buffer[i]);// дһ��byte
                    }
                }
                COM1.RX_Cnt = 0;
            }
        }
    }
}