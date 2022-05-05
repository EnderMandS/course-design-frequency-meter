//
// Created by M on 2022/04/29.
//

#ifndef FRECNT_CLION_LCD_H
#define FRECNT_CLION_LCD_H

#include "stm32f4xx.h"
#include "stdbool.h"

typedef struct
{
  uint16_t width;
  uint16_t height;
  uint16_t id;
  uint8_t dir;
  uint16_t	wramcmd;
  uint16_t setxcmd;
  uint16_t setycmd;
}_lcd_dev;
//LCD参数
extern _lcd_dev lcddev;
//LCD画笔颜色和背景色
extern uint32_t POINT_COLOR;
extern uint32_t BACK_COLOR;

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define	LCD_LED PBout(15)
//LCD Address struct
typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} LCD_TypeDef;
#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//scan direction
#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3
#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7
//default scan direction
#define DFT_SCAN_DIR  L2R_U2D

#define WHITE      0xFFFF
#define BLACK      0x0000
#define BLUE       0x001F
#define BRED       0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED        0xF800
#define MAGENTA    0xF81F
#define GREEN      0x07E0
#define CYAN       0x7FFF
#define YELLOW     0xFFE0
#define BROWN 		 0XBC40
#define BRRED 		 0XFC07
#define GRAY  		 0X8430
#define DARKBLUE   0X01CF
#define LIGHTBLUE  0X7D7C
#define GRAYBLUE   0X5458
#define LIGHTGREEN 0X841F
#define LGRAY 		 0XC618
#define LGRAYBLUE  0XA651
#define LBBLUE     0X2B12

//LCD分辨率
#define SSD_HOR_RESOLUTION		800
#define SSD_VER_RESOLUTION		480
//LCD驱动参数
#define SSD_HOR_PULSE_WIDTH		1
#define SSD_HOR_BACK_PORCH		46
#define SSD_HOR_FRONT_PORCH		210
#define SSD_VER_PULSE_WIDTH		1
#define SSD_VER_BACK_PORCH		23
#define SSD_VER_FRONT_PORCH		22
//参数计算宏
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

void freDisplay(void);
void cycleDisplay(void);

#endif //FRECNT_CLION_LCD_H

