#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st7735_user_lib.h"


int main(int argc, char const *argv[])
{
    int number;
    int ret;

    if ((argc > 3))
    {
        printf("Wrong command. Please enter: <./st7735 help> for more information");
        return 0;
    }

    if (strcmp(argv[1], "help") == 0)
    {
        printf("ST7735:\n");
        printf("<1 /color/> : set background color.\n");
        printf("<2 /number of picture(1 -> 4)/> : display picture 1-4.\n");
        return 0;
    } 

    number = atoi(argv[1]);

    if (number == 1)
    {
        if (strcmp(strupr(argv[2]), "RED") == 0)
        {
            ret = st7735_bsp_set_background_color(RED);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "GREEN") == 0)
        {
            ret = st7735_bsp_set_background_color(GREEN);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "BLUE") == 0)
        {
            ret = st7735_bsp_set_background_color(BLUE);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "CYAN") == 0)
        {
            ret = st7735_bsp_set_background_color(CYAN);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "WHITE") == 0)
        {
            ret = st7735_bsp_set_background_color(WHITE);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "MAGENTA") == 0)
        {
            ret = st7735_bsp_set_background_color(MAGENTA);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "YELLOW") == 0)
        {
            ret = st7735_bsp_set_background_color(YELLOW);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else if (strcmp(strupr(argv[2]), "ORANGE") == 0)
        {
            ret = st7735_bsp_set_background_color(ORANGE);
            if (ret < 0)        printf("Set color background fail !!!\n");
            return 0;
        }else {
            printf("Wrong color. Please enter: <./st7735 help> for more information\n");
            return 0;
        }
    }

    return 0;
}