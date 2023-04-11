#include "pwm.h"



/**************************************************************************
函数功能：pwm初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
返回  值：无
**************************************************************************/

void	dj_int(u16 arr,u16 psc)
{
	 GPIO_InitTypeDef GPIO_InitStructure;                 //定义结构体GPIO_InitStructure
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //定义结构TIM_TimeBaseStructure
	 TIM_OCInitTypeDef  TIM_OCInitStructure;               //定义结构TIM_OCInitStructure
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //使能定时器4时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟

	 GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6|GPIO_Pin_9;          //PB6 PB9
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO口速度
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     	//复用模式输出
	 GPIO_Init(GPIOB, &GPIO_InitStructure);              //GBIOB初始化  
	
	 TIM_TimeBaseStructure.TIM_Period = arr;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
   TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //设置时钟分割:TDTS = Tck_tim
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式

   TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //PWMTIM脉冲宽度调制模式2
 	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //设置TIM输出比较极性为高
   TIM_OCInitStructure.TIM_OutputState=	TIM_OutputState_Enable;   //比较输出使能
	

   TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStructure中指定的参数初始化外设TIM4
	 TIM_OC4Init(TIM4, &TIM_OCInitStructure);

   TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);	    //使能预装载寄存器
	 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	 TIM_ARRPreloadConfig(TIM4, ENABLE);      //使能自动装载允许位

	 TIM_Cmd(TIM4, ENABLE);   //启动定时器TIM4

}


void	servo_int(u16 arr,u16 psc)
{
	 GPIO_InitTypeDef GPIO_InitStructure;                 //定义结构体GPIO_InitStructure
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //定义结构TIM_TimeBaseStructure
	 NVIC_InitTypeDef NVIC_InitStructure;
	 TIM_OCInitTypeDef  TIM_OCInitStructure;               //定义结构TIM_OCInitStructure
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  //使能定时器4时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PB端口时钟

	 GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2;          //PA2
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO口速度
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     	//复用模式输出
	 GPIO_Init(GPIOA, &GPIO_InitStructure);              //GBIOA初始化  
	
	 TIM_TimeBaseStructure.TIM_Period = arr;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
   TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //设置时钟分割:TDTS = Tck_tim
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式

   TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//===================================================================
	
//	TIM_ClearFlag(TIM5, TIM_FLAG_Update);//清中断标志位

//    TIM_ITConfig(      //使能或者失能指定的TIM中断
//    TIM5,            //TIM5
//    TIM_IT_Update  | //TIM 更新中断源
//    TIM_IT_Trigger,  //TIM 触发中断源 
//    ENABLE  	     //使能
//    );
//	
//  //设置优先级
//  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	   //从优先级0级
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 
//	
	//===============================================================

	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //PWMTIM脉冲宽度调制模式2
 	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //设置TIM输出比较极性为高
   TIM_OCInitStructure.TIM_OutputState=	TIM_OutputState_Enable;   //比较输出使能

   TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStructure中指定的参数初始化外设TIM5
	 //TIM_OC2Init(TIM5, &TIM_OCInitStructure);

   TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);	    //使能预装载寄存器
	 //TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	 TIM_ARRPreloadConfig(TIM5, ENABLE);      //使能自动装载允许位

	 TIM_Cmd(TIM5, ENABLE);   //启动定时器TIM5
	 TIM5->CCR3=133;
}



void timer_Init(int arr,int psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能

  TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期值
  TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //参数初始化
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位

  TIM_ITConfig(      //使能或者失能指定的TIM中断
    TIM1,            //TIM1
    TIM_IT_Update  | //TIM 更新中断源
    TIM_IT_Trigger,  //TIM 触发中断源 
    ENABLE  	     //使能
    );
	
  //设置优先级
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	   //从优先级0级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 

  TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设
}

