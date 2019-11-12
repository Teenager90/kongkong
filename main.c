#include <main.h>
uint8  crc_Check=0;
uint8  getCount = 0;
uint8   temp = 0;
uint8 idata aa[5]={0x01,0x02,0x03,0x04,0x05};
void Uart2_Isr() interrupt 8 //using 1	 
{	
//	DO1=0;
//	if(S2CON & S2TI)
//	{
//	}
uint16 crcData;
	if (S2CON & S2RI)
	{		
		S2CON &= ~S2RI;		  //清除接收完成标志

		rece2Buf[rece2Count]=S2BUF;	//接收一个字节数据
		rece2Count++; 
		if(rece2Buf[0] == 0x20&& rece2Buf[1] == 0x03 && rece2Buf[2]==0x04)	  //判断接收开始标志
		{
			if((rece2Count==9))				 //判断接收完成
			{
			crcData = crc16(rece2Buf,7);
				if((rece2Buf[7] == (uint8)((crcData&0xff00)>>8))&&
					(rece2Buf[8] == (uint8)(crcData&0x00ff)))						 //数组清零
			       checkUart2data(); 					   //处理接收数据
      				rece2Count=0;
			}
			else
			{
			}
		}

	}


}


/*********************************************************************/

/*********************************************************************/
uint8 Rx_i = 0;
uint16 crcData;	
void Uart_Isr() interrupt 4 //using 1 
{	

	if(TI)
	{
	//	TI=0;
    
	}
	if(RI)      
	{ 
		RI=0;				      //接收到数据中断请求位手动清零
		Rx_i=SBUF;			      //提取字符
		receCount++;
		if(RxFlag==0)
		{	
			if((receCount==1)&&(Rx_i == 0xa5))		//判断前两个字节
			{
			  	receBuf[0] = Rx_i;
			}
			else if((receCount==2)&&(Rx_i == 0x5a))
			{
				receBuf[1] = Rx_i;
			}						 
			else if((receCount>2)&&(receBuf[0] == 0xa5) && (receBuf[1] ==0x5a))
			{
			 	receBuf[receCount-1]=Rx_i;					    //接收一个字节数据	                        
			 	if((receBuf[0] == 0xa5) && (receBuf[1] ==0x5a)&&(receCount>6))		 	//
			 	{
			     	getCount = receBuf[4];
					if(receCount==(getCount+8))
					{
				 	if(receBuf[(getCount+7)]==0xBF)		 //判断是否接收完成
				 	{

						switch(receBuf[3])
						{ 
							case 0x03://读取保持寄存器，读多路采集信号，对于传感板只需考虑功能3
							{
								if(receBuf[2] == localAddr)			 //设备地址正确
								{
					    			crcData = crc16(receBuf,(getCount+5));
									if((receBuf[(getCount+5)] == (uint8)((crcData&0xff00)>>8))&&
								   	   (receBuf[(getCount+6)] == (uint8)(crcData&0x00ff))
								      )
//									if(crcData == receBuf[(getCount+6)]+(receBuf[(getCount+5)]<<8))			//校验正确
									{
//										crc_Check=1;
										RxFlag=1;	
					    			}
									else
									{
//										crc_Check=2;
//										RxFlag=1;
										rep_Error();
									}

				    			}
								break;
			   				}
		   					default:
							{
		   						break;
							}
		 				}
						receCount = 0;									 
				 	}	
//					else if(receCount!=(getCount+8))
					else
					{
						receCount=0;
						RxFlag=0;
						memset(receBuf,0,sizeof(receBuf));
					}
					}


			  	}
//				else if(receCount>=20)
//				{		   	
//			    	receCount=0;
//			   		RxFlag=0;
//					memset(receBuf,0,sizeof(receBuf));
//				}
			}
			else
				receCount =0;
		}
		else
			receCount=0;
	}
}

void Timer0_Isr() interrupt 1
{
	TR0=0;				         //关定时器0
	temp++;
	if(temp==40)
	{	
//	    getMulti_soilwaterdata();
		temp=0;
	}
	TH0 = 0x4C;
	TL0 = 0x00;
	TR0=1;
}
void main()
{	
	rece2Count=0;
	receCount=0;
	port_init();
	timer0_init();
	uart1_init();
	uart2_init();
	RS485E=0;

//	WDT_CONTR = 0x3E;    //启动看门狗复位，周期为4.5511s

	while(1)
	{

		if(RxFlag==1)
		{
//			if(crc_Check==1)
				readRegisters();
//				Uart2Sendstr(sendCount,sendBuf);								//处理接收数据
//			else if(crc_Check==2)
//				rep_Error();
			memset(receBuf,0,20);								//清零
			receCount=0;
			RxFlag = 0;
			crc_Check = 0;											//清除标志位
		}
		getSHTdata();  //采集数据SHT数据每次循环采集，还是收到modbus采集数据时再采集呢？？是否需要多次测量求平均？两次读取间隔至少0.8S,
		getBH1750data();    //采集数据BH1750光照数据

	    getMGS811data();    //MGS811数据
		getsoilwaterdata(); //土壤水分含量测量
		getsoiltempdata();  //土壤温度测量
//		WDT_CONTR = 0x3E;    //看门狗复位，周期为4.5511s
	}
}




