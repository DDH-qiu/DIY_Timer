#include <DS1302.h>
/* ***************************************************** */
// λ����
/* ***************************************************** */
//74HC595
sbit smgSER = P3^4;		// 595��14�ţ�SER  ������������
sbit RCK = P3^3;		// 595��12�ţ�STCP ����ʱ�� 1������������һ������
sbit SCK = P3^2;		// 595��11�ţ�SHCP ��λʱ�� 8��ʱ������һ���ֽ�

/* ***************************************************** */
// ���鶨��
/* ***************************************************** */
//λѡ����
unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		
//��ѡ����
unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

/* ***************************************************** 
 �������ƣ�DelayMS()
 �������ܣ�������ʱ
 ��ڲ�������ʱ��������ValMS��
 ���ڲ�������
 ***************************************************** */
//void DelayMS(u16 ValMS)
//{
//	u16 uiVal,ujVal;
//	for(uiVal = 0; uiVal < ValMS; uiVal++)
//		for(ujVal = 0; ujVal < 120; ujVal++);
//}
/* ******************************************************************
 * �������ƣ�HC595_WrOneByte()
 * �������ܣ���HC595��д��һ���ֽ�
 * ��ڲ�������д��HC595��һ���ֽڣ�ucDat��
 * ���ڲ�������
/****************************************************************** */
void HC595_WrOneByte(unsigned char ucDat)
{
	unsigned char i = 0;
	//ͨ��8ѭ����8λ����һ������74HC595
	for(i=0;i<8;i++)
	{
		smgSER = (bit)(ucDat & 0x80);
		SCK = 0;
		ucDat <<= 1;
		SCK = 1;
	}
	//���ݲ�����������������أ�
	RCK = 0;		
	_nop_();
	_nop_();
	RCK = 1;
}
/* ******************************************************************
 * �������ƣ�Datapro
 * �������ܣ����ݴ���
 * ��ڲ�������
 * ���ڲ�������
/****************************************************************** */
void Datapro(void)
{
	DS1302_ReadTime();
	P2= Bit_Tab[0];					           // ��λѡ����
	HC595_WrOneByte(Disp_Tab[TIME[2]/16]);	   // �Ͷ�ѡ����
	HC595_WrOneByte(0x00);				       // ������Ӱ����
	
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
