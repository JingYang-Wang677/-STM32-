/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef _HC_SR04_H_
#define _HC_SR04_H_

/**********************************
包含头文件
**********************************/
#include "sys.h" 


/**********************************
PIN口定义
**********************************/
#define HCSR04_ECHO_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//ECHO引脚
#define HCSR04_ECHO_PORT                 GPIOB
#define HCSR04_ECHO_PIN                  GPIO_Pin_10
#define HCSR04_ECHO  										 PBin(10)

#define HCSR04_TRIG_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//TRIG引脚
#define HCSR04_TRIG_PORT                 GPIOB
#define HCSR04_TRIG_PIN                  GPIO_Pin_11
#define HCSR04_TRIG  										 PBout(11)


/**********************************
函数声明
**********************************/
void HC_SR04_Init(void);																						//HC_SR04初始化函数
uint16_t Hcsr04_GetDistance(uint16_t Hcsr04_temp);									//获取距离值函数


#endif

