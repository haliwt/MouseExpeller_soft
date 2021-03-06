#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_AD.h"
#define		_KEY_ALL_OFF				   0X1F

//普通按键按下值
#define		_KEY_TRG_1_POWER     			0x01  //power key
#define		_KEY_TRG_2_SHARP     			0x02  //sharp key
#define		_KEY_TRG_3_MODE     			0x04  //works Mode key


//长按按键检查 按键值或者组合按键值
#define		_KEY_CONT_1_POWER     	     0x81    //电源按键长按--按键值
#define		_KEY_CONT_2_SHARP     		 0x82    //风速按键长按--按键值
#define		_KEY_CONT_3_MODE     	     0x84    //works Mode long press key



#define		_KEY_CONT_1     	    0x81    //按键计数值
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88
#define		_KEY_CONT_5     		0x90

typedef  struct  _state_
{
 unsigned char         read;
 unsigned char         buffer;
 unsigned char         value;
 unsigned short int    on_time;
 unsigned short int    off_time;
 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

key_types key;

xdata struct _worksMode worksMode;
/****************************************************
	*
	*Function Name: INT8U AutoDC_ReChargeStatus(void)
	*Function :
	*Inpute Ref: 
	*Return Ref: 
	*
*****************************************************/
INT8U AutoDC_ReChargeStatus(void)
{
	if(Auto_DCCharge ==1 || DC_Recharge  ==1 ){//�س�͵�Դ������DC�����⣬û������??
	     
		 	SysFlag = 0xff;	
            SetStop();
			RunMode = 1;
			RunStep = 0;
		     SetFan(0);
			SetEdge(0);	
		    	     
            if(BatteryRechargStatus ==1){
			   LedRedOff();
			   LedGreenON();
	  
	          return 1;
			 }
			else if(twinkle < 1 ){
					 LedRedOff();
				      LedGreenOff();
				}
				else{
				 if(twinkle > 2)twinkle =0;
					 LedGreenOff();
					  LedRedON();
					 
				  }
				  return 1;
			  }
			else 
			  return 0;
}
/******************************************************************************
 **
 ** Function Name:	static void	key_value_init(void)
 ** Function : 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
static void	key_value_init(void)
{
	key.read = 0;
	key.buffer = 0;
	key.value = 0;
	//key.inc_delay = 0;
	key.on_time = 0;
	key.off_time = 0;
	key.state = 0;
}

/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
INT8U KEY_Scan(void)
{
	INT8U  reval = 0;

	key.read = _KEY_ALL_OFF; //0x1F 
	g_KeyValueHigh=690;
    CheckKeyVoltage();

	//g_KeyValue= KEY_Voltage %100;//WT.EDIT 2021.01.05
	//SBUF =g_KeyValue;
	//power key
	if(g_KeyValue == 0)
    {
		key.read &= ~0x01; // 0x1f | 0xfe = 0x1E 
	}
	//light led key
	else if(g_KeyValue== 0x03 || g_KeyValue == 0x04)
    {
		key.read &= ~0x02; // 0x1f | 0xfd = 0x1D
	}
	//worksMode key
	else if(g_KeyValue == 0x07 || g_KeyValue == 0x08  )
    {
		key.read &= ~0x04; // 0x1f | 0xfb = 0x1B
	}
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //例如：key.buffer = 0x1E	  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
			}
			break;
		}
		case first:
		{
			if(key.read == key.buffer) //继续按下
			{
				if(++key.on_time> 80) //消抖  0.5us
				{
					
						key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						key.on_time = 0;
						key.state   = second;
					
				}
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second:
		{
			if(key.read == key.buffer) //再次确认按键是否按下
			{
				
				if(++key.on_time>13000)//长按按键，按键长按时间 3000个单位（时间）
				{
					key.value = key.value|0x80;  // 赋值，哪个按键按下的（返回值）key.value(P14) = 0x01 | 0x80 =0X81
					key.on_time = 0;  //运行时间 0
					
					key.state   = finish;  //进入下一case ：
				 }
			
				
			}
			else if(key.read == _KEY_ALL_OFF)  //按键松开,短按按键
			{
				if(++key.off_time>5) //松开按键消抖
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
					
					key.state   = finish; //一般按键按下状态
				}
			}
		   
			break;
		}
		case finish:
		{
			reval = key.value; //分两种情况： 1.普通按键的按下返回值 TIMER_KEY = 0x04 
			                    // 2.长按键返回值：TIMER_KEY = 0X84
			key.state   = end;
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>10)
				{
					key.state   = start;
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
			break;
		}
	}
	return  reval;
}
/******************************************************************************
 **
 ** Function Name:	void KEY_FUNCTION(void)
 ** Function : receive key input message 
 ** Input Ref:NO
 ** Return Ref:NO
 **   
 ******************************************************************************/
 void KEY_Handing(INT8U key)
{
      static INT8U pressflg =0,n,m;
	   INT8U keyflg =0;
	  //keyflg = KEY_Scan();
	 switch(key)
	{
		 case 0x00://_KEY_TRG_1_POWER   : 
		    // RunMode =1 ;
			 pressflg =pressflg ^ 0x01;
			 if(pressflg==1){
			     worksMode.iPowerFlag=1;
				 LED_R=0;
			 	}
			 else {
			    worksMode.iPowerFlag=0;
				LED_R=1;
			 	}
			
			
	   break;

		 case 0x04://_KEY_TRG_2_SHARP:
			RunMode =2 ;
			  n=n ^ 0x01;
			 if(n==1){
			    LED_G=0;
				SharpTime_Hz=0;
				SharpWorksTime_Total=0;
				SharpWorksTime=0;
				RunMode =2;

			 }
			 else 
			    LED_G=1;
			 
	   break;

		 case 0x08: //_KEY_TRG_3_MODE :
	   	     //RunMode =3 ;
			  m=m ^ 0x01;
			 if(m==1)
			    LED_B=0;
			 else 
			    LED_B=1;
			 
	   break;

	   case _KEY_CONT_3_MODE : //0x84 long press key
	        // RunMode =4 ; //works mode transform 
	   		LED_R=1;
			LED_B=1;
			LED_G=1;
          
	   break;
	   default:
		
	   break;

	}
	

}


void Sharp_LED(INT8U sharp)
{
   switch(sharp){
	   case 1:
		//10HZ ,50% ,T= 100ms works =1s stop =4s total =60s 10HZ
	   if(SharpWorksTime_Total<=60){
		   if(SharpWorksTime <=1){
			   if(SharpTime_Hz <=5 ){ //50ms
				  P2_0 =1;
				}
			   else if(SharpTime_Hz <=10 && SharpTime_Hz >5 ){
				 P2_0=0;
				 
				}
			   if(SharpTime_Hz>=10)SharpTime_Hz=0;
		   }
		   else  if(SharpWorksTime > 1 && SharpWorksTime <=5){
				P2_0=0;
			    
		   }
		   else if(SharpWorksTime > 5) SharpWorksTime =0;
	   }
	   else {

		 SharpWorksTime_Total =0;
		  SharpWorksTime =0;
		  SharpTime_Hz=0;
		 P2_0=0;
		 sharp=2;

	   }
	   
   break;
	   
	   case 2://5Hz 
		  //5HZ ,50% ,T= 200ms ,works =2s stop =8s total =120s 
	   if(SharpWorksTime_Total<=120){
		   if(SharpWorksTime <=2){
			   if(SharpTime_Hz <=10 ){ //
				  P2_0 =1;
				}
			   else if(SharpTime_Hz <=20 && SharpTime_Hz >10 ){
				 P2_0=0;
				 
				}
			   if(SharpTime_Hz>=20)SharpTime_Hz=0;
		   }
		   else  if(SharpWorksTime > 2 && SharpWorksTime <=10){
				  P2_0=0;
			      
			
		   }
		   else if(SharpWorksTime > 10) SharpWorksTime =0;
	   }
	   else {

		  SharpWorksTime_Total =0;
		  SharpWorksTime =0;
		  SharpTime_Hz=0;
		 P2_0=0;
		 sharp =3;

	   }
	   
	   
	   break;
	   case 3:
		     //3HZ ,50% ,T= 333ms ,works =3s stop =12s total =150s 
	   if(SharpWorksTime_Total<=150){
		   if(SharpWorksTime <=3){
			   if(SharpTime_Hz <=16 ){ //333/2= 166ms
				  P2_0 =1;
				}
			   else if(SharpTime_Hz <=32 && SharpTime_Hz >16 ){
				 P2_0=0;
				 
				}
			   if(SharpTime_Hz>=32)SharpTime_Hz=0;
		   }
		   else  if(SharpWorksTime > 3 && SharpWorksTime <=15){
				  P2_0=0;
			}
		   else if(SharpWorksTime > 15) SharpWorksTime =0;
	   }
	   else {

		 SharpWorksTime_Total =0;
		  SharpWorksTime =0;
		  SharpTime_Hz=0;
		 P2_0=0;
		 sharp =1;

	   }
	   
	   break;

}
 }

