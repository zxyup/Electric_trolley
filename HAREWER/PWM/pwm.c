#include "pwm.h"



/**************************************************************************
�������ܣ�pwm��ʼ��
��ڲ�����arr����Ϊһ��ʱ��Ƶ�ʵ����ֵ  psc�� Ԥ��Ƶֵ
����  ֵ����
**************************************************************************/

void	dj_int(u16 arr,u16 psc)
{
	 GPIO_InitTypeDef GPIO_InitStructure;                 //����ṹ��GPIO_InitStructure
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //����ṹTIM_TimeBaseStructure
	 TIM_OCInitTypeDef  TIM_OCInitStructure;               //����ṹTIM_OCInitStructure
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //ʹ�ܶ�ʱ��4ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��

	 GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6|GPIO_Pin_9;          //PB6 PB9
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO���ٶ�
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     	//����ģʽ���
	 GPIO_Init(GPIOB, &GPIO_InitStructure);              //GBIOB��ʼ��  
	
	 TIM_TimeBaseStructure.TIM_Period = arr;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
   TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //����ʱ�ӷָ�:TDTS = Tck_tim
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ

   TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //PWMTIM�����ȵ���ģʽ2
 	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //����TIM����Ƚϼ���Ϊ��
   TIM_OCInitStructure.TIM_OutputState=	TIM_OutputState_Enable;   //�Ƚ����ʹ��
	

   TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStructure��ָ���Ĳ�����ʼ������TIM4
	 TIM_OC4Init(TIM4, &TIM_OCInitStructure);

   TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);	    //ʹ��Ԥװ�ؼĴ���
	 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	 TIM_ARRPreloadConfig(TIM4, ENABLE);      //ʹ���Զ�װ������λ

	 TIM_Cmd(TIM4, ENABLE);   //������ʱ��TIM4

}


void	servo_int(u16 arr,u16 psc)
{
	 GPIO_InitTypeDef GPIO_InitStructure;                 //����ṹ��GPIO_InitStructure
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //����ṹTIM_TimeBaseStructure
	 NVIC_InitTypeDef NVIC_InitStructure;
	 TIM_OCInitTypeDef  TIM_OCInitStructure;               //����ṹTIM_OCInitStructure
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  //ʹ�ܶ�ʱ��4ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��

	 GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2;          //PA2
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO���ٶ�
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     	//����ģʽ���
	 GPIO_Init(GPIOA, &GPIO_InitStructure);              //GBIOA��ʼ��  
	
	 TIM_TimeBaseStructure.TIM_Period = arr;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
   TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //����ʱ�ӷָ�:TDTS = Tck_tim
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ

   TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//===================================================================
	
//	TIM_ClearFlag(TIM5, TIM_FLAG_Update);//���жϱ�־λ

//    TIM_ITConfig(      //ʹ�ܻ���ʧ��ָ����TIM�ж�
//    TIM5,            //TIM5
//    TIM_IT_Update  | //TIM �����ж�Դ
//    TIM_IT_Trigger,  //TIM �����ж�Դ 
//    ENABLE  	     //ʹ��
//    );
//	
//  //�������ȼ�
//  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	   //�����ȼ�0��
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 
//	
	//===============================================================

	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //PWMTIM�����ȵ���ģʽ2
 	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //����TIM����Ƚϼ���Ϊ��
   TIM_OCInitStructure.TIM_OutputState=	TIM_OutputState_Enable;   //�Ƚ����ʹ��

   TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStructure��ָ���Ĳ�����ʼ������TIM5
	 //TIM_OC2Init(TIM5, &TIM_OCInitStructure);

   TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);	    //ʹ��Ԥװ�ؼĴ���
	 //TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	 TIM_ARRPreloadConfig(TIM5, ENABLE);      //ʹ���Զ�װ������λ

	 TIM_Cmd(TIM5, ENABLE);   //������ʱ��TIM5
	 TIM5->CCR3=133;
}



void timer_Init(int arr,int psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��

  TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ�������ֵ
  TIM_TimeBaseStructure.TIM_Prescaler =psc;//����Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//�ظ���������
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //������ʼ��
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ

  TIM_ITConfig(      //ʹ�ܻ���ʧ��ָ����TIM�ж�
    TIM1,            //TIM1
    TIM_IT_Update  | //TIM �����ж�Դ
    TIM_IT_Trigger,  //TIM �����ж�Դ 
    ENABLE  	     //ʹ��
    );
	
  //�������ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	   //�����ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 

  TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����
}

