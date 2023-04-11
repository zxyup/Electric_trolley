#include "moto.h"


/**************************************************************************
函数功能：电机的正反转
入口参数：mode   mode=0时为正转  mode=1时反转
返回  值：无
**************************************************************************/


void motoA(int mode)
{
	if(mode==1)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_1);	 // 高电平
	 GPIO_ResetBits(GPIOC, GPIO_Pin_2);	 // 低电平}
	}
	 if(mode==0)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_2);	 // 高电平
	 GPIO_ResetBits(GPIOC, GPIO_Pin_1);	 // 低电平}
	 }
 
}

void motoB(int mode)
{
	if(mode==0)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_4);	 // 高电平
	 GPIO_ResetBits(GPIOC, GPIO_Pin_5);	 // 低电平}
	}
	 if(mode==1)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_5);	 // 高电平
	 GPIO_ResetBits(GPIOC, GPIO_Pin_4);	 // 低电平}
	 }
 
}

void move(int a,int b)
{
		if(a>0)
		{
			motoA(1); 
			TIM4->CCR1=a;
		}
		else
		{
			motoA(0); 
			TIM4->CCR1=-a;
		}
		if(b>0)
		{
			motoB(1); 
			TIM4->CCR4=b;
		}
		else
		{
			motoB(0); 
			TIM4->CCR4=-b;
		}
}
