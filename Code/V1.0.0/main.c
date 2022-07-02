#include"reg51.h"
unsigned char Time_num=0;
unsigned char Key_num;

//定时器0初始化,50ms的计数时间
void Timer_Init()
{
	TMOD &= 0x0F;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初始值
	TH0 = 0x3C;		//设置定时初始值
	TF0 = 0;		//清除TF1标志
	TR0 = 1;		//定时器1开始计时
	ET0=1;			//开启定时器中断
	EA=1;			//开启总中断
}

//时间计数
void Time_Count()
{
	// P1=0XFE;//初始化，1111 1110
	if (Time_num==180)
	{
		P1=0xFC;//15分钟到，1111 1100
	}
	if (Time_num==360)
	{
		P1=0xF8;//30分钟到，1111 1000
	}
	if (Time_num==361)
	{
		P1=0xF0;//45分钟到，1111 0000
	}
	if (Time_num==720)
	{
		P1=0xFF;//60分钟到，1111 1111
		Time_num=0;//复位
	}
}

//主函数
int main()
{
	Timer_Init();
	while(1)
	{
		
		Time_Count();
	}
}


void Timer0_isr() interrupt 1
{
	
	TL0=0xB0;		//设置定时初始值
	TH0=0x3C;		//设置定时初始值
	// TF0= 0;		//清除TF1标志
	Time_num++;//将该数字加一
	// if (Time_num>=180)
	// {
	// 	P1=0xFC;//15分钟到，1111 1100
	// }
	// if (Time_num>=360)
	// {
	// 	P1=0xF8;//30分钟到，1111 1000
	// }
	// if (Time_num>=400)
	// {
	// 	P1=0xF0;//45分钟到，1111 0000
	// }
	// if (Time_num==450)
	// {
	// 	P1=0xFF;//60分钟到，1111 1111
	// 	Time_num=0;//复位
	// }
	// TR0=1;
}