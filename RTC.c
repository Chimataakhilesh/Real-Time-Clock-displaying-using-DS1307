#include <LPC21XX.H>

typedef unsigned char u8;
typedef unsigned int  u32;

#include "lcd_header.h"
#include "I2C_header.h"

#define RTC_SLAVE_ADDR 0x68

u8 BCD_to_Decimal(u8 bcd);
u8 rtc_read(u8 reg_addr);
void LCD_integer(u8 d);

int main() {
    u8 sec, min, hour; // To track changes

    I2C_INIT();
    LCD_INIT();
		while(1)
		{
			sec = BCD_to_Decimal(rtc_read(0x00));
			min = BCD_to_Decimal(rtc_read(0x01));
			hour = BCD_to_Decimal(rtc_read(0x02));
			
			
			LCD_COMMAND(0x80);
			LCD_integer(hour);
			LCD_DATA(':');
			LCD_integer(min);
			LCD_DATA(':');
			LCD_integer(sec);
			
		}
}
u8 rtc_read(u8 reg_addr)
{
    u8 data;

    I2C_Start();             
    I2C_Write(RTC_SLAVE_ADDR << 1);      
    I2C_Write(reg_addr);     

    I2C_Restart();           
    I2C_Write((RTC_SLAVE_ADDR << 1) | 1); 

    data = I2C_Nack();       
    I2C_Stop();

    return data;
}
void LCD_integer(u8 d) {

    if(d < 10) {
        LCD_DATA('0');
        LCD_DATA(d + '0');
    } 
		else {
        LCD_DATA((d / 10) + '0');
        LCD_DATA((d % 10) + '0');
    }
}
u8 BCD_to_Decimal(u8 bcd)
{
    return ((bcd / 16) * 10) + (bcd % 16);
}
