/**********************************

**********************************/


/**********************************
包含头文件
**********************************/
#include "motor_bujin.h"
#include "delay.h"


/****
*******电机初始化函数
*****/
void Motor_Bujin_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(MOTOR_IN1_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN1_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN1_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN1_PORT,MOTOR_IN1_PIN);						 			//IO口输出低
	
	RCC_APB2PeriphClockCmd(MOTOR_IN2_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN2_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN2_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN2_PORT,MOTOR_IN2_PIN);						 			//IO口输出低
	
	RCC_APB2PeriphClockCmd(MOTOR_IN3_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN3_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN3_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN3_PORT,MOTOR_IN3_PIN);						 			//IO口输出低
	
	RCC_APB2PeriphClockCmd(MOTOR_IN4_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN4_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN4_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN4_PORT,MOTOR_IN4_PIN);						 			//IO口输出低
	
	RCC_APB2PeriphClockCmd(MOTOR_IN11_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN11_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN11_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN11_PORT,MOTOR_IN11_PIN);						 			//IO口输出低
	
	RCC_APB2PeriphClockCmd(MOTOR_IN12_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN12_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN12_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN12_PORT,MOTOR_IN12_PIN);						 			//IO口输出低
	
	
	RCC_APB2PeriphClockCmd(MOTOR_IN13_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN13_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN13_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN13_PORT,MOTOR_IN13_PIN);						 			//IO口输出低
	
	
	RCC_APB2PeriphClockCmd(MOTOR_IN14_GPIO_CLK_ENABLE, ENABLE);	 	//使能引脚时钟
	GPIO_InitStructure.GPIO_Pin = MOTOR_IN14_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	GPIO_Init(MOTOR_IN14_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(MOTOR_IN14_PORT,MOTOR_IN14_PIN);						 			//IO口输出低
}

/****
*******电机正转函数 
*****/
void  Motor_Foreward(uint32_t num)
{ 
	unsigned int i;

	for(i=0;i<num;i++)
	{
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 1;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 1;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 1;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
	}
}

/****
*******电机正转函数 
*****/
void  Motor_Foreward1(uint32_t num)
{ 
	unsigned int i;

	for(i=0;i<num;i++)
	{
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 1;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 1;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 1;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 1;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 1;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 1;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
	}
}


/****
*******电机反转函数 
*****/
void  Motor_Reversal(uint32_t num)
{ 
	unsigned int i;

	for(i=0;i<num;i++)
	{
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 1;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 0;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 1;
		MOTOR_IN4 = 1;
		Delay_us(800);
		
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 1;
		Delay_us(800);
		
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 0;
		MOTOR_IN3 = 0;
		MOTOR_IN4 = 1;
		Delay_us(800);
	}
}


/****
*******电机反转函数 
*****/
void  Motor_Reversal1(uint32_t num)
{ 
	unsigned int i;

	for(i=0;i<num;i++)
	{
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 1;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 1;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN2 = 1;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 0;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 1;
		MOTOR_IN14 = 1;
		Delay_us(800);
		
		MOTOR_IN11 = 0;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 1;
		Delay_us(800);
		
		MOTOR_IN11 = 1;
		MOTOR_IN12 = 0;
		MOTOR_IN13 = 0;
		MOTOR_IN14 = 1;
		Delay_us(800);
	}
}
