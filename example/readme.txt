The main code is within the lcd_test.c file,
Refer to the file to see how the lib is used,

lcd_init has to be called before using any function within the lib; pass the i2c used, i.e., i2c0/i2c1, along with the LCD i2c address.
