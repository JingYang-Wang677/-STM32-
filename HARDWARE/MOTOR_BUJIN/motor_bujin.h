/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef __MOTOR_BUJIN_H__
#define __MOTOR_BUJIN_H__


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
PIN口定义
**********************************/
#define MOTOR_IN1_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOA				//步进电机引脚
#define MOTOR_IN1_PORT              GPIOA
#define MOTOR_IN1_PIN               GPIO_Pin_4
#define MOTOR_IN1 									PAout(4)

#define MOTOR_IN2_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOA				//步进电机引脚
#define MOTOR_IN2_PORT              GPIOA
#define MOTOR_IN2_PIN               GPIO_Pin_5
#define MOTOR_IN2 									PAout(5)

#define MOTOR_IN3_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOA				//步进电机引脚
#define MOTOR_IN3_PORT              GPIOA
#define MOTOR_IN3_PIN               GPIO_Pin_6
#define MOTOR_IN3 									PAout(6)

#define MOTOR_IN4_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOA				//步进电机引脚
#define MOTOR_IN4_PORT              GPIOA
#define MOTOR_IN4_PIN               GPIO_Pin_7
#define MOTOR_IN4 									PAout(7)


#define MOTOR_IN11_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOB				//步进电机引脚
#define MOTOR_IN11_PORT              GPIOB
#define MOTOR_IN11_PIN               GPIO_Pin_11
#define MOTOR_IN11 									PBout(11)

#define MOTOR_IN12_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOB				//步进电机引脚
#define MOTOR_IN12_PORT              GPIOB
#define MOTOR_IN12_PIN               GPIO_Pin_10
#define MOTOR_IN12 									PBout(10)

#define MOTOR_IN13_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOB				//步进电机引脚
#define MOTOR_IN13_PORT              GPIOB
#define MOTOR_IN13_PIN               GPIO_Pin_1
#define MOTOR_IN13 									PBout(1)

#define MOTOR_IN14_GPIO_CLK_ENABLE   RCC_APB2Periph_GPIOB				//步进电机引脚
#define MOTOR_IN14_PORT              GPIOB
#define MOTOR_IN14_PIN               GPIO_Pin_0
#define MOTOR_IN14 									PBout(0)
/**********************************
函数声明
**********************************/
void Motor_Bujin_Init(void);					//电机初始化函数
void Motor_Foreward(uint32_t num);						//电机正转函数
void Motor_Reversal(uint32_t num);						//电机反转函数
void Motor_Foreward1(uint32_t num);						//电机正转函数
void Motor_Reversal1(uint32_t num);						//电机反转函数

#endif

