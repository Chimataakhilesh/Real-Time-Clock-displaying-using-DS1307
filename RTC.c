#include <LPC21XX.H>   // LPC21xx microcontroller header

typedef unsigned char u8;   // 8-bit unsigned
typedef unsigned int  u32;  // 32-bit unsigned

#include "lcd_header.h"     // LCD functions
#include "I2C_header.h"     // I2C functions

#define RTC_SLAVE_ADDR 0x68 // RTC device address

u8 BCD_to_Decimal(u8 bcd);  // Function to convert BCD to decimal
u8 rtc_read(u8 reg_addr);   // Function to read RTC register
void LCD_integer(u8 d);     // Function to display integer on LCD

int main() 
{
    u8 sec, min, hour; // Variables to store time

    I2C_INIT();   // Initialize I2C
    LCD_INIT();   // Initialize LCD

    while(1)
    {
        // Read seconds, minutes and hours from RTC
        sec  = BCD_to_Decimal(rtc_read(0x00));
        min  = BCD_to_Decimal(rtc_read(0x01));
        hour = BCD_to_Decimal(rtc_read(0x02));

        // Display time on LCD
        LCD_COMMAND(0x80);   // Move cursor to first position
        LCD_integer(hour);   // Display hour
        LCD_DATA(':');       // Print :
        LCD_integer(min);    // Display minute
        LCD_DATA(':');       // Print :
        LCD_integer(sec);    // Display second
    }
}

// Function to read data from RTC
u8 rtc_read(u8 reg_addr)
{
    u8 data;

    I2C_Start();                         // Start I2C communication
    I2C_Write(RTC_SLAVE_ADDR << 1);      // Send RTC address (write mode)
    I2C_Write(reg_addr);                 // Send register address

    I2C_Restart();                       // Restart I2C
    I2C_Write((RTC_SLAVE_ADDR << 1) | 1);// Send RTC address (read mode)

    data = I2C_Nack();                   // Read data from RTC
    I2C_Stop();                          // Stop I2C

    return data;                         // Return received data
}

// Function to display number on LCD
void LCD_integer(u8 d) 
{
    if(d < 10) 
    {
        LCD_DATA('0');        // Print leading zero
        LCD_DATA(d + '0');    // Print digit
    } 
    else 
    {
        LCD_DATA((d / 10) + '0'); // Print tens digit
        LCD_DATA((d % 10) + '0'); // Print ones digit
    }
}

// Convert BCD value to decimal
u8 BCD_to_Decimal(u8 bcd)
{
    return ((bcd / 16) * 10) + (bcd % 16);
}
