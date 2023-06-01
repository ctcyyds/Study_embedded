//#include "config.h"
//#include "GPIO.h"
//#include "delay.h"
//#include "UART.h"
//#include <stdio.h>

//u8 key_state = 0x0f;//Up

//#define IS_KEY_DOWN(n) 		((key_state & (1 << n)) >> n) == 0
//#define IS_KEY_UP(n)			((key_state & (1 << n)) >> n) == 1

//#define SET_KEY_DOWN(n)  	key_state &=~ (1 << n)
//#define SET_KEY_Up(n)			key_state |= (1 << n)

////P51 P52 P53 P54

//void GPIO_config(void) {
//    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
//    GPIO_InitStructure.Mode=GPIO_HighZ;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//    GPIO_InitStructure.Pin=GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//ָ��Ҫ��ʼ����IO
//    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
//}

//void UART_config(void) {
//    COMx_InitDefine        COMx_InitStructure;                    //�ṹ����
//    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;    //ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
//    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;            //ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
//    COMx_InitStructure.UART_BaudRate  = 115200ul;            //������, һ�� 110 ~ 115200
//    COMx_InitStructure.UART_RxEnable  = ENABLE;                //��������,   ENABLE��DISABLE
//    COMx_InitStructure.BaudRateDouble = DISABLE;            //�����ʼӱ�, ENABLE��DISABLE
//    COMx_InitStructure.UART_Interrupt = ENABLE;                //�ж�����,   ENABLE��DISABLE
//    COMx_InitStructure.UART_Priority  = Priority_0;            //ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;    //�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
//    UART_Configuration(UART1, &COMx_InitStructure);        //��ʼ������1 UART1,UART2,UART3,UART4
//}

///char putchar (char dat) {
//    TX1_write2buff(dat);
//    return dat;
//}

///int main() {
//    GPIO_config();
//    UART_config();
//    EA = 1;
//    while(1) {
//        if(P51 && IS_KEY_DOWN(0)) {//������ڵ�ֵΪ1����һ�ε�ֵΪ0
//            //����״̬
//            SET_KEY_Up(0);
//            printf("P51 Up\r\n");
//        } else if(P51 == 0 && IS_KEY_UP(0)) {
//            SET_KEY_DOWN(0);
//            //Down״̬
//            printf("P51 Down\r\n");
//        }
//        //    0000 1 1 1 1
//        //&   0000 0 0 1 0
//        //=   0000 0 0 1 0
//        //>>1 0000 0 0 0 1
//        if(P52 && IS_KEY_DOWN(1)) {//������ڵ�ֵΪ1����һ�ε�ֵΪ0
//            //����״̬
//            SET_KEY_Up(1);
//            printf("P52 Up\r\n");
//        } else if(P52 == 0 && IS_KEY_UP(1)) {
//            SET_KEY_DOWN(1);
//            //Down״̬
//            printf("P52 Down\r\n");
//        }
//				
//				if(P53 && IS_KEY_DOWN(2)) {//������ڵ�ֵΪ1����һ�ε�ֵΪ0
//            //����״̬
//            SET_KEY_Up(2);
//            printf("P53 Up\r\n");
//        } else if(P53 == 0 && IS_KEY_UP(2)) {
//            SET_KEY_DOWN(2);
//            //Down״̬
//            printf("P53 Down\r\n");
//        }
//				
//				if(P54 && IS_KEY_DOWN(3)) {//������ڵ�ֵΪ1����һ�ε�ֵΪ0
//            //����״̬
//            SET_KEY_Up(3);
//            printf("P54 Up\r\n");
//        } else if(P54 == 0 && IS_KEY_UP(3)) {
//            SET_KEY_DOWN(3);
//            //Down״̬
//            printf("P54 Down\r\n");
//        }
//        delay_ms(20);
//    }
//}
#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "UART.h"
#include <stdio.h>
//P51 P52 P53 P54

// ��һ�ε�״ֵ̬: Ĭ��ֵ0x01  0b0000 0001
//  0b 0000 1		 |   1  |    1 |  1
// 					key4 | key3 | key2 | key1
//
// key1
// 0b 0000 1		 |   1  |    1 |  1
// & 0000  0         0       0    1
//>> 0

// key1
// 0b 0000 1		 |   1  |    1 |  0
// |= 0000 0        0        0    1
// 0b 0000 1		 |   1  |    1 |  1


// key1
// 0b 0000 1		 |   1  |    1 |  1
//    0000 0         0       0    1
// ~
// &  1111 1         1       1    0
// 0b 0000 1		 |   1  |    1 |  0


// key2
// 0b 0000 1		 |   1  |    1 |  1
// & 0000  0         0       1    0			0x02 
// >> 1
//   0000  0   0         0       1    ==0x01
//   0000  0         0       1    0	

u8 key_state = 0x0f;//1Ϊup��0Ϊdown

// 0		0x01
// 1		0x02
// 2		0x04
// n		1 << n
#define IS_KEY_DOWN(n)	((key_state & (1 << n)) >> n) == 0
#define IS_KEY_UP(n) 		((key_state & (1 << n)) >> n) == 1

#define SET_KEY_DOWN(n)	 key_state &= ~(1 << n)
#define SET_KEY_UP(n)		 key_state |= (1 << n)

char putchar (char dat) {
	TX1_write2buff(dat);
	return dat;
}

void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_HighZ;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
    COMx_InitStructure.UART_Priority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
}

int main() {
    GPIO_config();
		UART_config();

    EA = 1;

    while(1) {
			if(P51 && IS_KEY_DOWN(0)) {
				// ������ڵ�ֵΪ1(UP),��һ��Ϊ0(Down)
				// ����״̬, key1 ��Ϊ 1
				SET_KEY_UP(0);
				// ���� UP
				printf("P51 UP\r\n");
			} else if(P51 == 0 && IS_KEY_UP(0)){
				// ������ڵ�ֵΪ0(Down),��һ��Ϊ1(Up)
				// ����״̬,  key1 ��Ϊ 0
				SET_KEY_DOWN(0);
				// ���� DOWN
				printf("P51 DOWN\r\n");
			}
			
			if(P52 && IS_KEY_DOWN(1)) {
				// ������ڵ�ֵΪ1(UP),��һ��Ϊ0(Down)
				// ����״̬
				SET_KEY_UP(1);
				// ���� UP
				printf("P52 UP\r\n");
			} else if(P52 == 0 && IS_KEY_UP(1)){
				// ������ڵ�ֵΪ0(Down),��һ��Ϊ1(Up)
				// ����״̬
				SET_KEY_DOWN(1);
				// ���� DOWN
				printf("P52 DOWN\r\n");
			}
			
			if(P53 && IS_KEY_DOWN(2)) {
				// ������ڵ�ֵΪ1(UP),��һ��Ϊ0(Down)
				// ����״̬
				SET_KEY_UP(2);
				// ���� UP
				printf("P53 UP\r\n");
			} else if(P53 == 0 && IS_KEY_UP(2)){
				// ������ڵ�ֵΪ0(Down),��һ��Ϊ1(Up)
				// ����״̬
				SET_KEY_DOWN(2);
				// ���� DOWN
				printf("P53 DOWN\r\n");
			}
			
			if(P54 && IS_KEY_DOWN(3)) {
				// ������ڵ�ֵΪ1(UP),��һ��Ϊ0(Down)
				// ����״̬
				SET_KEY_UP(3);
				// ���� UP
				printf("P54 UP\r\n");
			} else if(P54 == 0 && IS_KEY_UP(3)){
				// ������ڵ�ֵΪ0(Down),��һ��Ϊ1(Up)
				// ����״̬
				SET_KEY_DOWN(3);
				// ���� DOWN
				printf("P54 DOWN\r\n");
			}
			
			delay_ms(20);
    }
}