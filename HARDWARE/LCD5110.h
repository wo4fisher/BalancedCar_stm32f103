#ifndef LCD5110_H
#define LCD5110_H

#include "include.h"

//位操作定义
#define     LCD5110_SCLK        PAout(5)
#define     LCD5110_SDIN        PAout(4)
#define     LCD5110_DC          PAout(3)
#define     LCD5110_CE          PAout(2)
#define     LCD5110_RST         PAout(8)


extern uint8_t font6x8[134][6];
extern uint8_t write_chinese[11][24];
extern uint8_t  AVR_bmp[21*16+14];

//函数声明
//void delay_1us(void);
extern void LCD5110_init(void);
extern void LCD5110_clear(void);
extern void LCD5110_write_byte(uint8_t dat, uint8_t dc);
extern void LCD5110_set_XY(uint8_t X, uint8_t Y);
extern void LCD5110_write_char(uint8_t c);
extern void LCD5110_Write_Char(uint8_t X ,uint8_t Y ,uint8_t c);
extern void LCD5110_Write_Num(uint8_t X ,uint8_t Y ,uint16_t num);

extern void LCD5110_move_chinese_string(uint8_t X, uint8_t Y, uint8_t T);

extern void LCD5110_write_english_string(uint8_t X,uint8_t Y,int8_t *s);
extern void LCD5110_write_chinese_string(uint8_t X, uint8_t Y,
                                  uint8_t ch_with,uint8_t num,
                                  uint8_t line,uint8_t row);
extern void chinese_string(uint8_t X, uint8_t Y, uint8_t T);

extern void LCD5110_draw_bmp_pixel(uint8_t X,uint8_t Y,uint8_t *map,
                            uint8_t Pix_x,uint8_t Pix_y);




#endif /* __LCD5110_H__ */
