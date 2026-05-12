#ifndef LCD1602I2C_H
#define LCD1602I2C_H


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

extern i2c_inst_t *I2C_PORT;
extern uint8_t LCD_ADDR;

#define LCD_RS 0x01
#define LCD_EN 0x04
#define LCD_BL 0x08

void lcd_init(i2c_inst_t *port_n, int lcd_add);
void lcd_send_byte(uint8_t data);
void lcd_toggle_enable(uint8_t data);
void lcd_send_nibble(uint8_t nibble, uint8_t mode);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_clear();
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);

#endif