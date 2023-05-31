#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "UART.h"
#include "timer.h"

/*
��ʼ��P30 P31 P53 P52
*/
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_0 | GPIO_Pin_1;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_2 | GPIO_Pin_3;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}
//���ڳ�ʼ��
void UART_config(void) {
    COMx_InitDefine        COMx_InitStructure;                    //�ṹ����
    /*����1��ʼ��*/
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

void TIMER_config(void) {
    TIM_InitTypeDef        TIM_InitStructure;                        //�ṹ����
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;    //ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
    TIM_InitStructure.TIM_Priority    = Priority_0;            //ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    TIM_InitStructure.TIM_Interrupt = ENABLE;                    //�ж��Ƿ�����,   ENABLE��DISABLE
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;        //ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    TIM_InitStructure.TIM_ClkOut    = DISABLE;                //�Ƿ������������, ENABLE��DISABLE
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 100000UL);        //��ֵ,
    TIM_InitStructure.TIM_Run       = ENABLE;                    //�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
    Timer_Inilize(Timer0,&TIM_InitStructure);                    //��ʼ��Timer0      Timer0,Timer1,Timer2,Timer3,Timer4
}

int main() {
    u8 i;
    GPIO_config();
    UART_config();
    TIMER_config();
    //�ж��ܿ���
    EA=1;
    while(1) {
        delay_ms(10);
        //���մ�������
        if(COM1.RX_TimeOut > 0)        //��ʱ����
        {
            if(--COM1.RX_TimeOut == 0)
            {
                if(COM1.RX_Cnt > 0)
                {
                    for(i=0; i<COM1.RX_Cnt; i++)    {
                        // TODO: RX1_Buffer[i]����ǽ��յ�����
                        // TODO: ��������߼�
                        //����1���յ�����ͨ������4���ͳ�ȥ
                        //TX4_write2buff(RX1_Buffer[i]);
                    }
                }
                COM1.RX_Cnt = 0;
            }
        }
    }
}