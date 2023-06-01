#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "ADC.h"
#include "UART.h"
#include "stdio.h"
#include "NTC.h"

void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_0 | GPIO_Pin_1;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//��ʼ��
}

void ADC_config(void)
{
    ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����
    ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
    ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
    ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
    ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
    ADC_InitStructure.ADC_Power     = ENABLE;				//ADC��������/�ر�	ENABLE,DISABLE
    ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
    ADC_InitStructure.ADC_Priority    = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    ADC_InitStructure.ADC_Interrupt = DISABLE;			//�ж�����	ENABLE,DISABLE
    ADC_Inilize(&ADC_InitStructure);					//��ʼ��
    ADC_PowerControl(ENABLE);							//������ADC��Դ��������, ENABLE��DISABLE
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

char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

int main() {
	int t;
    GPIO_config();
    UART_config();
		ADC_config();
		//��ʼ������
		NTC_init();
    EA = 1;
    while(1) {
				//��ȡ�¶ȣ����÷���
				t = NTC_get_temperature();
				
        printf("%d\r\n",t);

        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
    }
}