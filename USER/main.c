/*

#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "encoder.h"
#include "usart1.h"

#define M 20

void Systick_init(void)
{
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock / 100))	        //1000 -> 1ms  100->10ms
	{ 
		// Capture error  
		while (1);
	}
}


//**************************************************************************
���ߣ������� ���� ������
//**************************************************************************

//------------����˵��---------------

//    PWMA    -----------    B6       TIM4 ch1
//    AIN2    -----------    C2
//    AIN1    -----------    C1
//    STBY    -----------    5V
//    BIN1    -----------    C4
//    BIN2    -----------    C5
//    PWMB    -----------    B9       TIM4 ch4
//    VM      -----------    5-12V����ӵ�Դ��
//    GND     -----------    GND  ����ӵ�Դ��
//    VCC     -----------    5V   ���߼���Դ��
//    GND     -----------    GND   ���߼����أ�
// ===������====
//TIM3  A6 A7                       
//TIM2  A0 A1

//====���=====
// TIM5  A2

//------------����˵��---------------

//TB6612˿ӡ��ʶ--------���
//    AO1   ------------  ����ߵ�Դ+
//    AO2   ------------  ����ߵ�Դ-
//------------����˵��---------------
int flag = 0;
int fx=0;
int stop=0;
int va,vb;
//10s    1200 1200 300
//13s  800 1200 300
//16s 700 1200 300
//0�� 800,1200,300
//5�� 1200��1800��500
int TargetVelocityA=7,TargetVelocityB=7;
const int normal_speed = 1200,plus_speed =2200, decline_speed = 1000;
int n=7,pn=8,dn=6;
int pwmlim(int x)
{
	if(x<=80) x=80;
	if(x>=220) x=220;
	return x;
}
void buzz(int x)
{
	if(x) 
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		delay_ms(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		delay_ms(1);
	}
}
int i_limit(int *_in_val,int16_t  standard_val)
{
    if(*_in_val > standard_val)
        *_in_val = standard_val;
    if(*_in_val < -standard_val)
        *_in_val = -standard_val;
    return *_in_val;
}
 void Lcdshow()
 {
	 Lcd_Init();
	 LCD_LED_SET;//ͨ��IO���Ʊ�����	
	 Lcd_Clear(GRAY0);
	 Gui_DrawFont_GBK16(16,5,YELLOW,GRAY0,"�������Ӽ���");
	 Gui_DrawFont_GBK16(16,30,BLUE,GRAY0,"רעҺ������");
	 Gui_DrawFont_GBK16(16,55,RED,GRAY0, "ȫ�̼���֧��");
	 Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Tel:11239000975");
	 Gui_DrawFont_GBK16(0,105,RED,GRAY0, "QQ:1234656669");		
	 LCD_LED_CLR;//IO���Ʊ�����	
 }

 
u8 xj_State(void)
{
	u8 state = 0;
	state = (u8)(GPIO_ReadInputData(GPIOC) >> 11) & 0x001f;
	return state;
}
 
int Binary_number(int dec){
	int result = 0,temp = 10000,yushu = 0;
	while(1){
		yushu = dec%2;
		dec/=2;
		result+=yushu*temp;
		temp/=10;
		if(dec<2)
		{
			result+=dec*temp;
			break;
		}
	}
	return result;
}
 
 
void adjust(u8 x)
{
    if ((((~x) & 7)==3) || (((~x) & 7)==6)) {
    stop=1;
  }
	if (stop) return;
	if (flag == 1) {
		if (!(x&4)) {
			flag = 2;
			TargetVelocityA=n;
			TargetVelocityB=n;
			TIM5->CCR3=133;
		}
		else {
		  TIM5->CCR3 = 220;
		  TargetVelocityA=pn;TargetVelocityB=dn;
		}
	}
	else {
			switch(x)
				{
					case 19:
					    if (!flag) {TIM5->CCR3=220;flag=1;TargetVelocityA=pn;TargetVelocityB=dn;}
					    else TIM5->CCR3=160;
					    break;
					case 23:
              if (!flag) {TIM5->CCR3=220;flag=1;TargetVelocityA=pn;TargetVelocityB=dn;}
					    else TIM5->CCR3=160;
					    break;
					case 25: TIM5->CCR3=100;break;
					case 31: TIM5->CCR3=133;break;
					case 29: TIM5->CCR3=100;break;
					case 27: TIM5->CCR3=133;break;
				}
	}

}

void adjust2(u8 x)
{
	switch(x)
	{
		case 27: 
		case 31: if(fx==0){TIM5->CCR3=133;fx=0;}if(fx==1){TIM5->CCR3=80;delay_ms(100);fx=0;}if(fx==-1){TIM5->CCR3=220;delay_ms(100);fx=0;}break;
		case 29: 
		case 30: fx=1;TIM5->CCR3=80;break;
		case 23: 
		case 15: fx=-1;TIM5->CCR3=220;break;
	}
}




int a=0,b=0,xj=0,xj1=0;
float Velocity_Kp=500,  Velocity_Ki=0.5,  Velocity_Kd=0; 
int ControlVelocity=0;
int err_1a=0;		//e(k-1)
int err_2a=0; 	//e(k-2)
int err_1b=0;		//e(k-1)
int err_2b=0; 	//e(k-2)
int a1=0,b1=0;
int time=0;
int cnt=0;
int middlestate=0;//��¼�м��״̬
int phsteer=133;  //ƫ���������(80-220)��-��
int phstate=0;//0-left,1-right; ����ƫ��״̬
int wphstate=0;//0-left,1-right; ΢ƫ��״̬
int phoc=0;   //����ƫ���������(1 or 0)
int wphoc=0;
int lightstate=0;  //�Ƹ�Ӧ�źŸ�������Ӧ��ɫ����
int steerincrease=1  ;


int fib(int n)
{
	if(n==0) return 0;
	if(n==1) return 1;
	else return fib(n-1)+fib(n-2);
}


int main(void)
 {	
	 char s[20],c[20]="                   ";
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   SystemInit(); //����ϵͳʱ��Ϊ72M   
	 delay_init();    //��ʱ������ʼ��
   Gpio_Init();    //��ʼ��gpio��B pin_7/pin_8
   dj_int(7199,0);      //��ʼ��pwm��� 72000 000 /7199+1=10000 
	 servo_int(1999,719);
	 timer_Init(999,719);
	 usart1_init(115200);
	 Lcd_Init();
	 Encoder_A_init();
   Encoder_B_init();
	 LCD_LED_SET;//ͨ��IO���Ʊ�����
	 Lcd_Clear(GRAY0);	 
	 TIM5->CCR3=133;
	 buzz(0);
  while(1)
    {
				//TargetVelocity=-TargetVelocity;
			//delay_ms(3000);
//		  xj=xj_State();
//			adjust(xj);
//		  if (stop) {
//			  va=vb=0;
//			  buzz(1);
//		  }
	    //move(va,vb);
			//======================================
//	  a=Read_Encoder(1);
//	  b=Read_Encoder(2);
		
			if(stop==1) {move(0,0);Lcd_Clear(RED);}
			else{
				sprintf(s,"a:%5db:%5d",a,b);
				Gui_DrawFont_GBK16(0,40,RED,GRAY0,(u8 *)s);
				sprintf(s,"cnt:%5d ls:%d",cnt,lightstate);
				Gui_DrawFont_GBK16(0,80,RED,GRAY0,(u8 *)s);
			}
//    xj=xj_State();
//		xj1=Binary_number(xj);
//		sprintf(s,"xj:%05d",xj1);
//	  Gui_DrawFont_GBK16(0,60,RED,GRAY0,(u8 *)s);
//		sprintf(s,"xj:%05d    %02d",xj,fx);
//	  Gui_DrawFont_GBK16(0,85,RED,GRAY0,(u8 *)s);
//		adjust2(xj);
			//delay_ms(5);
		
	}
 }
int Velocity_Control1(int MeasureVelocity,int TargetVelocity,int mode)
{
	int err;  
	int proportion,integral,derivative;
	
	err=TargetVelocity-MeasureVelocity; 					//���ٶ�ƫ��
	proportion= Velocity_Kp*err;
	if(mode==0){
	integral  = Velocity_Ki*(err+err_1a+err_2a);
	derivative= Velocity_Kd*(err-err_1a);
	err_2a=err_1a;
	err_1a=err;}
	else if(mode==1){
	integral  = Velocity_Ki*(err+err_1b+err_2b);
	derivative= Velocity_Kd*(err-err_1b);
	err_2b=err_1b;
	err_1b=err;}
	ControlVelocity = proportion+ integral +derivative;
	
	return ControlVelocity; //�����ٶȿ���ֵ
}





int TIM1_UP_IRQHandler()//10ms once
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ
    a=Read_Encoder(1);
	  b=Read_Encoder(2);		
		xj=xj_State();				
	  a1=Velocity_Control1(a,TargetVelocityA,0);
    b1=Velocity_Control1(b,TargetVelocityB,1);	
		
	if(time<50)//ǰ��PID��ֹ����
	{
		i_limit(&a1,700); 
		i_limit(&b1,700);}
	else{
	  i_limit(&a1,4200); 
    i_limit(&b1,4200);}
	
		if(stop==0) move(a1,b1);//�������ָ��
		
		yofa_send_vel(a,TargetVelocityA);//yellow-red,green-brown,orange-black;;;fuck;;;���䴮���ź�
		
		time++;cnt++;//��ʱ,timeΪPID����ʱ�䣬cntΪƫ��ʱ��
		if(cnt>=1000){cnt=1000;}
		if(time>1000) time=1000;//��ʱ��������
		
		if((xj&4)!=middlestate) {cnt=0;buzz(0);phsteer=133;steerincrease=1;}//�м���ź�ˢ��cnt����buzzϨ��
		middlestate = xj&4;			//�����м�״̬
		lightstate = (!(xj&1))+(!(xj&2))+(!(xj&4))+(!(xj&8))+(!(xj&16)); //��ȡ���źŸ�������ɫ��Ϊ���ź�
		if( lightstate>=2 ) stop=1;   //�źų���һ��������ֹͣ�ź�

		
		
		if(stop==0){					//ֹͣ�ź�δ����ǰ

		if(cnt>42)						//ƫ�������ҳ�ʱ
		{
			buzz(1);						//������
			     if(!(xj&8)) {wphstate=1;phoc=0;}
			else if(!(xj&2)) {wphstate=0;phoc=0;}//��¼΢ƫ�����ң�����ƫ������
			
			     if(!(xj&16)){phstate=1;phoc=1;}//��¼����ƫ�����ң�����ƫ����һ
			else if(!(xj&1)) {phstate=0;phoc=1;}
			
			if(cnt>80) {										//ƫ�����س�ʱ�������Ҵ��򣬷�����������
				phsteer+=steerincrease; 
				if((!(xj&1))||(!(xj&1)))			//����ź�����������ͷ 
				{
					phsteer = 133-2*(phsteer-133);steerincrease=-1;
				}
				if(steerincrease>0) {TargetVelocityA=pn;TargetVelocityB=dn;}
				else								{TargetVelocityB=pn;TargetVelocityA=dn;}
				}
			else{														//ƫ��δ���س�ʱ���ò���С��
			if(wphstate) {TargetVelocityA=pn;TargetVelocityB=dn;}  //��ȡ΢ƫ��λ�ã�ѡ����ٷ���
			else 				 {TargetVelocityB=pn+1;TargetVelocityA=dn-1;}//Ĭ����else����������ٴ�һЩ���Ѱ·Ч��
		  }
			if(phoc)			//�������ƫ������
			{
			if(phstate) {phsteer = 220;TargetVelocityA=pn+2;TargetVelocityB=dn-2;}  //���ݷ��򣬴���Ӳ���ѭ��
				else 			{phsteer = 80;TargetVelocityB=pn+2;TargetVelocityA=dn-2;}
			}
			
			TIM5->CCR3=pwmlim(phsteer);  //���ͷ������
		}else {TIM5->CCR3=133;TargetVelocityA=n;TargetVelocityB=n;}//ƫ��δ��ʱ�޲��ٲ�ƫ��
		
	}
	}
}*/





#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "encoder.h"
#include "usart1.h"

#define M 20

void Systick_init(void)
{
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock / 100))	        //1000 -> 1ms  100->10ms
	{ 
		// Capture error  
		while (1);
	}
}


//**************************************************************************
//���ߣ�������
//**************************************************************************

int dp[200][100]={0};
long long x[10]={0};

void add(int a[],int b[],int c[])
{
	for(int i=0;i<99;i++)
	{
		c[i]+=a[i]+b[i];
		if(c[i]>=10)
		{
			c[i+1]+=1;
			c[i]-=10;
		}
	}
}
void fib(int n)
{
    int i,j=0,k=0;
    dp[0][0]=0;
    dp[1][0]=1;
    for(i=2;i<=n;i++)
    {
        add(dp[i-1],dp[i-2],dp[i]);
    }
    for(i=99;i>=1;i--)
	if(dp[200][i]!=0) break; 
	for(;i>=0;i--) //printf("%d",dp[200][i]);
	{
		static long long o=100000000000000;
		x[k]=dp[200][i]*o;
		o/=10;
		j++;
		if(!j%15)
		{
			k++;
			j=0;
			o=100000000000000;
		}
	}
	
}

int main(void)
 {	
	 char s[40],c[40]="                   ";
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   SystemInit(); //����ϵͳʱ��Ϊ72M   
	 delay_init();    //��ʱ������ʼ��
   Gpio_Init();    //��ʼ��gpio��B pin_7/pin_8
	 Lcd_Init();
	 LCD_LED_SET;//ͨ��IO���Ʊ�����
	 Lcd_Clear(GRAY0);
	 fib(20);
  while(1)
    {
				sprintf(s,"%lld",x[0]);
				Gui_DrawFont_GBK16(0,40,RED,GRAY0,(u8 *)s);
		}
//    xj=xj_State();
//		xj1=Binary_number(xj);
//		sprintf(s,"xj:%05d",xj1);
//	  Gui_DrawFont_GBK16(0,60,RED,GRAY0,(u8 *)s);
//		sprintf(s,"xj:%05d    %02d",xj,fx);
//	  Gui_DrawFont_GBK16(0,85,RED,GRAY0,(u8 *)s);
//		adjust2(xj);
			//delay_ms(5);
		
}
