/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LEDS_GPIO_PORT                GPIOC        	//最小系统LED
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)


#define RELAY_JH_GPIO_CLK             RCC_APB2Periph_GPIOB				//灯  继电器引脚
#define RELAY_JH_PORT                 GPIOB
#define RELAY_JH_PIN                  GPIO_Pin_13
#define LED														PBout(13)

#define FS_GPIO_CLK                 RCC_APB2Periph_GPIOA				//风扇控制引脚
#define FS_PORT                     GPIOA
#define FS_PIN                      GPIO_Pin_1
#define FS 									    		PAout(1)

/**********************************
函数声明
**********************************/
void Gpio_Init(void);																//GPIO初始化


#endif

