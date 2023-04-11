#include "moto.h"


/**************************************************************************
�������ܣ����������ת
��ڲ�����mode   mode=0ʱΪ��ת  mode=1ʱ��ת
����  ֵ����
**************************************************************************/


void motoA(int mode)
{
	if(mode==1)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_1);	 // �ߵ�ƽ
	 GPIO_ResetBits(GPIOC, GPIO_Pin_2);	 // �͵�ƽ}
	}
	 if(mode==0)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_2);	 // �ߵ�ƽ
	 GPIO_ResetBits(GPIOC, GPIO_Pin_1);	 // �͵�ƽ}
	 }
 
}

void motoB(int mode)
{
	if(mode==0)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_4);	 // �ߵ�ƽ
	 GPIO_ResetBits(GPIOC, GPIO_Pin_5);	 // �͵�ƽ}
	}
	 if(mode==1)
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_5);	 // �ߵ�ƽ
	 GPIO_ResetBits(GPIOC, GPIO_Pin_4);	 // �͵�ƽ}
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
