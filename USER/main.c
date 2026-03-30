/**********************************

**********************************/


/**********************************
包含头文件
**********************************/
#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "dht11.h"
#include "adc.h"
#include "hc-sr04.h"
#include "motor_bujin.h"
#include "motor_bujin1.h"
#include "timer.h"
/**********************************
变量定义
**********************************/
char display_buf[32];									//显示缓存区
uint8_t key_num = 0;									//按键扫描标志位	
uint8_t flag_display = 0;							//显示界面标志位
_Bool flag_mode = 0;									//当前模式标志位
uint32_t time_num = 0;								//10ms计时
uint32_t light_value = 0;							//光照值
uint8_t light_max = 70;								//光照最大值
uint8_t light_min = 30;								//光照最小值
u16 temp_value = 0;										//温度最大值
u16 temp_max = 27;										//温度最大值
u16 temp_min = 10;										//温度最小值
u16 humi_value = 0;										//湿度最大值
u16 humi_max = 70;										//湿度最大值
u16 humi_min = 30;										//湿度最小值
uint32_t distance_value =0;						//距离值
uint8_t distance_max = 40;						//距离最大值
uint8_t distance_min = 10;						//距离最小值
uint32_t time_all = 0;								//定时时长
int16_t time_set_h = 0;								//定时（时）
int16_t time_set_m = 0;								//定时（分）
int16_t time_set_s = 0;								//定时（秒）
_Bool flag_time_end = 0;							//定时时间到达标志位
_Bool flag_zuozi = 0;									//坐姿标志位
uint32_t flag_dj = 0;									//电机角度
uint32_t flag_dj1 = 0;								//电机角度
_Bool flag_zz = 0;										//电机正转标志位
_Bool flag_fz = 0;										//电机反转标志位
_Bool flag_zz1 = 0;										//电机正转标志位
_Bool flag_fz1 = 0;										//电机反转标志位
extern uint32_t pwm_value;						//pwm值
extern _Bool flag_timer_begin ;				//计时开始标志位
extern _Bool flag_1s ;								//定时1s完成标志位
extern uint8_t usart2_buf[256];				//串口1接收数组

/**********************************
函数声明
**********************************/
void Key_function(void);							//按键函数
void Monitor_function(void);					//监测函数
void Display_function(void);					//显示函数
void Manage_function(void);						//处理函数


/****
*******	主函数 
*****/
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先分组
	Delay_Init();	    	 								//延时初始化	  
	Gpio_Init();		  									//IO初始化
	Key_Init();		  										//按键初始化
	Oled_Init();		  									//OLED初始化
	Oled_Clear_All();										//清屏
	
	
	
	
	Usart2_Init(9600);    							//串口1初始化
	
	
	
	
	
	TIM2_Init(9,7199);							//定时器初始化
	Motor_Bujin_Init();							//步进电机初始化
	DHT11_Init();										//温湿度初始化
	Adc_Init();											//ADC初始化
	HC_SR04_Init();									//HC_SR04初始化	
	
	
	
	
	
	while(1)
	{
		Key_function();										//按键函数
		Monitor_function();								//监测函数
		Display_function();								//显示函数


		time_num++;												//计时变量+1
		Delay_ms(10);
		if(time_num %10 == 0)
			LED_SYS = ~LED_SYS;
		if(time_num >= 5000)
		{
			time_num = 0;
		}
	}
}

///****
//*******按键函数
//*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(1);		//按键扫描
	if(key_num != 0)											//有按键按下
	{
		switch(key_num)
		{
			case 1:								            //按键1，切换设置界面
				flag_display++;
				if(flag_display >= 9)

			break;

				
				
//								pwm_value=10;
//						if(pwm_value > 10)
//							pwm_value = 0;
//						flag_mode = 1;		
				
				
			case 2:																	//按键2：加键
				switch(flag_display)
				{
					case 0:															//界面0：手动调节灯光亮度
						pwm_value=10;
						if(pwm_value > 10)
							pwm_value = 0;
						flag_mode = 1;
					break;					

					case 1:															//界面1：距离最大值+1
						if(distance_max < 100)
							distance_max++;
					break;
						
					case 2:															//界面2：距离最小值+1
						if(distance_min < distance_max-1)
							distance_min++;
					break;						

					case 3:															//界面3：光照最大值+1
						if(light_max < 99)
							light_max++;
					break;
					
					case 4:															//界面4：光照最小值+1
						if(light_min < light_max - 1)
							light_min++;
					break;
						
					case 5:															//界面5：定时时+1
						time_set_h++;
						if(time_set_h >= 24)
							time_set_h = 0;
					break;
						
					case 6:															//界面6：定时分+1
						time_set_m++;
						if(time_set_m >= 60)
							time_set_m = 0;	
					break;	

					case 7:														//界面7：定时秒+1
						time_set_s++;
						if(time_set_s >= 60)
							time_set_s = 0;
					break;
						
					case 8:
						if(temp_max < 99)
							temp_max++;
						break;
					
												
					default:
					break;
				}
			break;

			case 3:														//按键3：减键
				switch(flag_display)
				{
					case 0:												//界面0：回到自动模式
            flag_mode = 0;			
					break;
					
					case 1:												//界面1：距离最大值-1
						if(distance_max > distance_min+1)
							distance_max--;
					break;
						
					case 2:												//界面2：距离最小值-1
						if(distance_min > 0)
							distance_min--;
					break;					

					case 3:												//界面3：光照最大值-1
						if(light_max > light_min + 1)
							light_max--;
					break;
					
					case 4:												//界面4：光照最小值-1
						if(light_min > 0)
							light_min--;
					break;
						
          case 5:												//界面5：定时时-1
						time_set_h--;
						if(time_set_h < 0)
							time_set_h= 23;
					break;
						
					case 6:												//界面6：定时分-1
						time_set_m--;
						if(time_set_m < 0)
							time_set_m= 59;
					break;

          case 7:												//界面7：定时秒-1
						time_set_s--;
						if(time_set_s < 0)
							time_set_s= 59;
					break;
					case 8:
						if(temp_max > 0)
							temp_max--;
					break;
					default:
					break;
				}
			break;
			
			case 4:														//按键4				
				if(flag_dj<4)										//提高桌面
				{
					flag_dj++;
					flag_zz = 1;
					flag_mode = 1;
					Oled_Clear_All();					      //清屏
				}
			break;
				
			case 5:														//按键5				
				if(flag_dj>0)										//降低桌面降低桌面
				{
					flag_dj--;						
					flag_fz = 1;
					flag_mode = 1;	
					Oled_Clear_All();					      //清屏					
				}
			break;
				
			case 6:														//按键6				
				if(flag_dj1<4)										//提高桌面角度
				{
					flag_dj1++;
					flag_zz1 = 1;
					flag_mode = 1;
					Oled_Clear_All();					      //清屏
				}
			break;
				
			case 7:														//按键7				
				if(flag_dj1>0)										//降低桌面角度
				{
					flag_dj1--;						
					flag_fz1 = 1;
					flag_mode = 1;	
					Oled_Clear_All();					      //清屏					
				}
				
			break;
			default:
				
			break;
		}
	}
}





void Monitor_function(void)
{
	if(flag_display == 0)																			//测量界面
	{
		if(time_num % 5 == 0)																		//约1s检测一次
		{
			light_value  = 30*(Get_Adc_Average(0,1)/4096.0*3.3);	//获取光照值
			distance_value = Hcsr04_GetDistance(28);							//获取距离值
			Dht11_Get_Temp_Humi_Value(&temp_value,&humi_value);		//获取温湿度
		}
	}
}

/****
*******显示函数
*****/
void Display_function(void)
{
	switch(flag_display)									//根据不同的显示模式标志位，显示不同的界面
	{
		case 0:									      			//界面0：
			Oled_ShowString(1,0,"L:");
			sprintf(display_buf,"%dLx   ",light_value);
			Oled_ShowString(1, 2, display_buf);	
			Oled_ShowString(1,8,"J:");
			sprintf(display_buf,"%dcm   ",distance_value);
			Oled_ShowString(1, 10, display_buf);
			Oled_ShowString(2,0,"T:");
			sprintf(display_buf,"%d.%dC   ",temp_value/10,temp_value%10);
			Oled_ShowString(2, 2, display_buf);
			Oled_ShowString(2,8,"H:");
			sprintf(display_buf,"%d.%d%%  ",humi_value/10,humi_value%10);
			Oled_ShowString(2, 10, display_buf);
			
			Oled_ShowCHinese(3, 0, "高度：");
		













switch(flag_dj)																	//显示书桌高度
			{
				case 0:
					Oled_ShowCHinese(3, 3, "最低");						
				break;
				
				case 1:
					Oled_ShowCHinese(3, 3, "低　");
									
				break;

				case 2:
					Oled_ShowCHinese(3, 3, "中　");						
				break;

				case 3:
					Oled_ShowCHinese(3, 3, "高　");							
				break;	
				
				case 4:
					Oled_ShowCHinese(3, 3, "最高");							
				break;				
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			switch(flag_dj1)																	//显示书桌高度
			{
				case 0:
					Oled_ShowString(3,12,"0c ");	
				break;
				
				case 1:
					Oled_ShowString(3,12,"10c ");					
				break;

				case 2:
					Oled_ShowString(3,12,"20c ");				
				break;
				
				case 3:
					Oled_ShowString(3,12,"30c ");							
				break;		
			}
			
			Oled_ShowCHinese(4, 0, "模式：");
			if(flag_mode == 0)
				Oled_ShowCHinese(4,3,"自动");
			else
				Oled_ShowCHinese(4,3,"手动");	
		break;
		
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		case 1:																								//界面1：显示设置距离最大值
			Oled_ShowCHinese(1,0,"设置距离最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d",distance_max);
				Oled_ShowString(2, 6, display_buf);	
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 6, "    ");
			}
		break;
			
		
		
		
//			{
//				sprintf(display_buf,"%d",distance_min);
//				Oled_ShowString(2, 6, display_buf);	
//			}
//			if(time_num % 10 == 0)
//			{
//				Oled_ShowString(2, 6, "    ");
		
		
		
		
		case 2:																								//界面2：显示设置距离最小值
			Oled_ShowCHinese(1,0,"设置距离最小值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d",distance_min);
				Oled_ShowString(2, 6, display_buf);	
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 6, "    ");
			}
		break;

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		case 3:																								//界面3：显示设置光照最大值
			Oled_ShowCHinese(1,0,"设置光照最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d",light_max);
				Oled_ShowString(2, 6, display_buf);	
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 6, "    ");
			}
		break;				
			
		case 4:																								//界面4：显示设置光照最小值
			Oled_ShowCHinese(1,0,"设置光照最小值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d",light_min);
				Oled_ShowString(2, 6, display_buf);	
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 6, "    ");
			}
		break;		
	





//	Oled_ShowCHinese(1,0,"设置光照最小值");
//			if(time_num % 5 == 0)
//			{
//				sprintf(display_buf,"%d",light_min);
//				Oled_ShowString(2, 6, display_buf);	





			
		case 5:																								//界面5：显示设置设置定时时间
			Oled_ShowCHinese(1,1,"设置定时时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%02d:%02d:%02d",time_set_h,time_set_m,time_set_s);
				Oled_ShowString(2, 4, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 4, "  ");
			}
		break;
			
		case 6:																								//界面6：显示设置设置定时时间
			Oled_ShowCHinese(1,1,"设置定时时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%02d:%02d:%02d",time_set_h,time_set_m,time_set_s);
				Oled_ShowString(2, 4, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "  ");
			}
		break;		

			
			
			
			
			
			
			
//					{
//				sprintf(display_buf,"%02d:%02d:%02d",time_set_h,time_set_m,time_set_s);
//				Oled_ShowString(2, 4, display_buf);
//			}
//			if(time_num % 10 == 0)
			
			
			
			
			
			
			
			
			
			
			
			
		case 7:																								//界面7：显示设置设置定时时间
			Oled_ShowCHinese(1,1,"设置定时时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%02d:%02d:%02d",time_set_h,time_set_m,time_set_s);
				Oled_ShowString(2, 4, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 10, "  ");
			}
		break;
			
		case 8:																								//界面4：显示设置温度最大值
			Oled_ShowCHinese(1,0,"设置温度最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d",temp_max);
				Oled_ShowString(2, 6, display_buf);	
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 6, "    ");
			}
		break;	
		
		default:
			
		break;
	}
}

/****
*******处理函数
*****/




















void Manage_function(void)
{
	if(flag_display == 0)                  //测量界面
	{
		if(distance_value < distance_max)														//当距离值小于设置最大值，则证明有人在台灯前
		{	
			if(time_all > 0)			
				flag_timer_begin = 1;
			if(flag_mode == 0)																			//自动模式下
			{
				if(light_value > light_max)                                                                                                                //光照大于设置最大值，关闭灯光
				{
								pwm_value = 0;
				}
				else if(light_value < light_min)                                                                                        //光照小于设置最小值，灯光最亮
				{
								pwm_value = 10;
				}
				else                                                                                                                                                                                                        //光照处于设置的上下限值之间，根据光照值调节灯光亮度
				{
								pwm_value = 10 - 10*(light_value-light_min) / (light_max-light_min);
				}
			}
			
			if(distance_value < distance_min)												//当距离值小于设置最小值，则坐姿有问题，通过语音模块提醒“请注意坐姿”	
			{
//				if(flag_zuozi == 1)
//				{
				Delay_us(800);
//				Delay_us(800);
//				Delay_us(800);
//				Delay_us(800);
					UsartPrintf(USART2,"嘀请注意坐姿");

//					flag_zuozi = 1;
//				}
			}	
			else
			{
				flag_zuozi = 0;
			}				
		}
		else if(flag_mode == 0)																		//距离大于设置最大值，关灯	
		{
			pwm_value	= 0;
		}
		
		if(flag_time_end == 1)																		//计时达到设置时间，通过语音模块提醒“请注意休息”，且控制书桌下降
		{
			flag_time_end = 0;
			time_all = time_set_h*3600+time_set_m*60+time_set_s;
			UsartPrintf(USART2,"请注意休息");
			while(flag_dj > 0)
			{
				flag_dj--;
				Motor_Reversal(64);
			}
		}
		
		if(temp_value > temp_max*10)
		{
			FS = 1;
		}
		else
		{
			FS = 0;
		}
		
		if(flag_mode == 1)
		{
			if(flag_zz == 1)
			{
				Motor_Foreward(64);			
				flag_zz = 0;
			}
			else if(flag_fz == 1)
			{
				Motor_Reversal(64);
				flag_fz = 0;
			}
			
			if(flag_zz1 == 1)
			{
				Motor_Foreward1(64);			
				flag_zz1 = 0;
			}
			else if(flag_fz1 == 1)
			{
				Motor_Reversal1(64);
				flag_fz1 = 0;
			}
			
		}
	}
	else													         //设置界面
	{
		
	}
}

