#include "gpio.h"

void Gpio_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;            //����ṹ��GPIO_InitStructure
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9| GPIO_Pin_8|GPIO_Pin_15;	  //PB7 PB8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     	//���죬��������������  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);          //GPOB��ʼ��  
	
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PA�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_7| GPIO_Pin_8;	  //PA7 PA8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     	//���죬��������������  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //GPIOA��ʼ�� 

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PA�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_4| GPIO_Pin_5;	  //PC1 PC2 PC4 PC5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     	//���죬��������������  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);          //GPIOA��ʼ�� 

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PA�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;	  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     	//����  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);          //GPIOA��ʼ��
}
