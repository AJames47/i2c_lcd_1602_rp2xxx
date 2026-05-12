#include "lcd1602I2C.h"

i2c_inst_t *I2C_PORT;
uint8_t LCD_ADDR;

void lcd_init(i2c_inst_t *port_n, int lcd_add)
{
    I2C_PORT = port_n;
    LCD_ADDR = lcd_add;

    sleep_ms(50);

    // Reset sequence
    lcd_send_nibble(0x30, 0);
    sleep_ms(5);

    lcd_send_nibble(0x30, 0);
    sleep_us(150);

    lcd_send_nibble(0x30, 0);
    sleep_us(150);

    // Set 4-bit mode
    lcd_send_nibble(0x20, 0);
    sleep_ms(5);

    // Function set: 4-bit, 2-line, 5x8
    lcd_send_cmd(0x28);

    // Display ON, cursor OFF
    lcd_send_cmd(0x0C);

    // Entry mode
    lcd_send_cmd(0x06);

    // Clear display
    lcd_clear();

    sleep_ms(5);
}

void lcd_send_byte(uint8_t data)
{
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &data, 1, false);
}

void lcd_toggle_enable(uint8_t data)
{
    sleep_us(5);

    lcd_send_byte(data | LCD_EN);
    sleep_us(5);

    lcd_send_byte(data & ~LCD_EN);
    sleep_us(100);
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

    sleep_us(50);
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