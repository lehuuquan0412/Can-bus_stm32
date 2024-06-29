#ifndef ST7735_USER_LIB_H__
#define ST7735_USER_LIB_H__

#include "st7735.h"
#include <stdio.h>
#include <stdint.h>


#define DEVICE_PATH                 "/dev/st7735"

#define CMD_MODE                    SPI_SEND_CMD
#define DATA_MODE                   SPI_SEND_DATA

#define BLACK 							0x0000
#define WHITE 							0xFFFF
#define RED 							0xF800
#define GREEN 							0x07E0
#define BLUE 							0x001F
#define CYAN 							0x07FF
#define MAGENTA 						0xF81F
#define YELLOW 							0xFFE0
#define ORANGE 							0xFC00

typedef struct
{
    uint8_t x0;
    uint8_t x1;
    uint8_t y0;
    uint8_t y1;
}display_area_t;

typedef struct
{
    display_area_t st7735_display_area;
    uint8_t *draw_buff_1;
    uint8_t *draw_buff_2;
}st7735_info_t;


int st7735_write(uint8_t MODE, uint8_t *data, uint32_t size);

int st7735_write_data(uint8_t *data, uint32_t size);
int st7735_write_cmd(uint8_t cmd);

int st7735_bsp_set_display_area(display_area_t area);
int st7735_bsp_send_cmd_mem_write(void);
int st7735_bsp_set_background_color(uint16_t COLOR);
int st7735_bsp_fill_rect(uint16_t COLOR, display_area_t area);
void st7735_init(void);
void st7735_bsp_init(void);

void st7735_bsp_buffer_init(st7735_info_t *st7735_info);

void *st7735_bsp_get_draw_buffer1_addr(void);
void *st7735_bsp_get_draw_buffer2_addr(void);
#endif
