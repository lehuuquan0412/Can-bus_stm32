#include "st7735_user_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DB_SIZE 					(10UL * 1024UL)

st7735_info_t st7735_init_info;
st7735_info_t *st7735_addr = &st7735_init_info;

uint8_t bsp_db[DB_SIZE];
uint8_t bsp_wb[DB_SIZE];



int st7735_write(uint8_t MODE, uint8_t *data, uint32_t size)
{
    uint8_t data_to_send[size + 1];
    int ret;
    int fd = open(DEVICE_PATH, O_RDWR);

    if (size < 1)    return -1;
    if (fd < 0)     return fd;

    data_to_send[0] = MODE;

    for (uint32_t i = 0; i < size; i++)
    {
        data_to_send[i+1] = data[i];
    }

    ret = write(fd, (char)data_to_send, size + 1);

    close(fd);
    return ret;
}

int st7735_write_data(uint8_t *data, uint32_t size)
{
    return st7735_write(DATA_MODE, data, size);
}

int st7735_write_cmd(uint8_t cmd)
{
    return st7735_write(CMD_MODE, &cmd, 1);
}

int st7735_bsp_set_display_area(display_area_t area)
{
    uint8_t data_to_send[4];
    int ret;
    if ((area.x1 >= ST7735_C_VALUE)||(area.y1 >= ST7735_R_VALUE)||(area.x0 >= ST7735_C_VALUE)||(area.y0 >= ST7735_R_VALUE))         return -1;
    if ((area.x0 < 0)||(area.y0 < 0))                                   return -1;

    data_to_send[0] = ST7735_CASET;
    ret = st7735_write(CMD_MODE, data_to_send, 1);
    if (ret < 0)            return ret;

    data_to_send[0] = 0;
    data_to_send[1] = area.x0;
    data_to_send[2] = 0;
    data_to_send[3] = area.x1;

    ret = st7735_write(DATA_MODE, data_to_send, 4);
    if (ret < 0)            return ret;

    data_to_send[0] = 0;
    data_to_send[1] = area.y0;
    data_to_send[2] = 0;
    data_to_send[3] = area.y1;

    ret = st7735_write(DATA_MODE, data_to_send, 4);
}

int st7735_bsp_send_cmd_mem_write(void)
{
    uint8_t data_to_send = ST7735_WRITE_RAM;
    return st7735_write(CMD_MODE, &data_to_send, 1);
}

int st7735_bsp_set_background_color(uint16_t COLOR)
{   
    int ret;
    display_area_t area;
    area.x0 = 0;
    area.x1 = ST7735_C_VALUE - 1;
    area.y0 = 0;
    area.y1 = ST7735_R_VALUE - 1;

    return st7735_bsp_fill_rect(COLOR, area);
}

int ls st7735_bsp_fill_rect(uint16_t COLOR, display_area_t area)
{
    int ret;
    uint8_t data_to_send[2];

    ret = st7735_bsp_set_display_area(area);
    if (ret < 0)        return ret;
    
    ret = st7735_bsp_send_cmd_mem_write();
    if (ret < 0)        return ret;

    data_to_send[1] = (~(0xFF00))&(COLOR);
	data_to_send[0] = ((~(0x00FF))&(COLOR)) >> 8;

    for (uint32_t i = 0; i < (area.x1 - area.x0 + 1)*(area.y1 - area.y0 + 1); i++)
    {
        ret = st7735_write(DATA_MODE, data_to_send, 2);
        if (ret < 0)    return ret;
    }

    return ret;
}

void st7735_init(void)
{
    st7735_write_cmd(ST7735_SW_RESET);
    for(uint32_t i = 0 ; i<(0xFFFFU);i++);
    st7735_write_cmd(ST7735_SLEEP_OUT);
    for (uint32_t i = 0; i < (0xFFFFU); i++);

    st7735_write_cmd(ST7735_FRAME_RATE_CTRL1);
    uint8_t params[16];
    params[0] = 0x01;
    params[1] = 0x2C;
    params[2] = 0x2D;
    st7735_write_data(params, 3);

    st7735_write_cmd(ST7735_FRAME_RATE_CTRL2);
    st7735_write_data(params, 3);

    st7735_write_cmd(ST7735_FRAME_RATE_CTRL3);
    st7735_write_data(params, 3);
    st7735_write_data(params, 3);

    st7735_write_cmd(ST7735_FRAME_INVERSION_CTRL);
    params[0] = 0x07;
    st7735_write_data(params, 1);

    st7735_write_cmd(ST7735_PWR_CTRL1);
    params[0] = 0xA2;
    params[1] = 0x02;
    params[2] = 0x84;
    st7735_write_data(params, 3);

    st7735_write_cmd(ST7735_PWR_CTRL2);
    params[0] = 0xC5;
    st7735_write_data(params, 1);

    st7735_write_cmd(ST7735_PWR_CTRL3);
    params[0] = 0x0A;
    params[1] = 0x00;
    st7735_write_data(params, 2);

    st7735_write_cmd(ST7735_PWR_CTRL4);
    params[0] = 0x8A;
    params[1] = 0x2A;
    st7735_write_data(params, 2);

    st7735_write_cmd(ST7735_PWR_CTRL5);
    params[1] = 0xEE;
    st7735_write_data(params, 2);

    st7735_write_cmd(ST7735_VCOMH_VCOML_CTRL1);
    params[0] = 0x0E;
    st7735_write_data(params, 1);

    st7735_write_cmd(ST7735_DISPLAY_INVERSION_OFF);

    st7735_write_cmd(ST7735_MADCTL);
    params[0] = 0xA0;
    st7735_write_data(params, 1);

    st7735_write_cmd(ST7735_COLOR_MODE);
    params[0] = 0x05;
    st7735_write_data(params, 1);

    st7735_write_cmd(ST7735_CASET);
    params[0] = 0;
    params[1] = 0;
    params[2] = 0;
    params[3] = 160;
    st7735_write_data(params, 4);

    st7735_write_cmd(ST7735_RASET);
    params[3] = 128;
    st7735_write_data(params, 4);

    st7735_write_cmd(ST7735_PV_GAMMA_CTRL);
    params[0] = 0x02;
    params[1] = 0x1C;
    params[2] = 0x07;
    params[3] = 0x12;
    params[4] = 0x37;
    params[5] = 0x32;
    params[6] = 0x29;
    params[7] = 0x2D;
    params[8] = 0x29;
    params[9] = 0x25;
    params[10] = 0x2B;
    params[11] = 0x39;
    params[12] = 0x00;
    params[13] = 0x01;
    params[14] = 0x03;
    params[15] = 0x10;
    st7735_write_data(params, 16);

    st7735_write_cmd(ST7735_NV_GAMMA_CTRL);
    params[0] = 0x03;
    params[1] = 0x1D;
    params[2] = 0x07;
    params[3] = 0x06;
    params[4] = 0x2E;
    params[5] = 0x2C;
    params[6] = 0x29;
    params[7] = 0x2D;
    params[8] = 0x2E;
    params[9] = 0x2E;
    params[10] = 0x37;
    params[11] = 0x3F;
    params[12] = 0x00;
    params[13] = 0x00;
    params[14] = 0x02;
    params[15] = 0x10;
    st7735_write_data(params, 16);

    st7735_write_cmd(ST7735_NORMAL_DISPLAY_OFF);
    for (uint32_t i = 0; i < (0xFFFFU*2); i++);
    st7735_write_cmd(ST7735_DISPLAY_ON);
}

void st7735_bsp_init(void)
{
    st7735_addr->st7735_display_area.x0 = 0;
    st7735_addr->st7735_display_area.x1 = ST7735_C_VALUE - 1;
    st7735_addr->st7735_display_area.y0 = 0;
    st7735_addr->st7735_display_area.y1 = ST7735_R_VALUE - 1;

    st7735_init();
    st7735_bsp_set_display_area(st7735_addr->st7735_display_area);
    st7735_bsp_buffer_init(st7735_addr);
}

void st7735_bsp_buffer_init(st7735_info_t *st7735_info)
{
    st7735_info->draw_buff_1 = bsp_db;
    st7735_info->draw_buff_2 = bsp_wb;
}

void *st7735_bsp_get_draw_buffer1_addr(void)
{
    return (void*)st7735_addr->draw_buff_1;
}
void *st7735_bsp_get_draw_buffer2_addr(void)
{
	return (void*)st7735_addr->draw_buff_2;
}
