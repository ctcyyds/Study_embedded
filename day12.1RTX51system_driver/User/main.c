#include "UART.h"
#include "config.h"
#include "GPIO.h"
#include "MatrixKeys.h"
#include <stdio.h>

void GPIO_config(void) {

}

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

void All_init() {
    GPIO_config();
    UART_config();
    MK_init();
    EA = 1;
}

char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}


void MK_on_keyup(u8 row, u8 col) {
    printf("%d�У�%d�� UP\r\n",(int)row,(int)col);
}
void MK_on_keydown(u8 row, u8 col) {
    printf("%d�У�%d�� Down\r\n",(int)row,(int)col);
}


//�����ҵĳ������
void start() _task_ 0{
    All_init();

    os_create_task(1);
    os_create_task(2);
    os_delete_task(0);
}
void task1() _task_ 1{
    while(1) {
        u16 state;
        MK_scan(&state);
        os_wait2(K_TMO,4);
    }
}

void task2() _task_ 2{
    while(1) {

    }
}