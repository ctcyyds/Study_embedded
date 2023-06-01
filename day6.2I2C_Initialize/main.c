#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "I2C.h"

// ���ų�ʼ��
// P32 P33 GPIO_OUT_OD
void GPIO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;              // �ṹ����
    GPIO_InitStructure.Mode = GPIO_OUT_OD;            // IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_2; // ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);       // ��ʼ��
}

// I2C����
void I2C_config(void)
{
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master; // ����ѡ��   I2C_Mode_Master, I2C_Mode_Slave
    I2C_InitStructure.I2C_Enable = ENABLE;        // I2C����ʹ��,   ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_WDTA = DISABLE;      // ����ʹ���Զ�����,  ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_Interrupt = DISABLE; // ʹ������ģʽ�ж�,  ENABLE, DISABLE
    I2C_InitStructure.I2C_Speed = 13;             // �����ٶ�=Fosc/2/(Speed*2+4),      0~63
    I2C_InitStructure.I2C_IoUse = I2C_P33_P32;    // IO���л�   I2C_P14_P15, I2C_P24_P25, I2C_P33_P32

    I2C_Init(&I2C_InitStructure);
}

int main()
{
    u8 number;
    u8 p[2];
    u8 addr;
    u8 reg;
    EA = 1;
    GPIO_config();
    I2C_config();
    /**
     * ���豸��������ַ
     * 1.�豸��ַ 0xA2
     * 1.1����ַ0xA3  1��
     * 1.2д��ַ0XA2  0д
     * 2.�Ĵ�����ַ
     */
    while (1)
    {
        // �����addrΪ�Ĵ�����ַ
        // ReadNbyte(addr, p, 2);
        addr = 0x51;
        reg = 0x02;
        number = 1;
        I2C_ReadNbyte(addr, reg, p, 1);
        P[0];
        P[1];
    }
}
