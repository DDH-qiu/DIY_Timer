#include "DS1302.h"

/* ***************************************************** */
// ���鶨��
/* ***************************************************** */
//DS1302����ַ�����ʱ����������
unsigned char code DS1302_ReadAddr[7] = {0x81,0x83,0x85,0x87,0x89,0x8B,0x8D};

//DS1302д��ַ�����ʱ����������
unsigned char code DS1302_WriteAddr[7] ={0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};

//DS1302��ʼ��ʱ��,202004050 131400 ������
unsigned char TIME[7] = {0, 0x59, 0x06, 0x15, 0x04, 0x03, 0x20};
/* ***************************************************** */


/* ***************************************************** */
// �������ƣ�DS1302_Write
// ��������: ��DS1302д������
// ��ڲ�������ַaddr ����dat
// ���ڲ������� 
/* ***************************************************** */
void DS1302_Write(u8 addr,u8 dat)
{
	u8 i;
	CE = 0;             //��ֹ���ݴ���
	_nop_();
	SCLK = 0;           //ȷ��д����ǰ����SCLKΪ�͵�ƽ
	_nop_();            
	CE = 1;             //��������ʱ�������ݴ���
	_nop_();
	for(i=0;i<8;i++)
	{
		DATA = addr & 0x01;   //ȡ�������λ
		addr >>= 1;          //��������
		SCLK = 1;            //SCLKʱ��������ʱ��DS1302��ȡ����
		_nop_(); 
		SCLK = 0;            //Ϊд��dat������׼��      
        _nop_();		
	}
	for(i=0;i<8;i++)
	{
	    DATA = dat & 0x01;   //ȡ�������λ
		dat >>= 1;          //��������
		SCLK = 1;            //SCLKʱ��������ʱ��DS1302��ȡ����
		_nop_(); 
		SCLK = 0;            //Ϊд��dat������׼�� 	
		_nop_();
	}
	CE = 0;                  //���ݴ������
	_nop_();	
}

/* ***************************************************** */
// �������ƣ�DS1302_Read
// ��������: ��ȡ�����ַ������
// ��ڲ�������ַ addr
// ���ڲ��������� dat
/* ***************************************************** */
unsigned char DS1302_Read(u8 addr)
{
	u8 i,temp,dat;
	CE = 0;
	_nop_();
	SCLK = 0;
	_nop_();
	CE = 1;
	_nop_();
	for(i=0;i<8;i++)
	{
		DATA = addr & 0x01;   //ȡ�������λ
		addr >>=1;
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();		
	}
	_nop_();
	for(i=0;i<8;i++)
	{
		temp = DATA;
		dat = (dat>>1) | (temp<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;    //DS1302�½���ʱ,��������
		_nop_();
	}
	CE = 0;
	_nop_();
	SCLK = 1;
	_nop_();
	DATA = 0;
	_nop_();
	return dat;
}
/* ***************************************************** */
// �������ƣ�DS1302_Init
// ��������: ��ʼ��DS1302
// ��ڲ�������
// ���ڲ������� 
/* ***************************************************** */
void DS1302_Init(void)
{
	u8 i;
	DS1302_Write(0x8E,0x00);         //��ֹд����
	for(i=0;i<7;i++)
	{
		DS1302_Write(DS1302_WriteAddr[i],TIME[i]);
	}
	DS1302_Write(0x8E,0x80);         //ʹ��д����
}

/* ***************************************************** */
// �������ƣ�DS1302_ReadTime
// ��������: ��ȡʱ����Ϣ
// ��ڲ�������
// ���ڲ������� 
/* ***************************************************** */

void DS1302_ReadTime(void)
{
	u8 i;
	for(i=0;i<7;i++)
	{
		TIME[i] = DS1302_Read(DS1302_ReadAddr[i]);
	}
}
