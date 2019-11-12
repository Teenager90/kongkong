#include <STC12C5A.h>

#include <intrins.h> //Keil library (is used for _nop()_ operation)  
#include <math.h>    //Keil library  
#include <stdio.h>   //Keil library
#include <string.h>

#define uint8 	unsigned char 
#define uint16 	unsigned int
#define uint32 	unsigned long

extern  uint16  testRegister;	//用于测试字址址16，testRegister应该赋初值，初值如何设定？？
extern  uint8	localAddr;	//单片机板的地址
extern  uint8	sendCount;		//发送字节个数
extern  uint8	receCount,rece2Count;	    //接收到的字节个数
extern  uint8	getCount;	    //接收到的消息体长度

extern uint8  idata sendBuf[50],receBuf[20];
extern uint8  idata rece2Buf[40],soil_data[12];
extern uint8  idata co2_data[4];
extern  bit ByteEndFlag;	//字节流结束标志位
extern  bit RxFlag;		//接收完字节流标志位
extern  bit RXAAOK;		//接收到帧头标志位

extern  unsigned int SHThumi_vali,SHTtemp_vali;
extern  unsigned int AM23humi,AM23temp;
extern  unsigned int BH1750light;
extern  unsigned int soilhumikey;
extern  unsigned int MGS811key;
extern  unsigned int MGS811data;
extern  unsigned int SHThumi_valisoil,SHTtemp_valisoil;
extern  unsigned int soilwaterdata;
extern  unsigned int soiltempdata;
//------------------SHT------------------------------------------------------------
char s_write_byte(unsigned char value);
char s_read_byte(unsigned char ack);
void s_transstart(void);
void s_connectionreset(void);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth11(float *p_humidity ,float *p_temperature);
void getSHTdata(void);

//------------------SHT------------------------------------------------------------

//------------------SHT------------------------------------------------------------
char s_write_bytesoil(unsigned char value);
char s_read_bytesoil(unsigned char ack);
void s_transstartsoil(void);
void s_connectionresetsoil(void);
char s_measuresoil(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth11soil(float *p_humidity ,float *p_temperature);
void getSHTdatasoil(void);

//------------------SHT------------------------------------------------------------
//------------------AM23------------------------------------------------------------
void Delay_N10us(void);
void Delay_N30us(void);
void Delay_N30us(void);
void Delay_N2ms(void);
void Delay_N1ms(uint8 z);
unsigned char Read_AM23SensorData(void);
void getAM23data(void);
//------------------AM23------------------------------------------------------------

//--------------BH1750--------------------------------------------------------------
void Init_BH1750(void);
void Delay5us();
void Delay5ms();
void  Single_Write_BH1750(unsigned char REG_Address);               //单个写入数据
unsigned char Single_Read_BH1750(unsigned char REG_Address);                //单个读取内部寄存器数据
void  Multiple_Read_BH1750();                               //连续的读取内部寄存器数据
void BH1750_Start();                    //起始信号
void BH1750_Stop();                     //停止信号
void BH1750_SendACK(bit ack);           //应答ACK
bit  BH1750_RecvACK();                  //读ack
void BH1750_SendByte(unsigned char dat);         //IIC单个字节写
unsigned char BH1750_RecvByte();                 //IIC单个字节读
void Delay180ms();
void getBH1750data();
//--------------BH1750---------------------------------------------------------------

//--------------土壤湿度模块----------------------------------------------------------
void getsoilhumikey();
//--------------土壤水分测量模块----------------------------------------------------------
void getsoilwaterdata();
void getMulti_soilwaterdata();
//------------------MGS811------------------------------------------------------------
void getMGS811key();
void getMGS811data();


//------------------SHT------------------------------------------------------------

void checkComm0Modbus(void);
void readRegisters(void);
uint16 getRegisterVal(uint16 addr,uint16 *tempData);
uint16 crc16(uint8 *puchMsg, uint16 usDataLen);
void UartSendstr(uint8 len,uint8 stemp[]);	 //void beginSend(void);
void Uart2Sendstr(uint8 len,uint8 stemp[]);
void checkUart2data(void);
void rep_Error(void);

/*
void varInit(void);
void adc_init(void);
void watchdog_init(void); */
void delay(uint8 x);
void delay_1s(void);
void port_init(void);
void timer0_init(void);
void uart1_init(void);
void uart2_init(void);

//////void timeProc(void);	//定时处理  
////led测试灯
#define  DO1   	P21    //测试led，绿
#define   RS485E  	P40 

