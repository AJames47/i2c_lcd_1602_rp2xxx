#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd1602I2C.h"

#define I2C_PORTc i2c0
#define SDA_PIN 4
#define SCL_PIN 5

#define LCD_ADDRc 0x27

/* LCD control bits
#define LCD_RS 0x01
#define LCD_EN 0x04
#define LCD_BL 0x08

void lcd_send_byte(uint8_t val)
{
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &val, 1, false);
}

void lcd_toggle_enable(uint8_t val)
{
    sleep_us(1);

    lcd_send_byte(val | LCD_EN);
    sleep_us(1);

    lcd_send_byte(val & ~LCD_EN);
    sleep_us(50);
}

void lcd_send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = 0;

    data = (nibble & 0xF0);
    data |= mode;
    data |= LCD_BL;

    lcd_send_byte(data);
    lcd_toggle_enable(data);
}

void lcd_send_cmd(uint8_t cmd)
{
    lcd_send_nibble(cmd & 0xF0, 0);
    lcd_send_nibble((cmd << 4) & 0xF0, 0);
}

void lcd_send_data(uint8_t data)
{
    lcd_send_nibble(data & 0xF0, LCD_RS);
    lcd_send_nibble((data << 4) & 0xF0, LCD_RS);
}

void lcd_clear()
{
    lcd_send_cmd(0x01);
    sleep_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr;

    if(row == 0)
        addr = 0x80 + col;
    else
        addr = 0xC0 + col;

    lcd_send_cmd(addr);
}

void lcd_print(const char *str)
{
    while(*str)
    {
        lcd_send_data(*str++);
    }
}

void lcd_init()
{
    sleep_ms(50);

    // Initialize 4-bit mode
    lcd_send_nibble(0x30, 0);
    sleep_ms(5);

    lcd_send_nibble(0x30, 0);
    sleep_us(150);

    lcd_send_nibble(0x30, 0);
    sleep_us(150);

    lcd_send_nibble(0x20, 0);

    // Function set
    lcd_send_cmd(0x28);

    // Display ON
    lcd_send_cmd(0x0C);

    // Entry mode
    lcd_send_cmd(0x06);

    lcd_clear();
}*/

int main()
{
    stdio_init_all();
    int count = 0;
    char countd[1];

    // I2C init
    i2c_init(I2C_PORTc, 100 * 1000);

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    lcd_init(I2C_PORTc,LCD_ADDRc);

    lcd_set_cursor(0,0);
    lcd_print("test lcd");

    lcd_set_cursor(1,0);
    lcd_print("RP2040 LCD");

    sleep_ms(2000);

    while (1)
    {

        lcd_set_cursor(1,0);
        lcd_print("                ");
        lcd_set_cursor(1,0);
        sprintf(countd,"%d",count++);
        lcd_print(countd);
        sleep_ms(1000);
    }
}