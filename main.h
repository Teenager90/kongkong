#include <STC12C5A.h>

#include <intrins.h> //Keil library (is used for _nop()_ operation)  
#include <math.h>    //Keil library  
#include <stdio.h>   //Keil library
#include <string.h>

#define uint8 	unsigned char 
#define uint16 	unsigned int
#define uint32 	unsigned long

extern  uint16  testRegister;	//���ڲ�����ַַ16��testRegisterӦ�ø���ֵ����ֵ����趨����
extern  uint8	localAddr;	//��Ƭ����ĵ�ַ
extern  uint8	sendCount;		//�����ֽڸ���
extern  uint8	receCount,rece2Count;	    //���յ����ֽڸ���
extern  uint8	getCount;	    //���յ�����Ϣ�峤��

extern uint8  idata sendBuf[50],receBuf[20];
extern uint8  idata rece2Buf[40],soil_data[12];
extern uint8  idata co2_data[4];
extern  bit ByteEndFlag;	//�ֽ���������־λ
extern  bit RxFlag;		//�������ֽ�����־λ
extern  bit RXAAOK;		//���յ�֡ͷ��־λ

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
void  Single_Write_BH1750(unsigned char REG_Address);               //����д������
unsigned char Single_Read_BH1750(unsigned char REG_Address);                //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_BH1750();                               //�����Ķ�ȡ�ڲ��Ĵ�������
void BH1750_Start();                    //��ʼ�ź�
void BH1750_Stop();                     //ֹͣ�ź�
void BH1750_SendACK(bit ack);           //Ӧ��ACK
bit  BH1750_RecvACK();                  //��ack
void BH1750_SendByte(unsigned char dat);         //IIC�����ֽ�д
unsigned char BH1750_RecvByte();                 //IIC�����ֽڶ�
void Delay180ms();
void getBH1750data();
//--------------BH1750---------------------------------------------------------------

//--------------����ʪ��ģ��----------------------------------------------------------
void getsoilhumikey();
//--------------����ˮ�ֲ���ģ��----------------------------------------------------------
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

//////void timeProc(void);	//��ʱ����  
////led���Ե�
#define  DO1   	P21    //����led����
#define   RS485E  	P40 

