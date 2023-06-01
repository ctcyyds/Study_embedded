#include "PCF8563.h"
#include <stdio.h>


void PCF8563_init() {
}

//��ʱ��
//дʱ��
//��ȡʱ�䣺����������ʱ����
void PCF8563_set_clock(Clock_t c) {
    u8 p[7];
    u8 x;
    // second
    p[0] = (c.second % 10) + ((c.second / 10) << 4);
    // minute
    p[1] = (c.minute % 10) + ((c.minute / 10) << 4);
    // hour
    p[2] = (c.hour % 10) + ((c.hour / 10) << 4);
    // day
    p[3] = (c.day % 10) + ((c.day / 10) << 4);
    // weekday
    p[4] = c.weekday;
    // month
    x = c.year >= 2000 ? 1 : 0;
    p[5] = (c.month % 10) + ((c.month / 10) << 4) + (x << 7);
    // year
    p[6] = (c.year % 10) + ((c.year % 100 / 10) << 4);

    I2C_WRITE(PCF8563_ADDR, PCF8563_REG_TD, p, 7);
}

void PCF8563_get_clock(Clock_t *c) {
    u8 p[7];
    u8 x;
    // addr���Ĵ�����ַ
    //ReadNbyte(addr, p, number);
    I2C_READ(PCF8563_ADDR, PCF8563_REG_TD, p, 7);

    // second			��λ					ʮλ
    //second = (p[0] & 0x0F) + ((p[0] & 0x70) >> 4) * 10;
    c->second = (p[0] & 0x0F) + ((p[0] >> 4) & 0x07) * 10;

    // minute
    c->minute = (p[1] & 0x0F) + ((p[1] >> 4) & 0x07) * 10;

    // hour
    c->hour = (p[2] & 0x0F) + ((p[2] >> 4) & 0x03) * 10;

    // day
    c->day = (p[3] & 0x0F) + ((p[3] >> 4) & 0x03) * 10;

    // weekday
    c->weekday = p[4] & 0x07;

    // month
    c->month = (p[5] & 0x0F) + ((p[5] >> 4) & 0x01) * 10;
    x = p[5] >> 7;

    // year
    c->year = (p[6] & 0x0F) + (p[6] >> 4) * 10 + (x == 0 ? 1900 : 2000);
}

void PCF8563_enable_alarm() {
    u8 p;
    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);
    p |= 0x02;// ���� alarm IE
    p |= 0x10;// TI_PI
    p &= ~0x08;// ���� alarm flag
    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);

    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);
    printf("alarm: %d\r\n", (int)p);
}

void PCF8563_set_alarm(Alarm_t a) {
    u8 tmp[4];
    // ����alarm�� minute��hour��day�� weekday
    // minute		��λ		ʮλ			enable(0x80 �رգ�0����)
    tmp[0] = (a.minute % 10) + ((a.minute / 10) << 4) + ((a.enable_minute == 1) ? 0: 0x80);

    // hour		��λ		ʮλ			enable(0x80 �رգ�0����)
    tmp[1] = (a.hour % 10) + ((a.hour / 10) << 4) + ((a.enable_hour == 1) ? 0: 0x80);

    // day		��λ		ʮλ			enable(0x80 �رգ�0����)
    tmp[2] = (a.day % 10) + ((a.day / 10) << 4) + ((a.enable_day == 1) ? 0: 0x80);

    // weekday		��λ		ʮλ			enable(0x80 �رգ�0����)
    tmp[3] = a.weekday + ((a.enable_weekday == 1) ? 0: 0x80);
    I2C_WriteNbyte(0x51, 0x09, &tmp, 4);
}


void PCF8563_get_alarm(Alarm_t *a) {

}

void PCF8563_disable_alarm() {
    u8 p;
    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);
    p &= ~0x02;// �ر� alarm IE
    p &= ~0x08;// ���� alarm flag
    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);
}

void PCF8563_enable_timer() {
    u8 p;
    I2C_ReadNbyte(0x51, 0x01, &p, 1);
    p |= 0x01;// ���� timer IE
    p |= 0x10;
    p &= ~0x04;// ���� timer flag
    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);

    // timerλ��enable����
    I2C_ReadNbyte(0x51, 0x0E, &p, 1);
    p |= 0x80;
    I2C_WriteNbyte(0x51, 0x0E, &p, 1);

    I2C_ReadNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);
    printf("timer: %d\r\n", (int)p);
}
void PCF8563_set_timer(Timer_t t) {
    u8 p;
    I2C_ReadNbyte(0x51, 0x0E, &p, 1);
    p |= t.src_clk;//timer source clock frequency, enable
    I2C_WriteNbyte(0x51, 0x0E, &p, 1);

    p = t.countdown;// countdown period in seconds
    I2C_WriteNbyte(0x51, 0x0F, &p, 1);
}
void PCF8563_get_timer(Timer_t *t) {
}
void PCF8563_disable_timer() {
    u8 p;
    I2C_ReadNbyte(0x51, 0x01, &p, 1);
    p &= ~0x01;// �ر� timer IE
    p &= ~0x04;// ���� timer flag
    I2C_WriteNbyte(PCF8563_ADDR, PCF8563_REG_CS2, &p, 1);

    // timerλ��disable
    I2C_ReadNbyte(0x51, 0x0E, &p, 1);
    p &= ~0x80;
    I2C_WriteNbyte(0x51, 0x0E, &p, 1);
}

void  Ext_int3_call() {
    // alarm �ص�
    u8 p;
    // �����߼����̶���
    // ��ȡ��ǰ ���ƼĴ�����ֵ
    I2C_ReadNbyte(0x51, 0x01, &p, 1);
    printf("call: %d \r\n", (int)p);

#ifdef PCF8563_ENABLE_ALARM

    // ���ʱAlarm�������жϣ���ȥ����alarm��flag
    if(p & 0x08) {
        // ����Alarm Flag
        p &= ~0x08;// ����flag״̬
        I2C_WriteNbyte(0x51, 0x01, &p, 1);

        // �û��߼����ǹ̶��ģ���ҵ�����
        //printf("alarm \r\n");
        PCF8563_on_alarm();
    }

#endif

#ifdef PCF8563_ENABLE_TIMER
    // �����timer�������жϣ���ȥ����alarm��flag
    if(p & 0x04) {
        // timer �Ļص�
        // ����timer Flag
        p &= ~0x04;// ����flag״̬
        I2C_WriteNbyte(0x51, 0x01, &p, 1);

        I2C_ReadNbyte(0x51, 0x0F, &p, 1);
        printf("cnt: %d \r\n", (int)p);

        PCF8563_on_timer();
    }
#endif



}