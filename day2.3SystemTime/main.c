/*P53 �ߵͱ仯*/
#include "config.h"
#include "GPIO.h"
/*
IO��ʼ��
*/
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_3;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}
int main() {
    GPIO_config();
    while(1) {
        P53 =! P53;
        NOP1();
    }
}