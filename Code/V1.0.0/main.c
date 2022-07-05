#include"reg52.h"
#include"intrins.h"

unsigned char Time_num=0;
unsigned char Seconds_num=0;
unsigned char Key_num=0,key_value=0,fun_num=0;
sbit LED_w1=P1^0;
sbit LED_w2=P1^1;
sbit LED_w3=P1^2;
sbit LED_r=P1^3;
sbit Buzzer=P1^4;
sbit key_num=P1^5;
sbit star_num=P1^6;
sbit LED_star=P1^7;


//软件延时3ms
void Delay3ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 211;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}



//软件延时500ms
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



//定时器0初始化,50ms的计数时间
void Timer_Init()
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初始值
	TH0 = 0x3C;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	ET0=1;			//开启定时器中断
	EA=1;			//开启总中断
}

//时间计数
void Time_Count()
{
	char i=0;
	if (Seconds_num==900)
	{
		LED_w2=0;//15分钟到，1111 1100
		Buzzer=0;
		Delay100ms();
		Buzzer=1;
	}

	if (Seconds_num==1800)
	{
		LED_w3=0;//30分钟到，1111 1000
		Buzzer=0;
		Delay100ms();
		Buzzer=1;
	}

	if (Seconds_num==2700)
	{
		LED_r=0;//45分钟到，1111 0000
		Buzzer=0;
		Delay100ms();
		Buzzer=1;
	}

	if (Seconds_num==3600)
	{
		// P1&=0x0F;//60分钟到，1110 1111	
		for (i=0;i<3;i++)
		{
			Buzzer=0;
			Delay500ms();
			Buzzer=1;
			Delay500ms();
		}			
		TR0=0;
	}
}

//按键检测
void Key_Detection()
{
	//算出按动时长
	if (key_num==0)
	{
		Delay3ms();//按键消抖
		while (key_num==0)//判断是否按下按键
		{
			TR0=1;
			LED_w1=0;
		}
	}
	if (star_num==0)
	{
		Delay3ms();
		if (star_num==0)
		{
			TR0=0;
			P1=0xFF;
			Seconds_num=0;
		}
		
	}
}

//主函数
int main()
{
	LED_star=1;
	Timer_Init();
	P1=0xFF;
	while(1)
	{
		Time_Count();
		Key_Detection();
		LED_star=~TR0;//指示灯
	}
}


//定时器中断服务
void Timer0_isr() interrupt 1
{
	
	TL0 = 0xB0;		//设置定时初始值
	TH0 = 0x3C;		//设置定时初始值
	Time_num++;//将该数字加一
	if(Time_num==20)//1秒计时
	{
		Seconds_num++;//1秒到
		Time_num=0;
	}

}
