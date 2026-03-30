/**********************************

**********************************/


/**********************************
包含头文件
**********************************/
#include "hc-sr04.h"
#include "delay.h"


/**********************************
变量定义
**********************************/
uint16_t msHcCount = 0;



/****
*******HC_SR04初始化函数
*****/
void HC_SR04_Init(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*引脚配置*/
	RCC_APB2PeriphClockCmd(HCSR04_ECHO_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_PIN;									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 				//设为输入
	GPIO_Init(HCSR04_ECHO_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(HCSR04_ECHO_PORT,HCSR04_ECHO_PIN);								//拉低引脚

	RCC_APB2PeriphClockCmd(HCSR04_TRIG_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_PIN;									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         		 	//IO口速度为50MHz
	GPIO_Init(HCSR04_TRIG_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_ResetBits(HCSR04_TRIG_PORT,HCSR04_TRIG_PIN);								//拉低引脚

	/*定时器配置*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   					//时钟使能
	TIM_DeInit(TIM3);																								//初始化
	TIM_TimeBaseStructure.TIM_Period = 999;													//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 											//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);     						//根据指定的参数初始化TIMx的时间基数单位     
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);  													//清除中断标志位
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    										//使能指定的定时器中断,允许更新中断
	TIM_Cmd(TIM3,DISABLE);																					//失能定时器

	/*中断配置*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);									//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            			//哪个中断中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  			//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;           		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       					//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  																//初始化NVIC寄存器
}

/****
*******定时器中断函数
*****/
void TIM3_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  							//检查定时器更新中断发生与否
	{
		msHcCount++;																									//时间计数值+1
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);										//清除定时器更新中断标志 
	}
}

/****
*******获取距离值函数
传入值：温度值
返回值：测得的距离(距离单位cm)
*****/
uint16_t Hcsr04_GetDistance(uint16_t Hcsr04_temp)
{
	uint32_t Echo_time = 0;
	uint8_t i = 0;
	uint16_t distance = 0;
	uint16_t sum = 0;
	float gSpeed;

	gSpeed = 0.607*Hcsr04_temp+331.4;					// 根据公式 v=0.607T+331.4 计算出当前温度值对应的超声波速度，这时的单位是“米/秒” 
	gSpeed = gSpeed/10000;										// 将超声波的速度从单位“m/s”转为“cm/us”，方便后面的计算

	while(i != 3)															//取三次数据的平均值
	{
		HCSR04_TRIG = 1;												//给超声波模块一个开始脉冲
		Delay_us(20);
		HCSR04_TRIG = 0;

		while(HCSR04_ECHO == 0);      					//等待超声波模块的返回脉冲
		TIM_SetCounter(TIM3,0);									//复位计数值
		msHcCount = 0;													//清除溢出计数值
		TIM_Cmd(TIM3, ENABLE);									//开启定时器	
		i++;																		//次数+1
		while(HCSR04_ECHO == 1);								//等待超声波模块的返回脉冲结束
		TIM_Cmd(TIM3, DISABLE);									//关闭定时器
		Delay_ms(10);														//延时10ms
		Echo_time = msHcCount*1000 + TIM_GetCounter(TIM3);			//计算时间
		TIM_SetCounter(TIM3,0);									//复位计数值
		distance = Echo_time*gSpeed/2;					//计算距离
		sum = distance + sum ;									//叠加距离
	}
	distance = sum/3.0;												//取平局距离值

	return distance;
}

