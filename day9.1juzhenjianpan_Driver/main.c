#include "config.h"
#include "GPIO.h"
#include "UART.h"
#include "delay.h"
#include <stdio.h>
#include "MatrixKeys.h"

char putchar(char dat)
{
    TX1_write2buff(dat);
    return dat;
}

// GPIO��ʼ��
void GPIO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; // �ṹ����
    // P34 P35
    GPIO_InitStructure.Mode = GPIO_PullUp;            // IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_4 | GPIO_Pin_5; // ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);       // ��ʼ��
    // P40 P41
    GPIO_InitStructure.Mode = GPIO_PullUp;            // IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1; // ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);       // ��ʼ��
    // P03 P06 P07
    GPIO_InitStructure.Mode = GPIO_PullUp;                         // IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7; // ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);                    // ��ʼ��
    // P17
    GPIO_InitStructure.Mode = GPIO_PullUp;      // IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_7;        // ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure); // ��ʼ��
}

// UART��ʼ��
void UART_config(void)
{
    COMx_InitDefine COMx_InitStructure;              // �ṹ����
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;   // ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate = 115200ul;     // ������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable = ENABLE;       // ��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;     // �����ʼӱ�, ENABLE��DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;      // �ж�����,   ENABLE��DISABLE
    COMx_InitStructure.UART_Priority = Priority_0;   // ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31; // �л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);  // ��ʼ������1 UART1,UART2,UART3,UART4
}

void MK_on_keyup(u8 row, u8 col)
{
    printf("Up %d�� %d��\r\n", (int)row, (int)col); // ��ţ̌���ƽΪ��
}

void MK_on_keydown(u8 row, u8 col)
{
    printf("Down %d�� %d��\r\n", (int)row, (int)col); // ��ť���µ�ƽΪ��
}

int main()
{
		u16 state;
    GPIO_config();
    UART_config();
    MK_init();
    EA = 1;
    while (1)
    {
        delay_ms(20);
        MK_scan(&state);
    }
}