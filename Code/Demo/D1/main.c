#include <DS1302.h>
/* ***************************************************** */
// 位定义
/* ***************************************************** */
//74HC595
sbit smgSER = P3^4;		// 595（14脚）SER  数据输入引脚
sbit RCK = P3^3;		// 595（12脚）STCP 锁存时钟 1个上升沿所存一次数据
sbit SCK = P3^2;		// 595（11脚）SHCP 移位时钟 8个时钟移入一个字节

/* ***************************************************** */
// 数组定义
/* ***************************************************** */
//位选数组
unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		
//段选数组
unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

/* ***************************************************** 
 函数名称：DelayMS()
 函数功能：毫秒延时
 入口参数：延时毫秒数（ValMS）
 出口参数：无
 ***************************************************** */
//void DelayMS(u16 ValMS)
//{
//	u16 uiVal,ujVal;
//	for(uiVal = 0; uiVal < ValMS; uiVal++)
//		for(ujVal = 0; ujVal < 120; ujVal++);
//}
/* ******************************************************************
 * 函数名称：HC595_WrOneByte()
 * 函数功能：向HC595中写入一个字节
 * 入口参数：待写入HC595的一个字节（ucDat）
 * 出口参数：无
/****************************************************************** */
void HC595_WrOneByte(unsigned char ucDat)
{
	unsigned char i = 0;
	//通过8循环将8位数据一次移入74HC595
	for(i=0;i<8;i++)
	{
		smgSER = (bit)(ucDat & 0x80);
		SCK = 0;
		ucDat <<= 1;
		SCK = 1;
	}
	//数据并行输出（借助上升沿）
	RCK = 0;		
	_nop_();
	_nop_();
	RCK = 1;
}
/* ******************************************************************
 * 函数名称：Datapro
 * 函数功能：数据处理
 * 入口参数：无
 * 出口参数：无
/****************************************************************** */
void Datapro(void)
{
	DS1302_ReadTime();
	P2= Bit_Tab[0];					           // 送位选数据
	HC595_WrOneByte(Disp_Tab[TIME[2]/16]);	   // 送段选数据
	HC595_WrOneByte(0x00);				       // 消除鬼影现象
	
	P2 = Bit_Tab[1];
	HC595_WrOneByte(Disp_Tab[TIME[2]&0x0f]);
	HC595_WrOneByte(0x00);
	
	P2= Bit_Tab[2];
	HC595_WrOneByte(0x40);
	HC595_WrOneByte(0x00);
	
	P2 = Bit_Tab[3];
	HC595_WrOneByte(Disp_Tab[TIME[1]/16]);
	HC595_WrOneByte(0x00);
	
	P2 = Bit_Tab[4];
	HC595_WrOneByte(Disp_Tab[TIME[1]&0x0f]);
	HC595_WrOneByte(0x00);
	
	P2 = Bit_Tab[5];
	HC595_WrOneByte(0x40);
	HC595_WrOneByte(0x00);
	
	P2 = Bit_Tab[6];
	HC595_WrOneByte(Disp_Tab[TIME[0]/16]);
	HC595_WrOneByte(0x00);
	
	P2 = Bit_Tab[7];
	HC595_WrOneByte(Disp_Tab[TIME[0]&0x0f]);
	HC595_WrOneByte(0x00);
	
}




void main(void)
{
	DS1302_Init();
	while(1)
	{
		Datapro();
	}
}
