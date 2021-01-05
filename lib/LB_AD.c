/*

---------- file information -----------------------------------------------
file name: 
define   : <锟侥硷拷说锟斤拷>
version  : 锟斤拷锟侥硷拷尾锟斤�?
---------------------------------------------------------------------------
*/

//全锟街憋拷锟斤拷锟斤拷锟斤拷
#define  KAKA_AD_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "..\lib\LB_Led.h"
#include "LB_AD.h"

#endif
/**
  * @说锟斤拷  	锟斤拷时锟斤拷锟斤拷
  * @锟斤拷锟斤拷  	fui_i : 锟斤拷时时锟斤拷
  * @锟斤拷锟斤拷�?锟斤�?
  * @�?	Fcpu = 16MHz,fui_i = 1�?锟斤拷时时锟斤拷约为2us
  */
void Delay_2us(unsigned int fui_i)
{
	while(fui_i--);	
}
void InitADIO(void)
{
	P0M0 = 0x02;				        //P0_0 --setup GPIO analog input
	P0M1 = 0x02;				        //P0_2 ---setup GPIO analog input
	P0M2 = 0x02;				        //P03锟斤拷锟斤拷为模锟斤拷锟斤拷锟斤�?
	P0M4 = 0x02;				        //P04锟斤拷锟斤拷为模锟斤拷锟斤拷锟斤�?
	P0M5 = 0x02;				        //P05锟斤拷锟斤拷为模锟斤拷锟斤拷锟斤�?
	P0M6 = 0x02;				        //P06锟斤拷锟斤拷为模锟斤拷锟斤拷锟斤�?
	P0M7 = 0x02;				        //P07锟斤拷锟斤拷为模锟斤拷锟斤拷锟斤�?
	P2M2 = 0x02;				        //P2_2 ---AN10 key input analog 
	                     

   ///*
    P3M0 = 0xC2;  //WT.EDIT crash        //P20-Push-pull output "�������"
    P3M1 = 0xC2;  //WT.EDIT ground      //P03-Puse-pull output "�������"
	PWM2_MAP = 0X31;//0x03;				//PWM2 P3_1    --GPIO map to GPIO P0_3
	PWM21_MAP = 0X30;//0x20;					//PWM1通锟斤拷映锟斤拷P03锟斤�?
    PWM2C = 0x00;						//PWM1锟斤拷锟斤拷效锟斤拷PWM11锟斤拷锟斤拷效锟斤拷时锟斤拷8锟斤拷频 
    PWMM |= 0x40;						//PWM1锟斤拷锟斤拷锟斤�?


	PWM2PH = 0x0;						//锟斤拷锟节革�?位锟斤拷锟斤拷为0x03
	PWM2PL = 0x10;						//锟斤拷锟节碉�?位锟斤拷锟斤拷为0xFF



	PWM2DH = 0x00;						//PWM1锟斤�?位占锟秸憋拷0x01
	PWM2DL = 0x02;						//PWM1锟斤�?位占锟秸憋拷0x55
	PWM2DTH = 0x00;						//PWM1锟斤�?位占锟秸憋拷0x01
	PWM2DTL = 0x02;						//PWM1锟斤�?位占锟秸憋拷0x55
	PWMEN |= 0x44;						//使锟斤拷PWM2
   //*/

}

void SeleADChanel(INT8U ADChanel)
{
	ADCC0 = 0x81;						//锟斤拷ADC转锟斤拷锟斤拷源
	ADCC1 = (ADChanel&0X0F);			//选锟斤拷锟解部通锟斤拷0
	ADCC2 = 0x4f;						//转锟斤拷锟斤拷锟�?2位锟斤拷锟捷ｏ拷锟斤拷锟斤拷锟揭讹拷锟诫，ADC时锟斤拷16锟斤拷频

}

void StartAD()
{
	ADCC0&=0XDF;            //internal voltage is 3V
	ADCC0 |= 0x40;			//ref: VDD
}
void SetADINT(void)
{
    EADC = 1;             //ADC transform
    EA = 1;
}

/**********************************************************************
	*
	*Function Name:void  SetAD(INT8U ADChanel)
	*Function:AD transform
	*Input Ref: analog input channel 
	*
	*
**********************************************************************/
void  SetAD(INT8U ADChanel)
{
  code INT8U ADCC[9]={2,1,0,3,4,5,6,7,10}; //WT.EDIT.2021.01.02
  SeleADChanel(ADCC[ADChanel]);
  SetADINT();
  StartAD();
}
/**********************************************************************
	*
	*Function Name:void  void ReadAD5ms()
	*Function:AD transform
	*Input Ref: NO
	*Output Ref: NO
	*
**********************************************************************/
void ReadAD5ms()
{
  static INT8U i=0;
  static INT8U chanel=0;
  static INT16U ADtemp[5];  
  ADtemp[i]=ADCR;
  i++;
  if(i>2)
  {
     i=0;
	 AD5ms[chanel]=ADtemp[2]; //(ADtemp[1]+ADtemp[2])/2;
	 //AD5ms[5]=0xaa;
	 chanel++;
	 if(chanel>8)
	 {
	   if(ADCtl)
	   { 
		   if(ADFlag)  //锟斤拷锟斤拷PMW 占锟秸憋�?锟斤拷锟斤拷锟斤拷IR锟斤拷锟斤拷   锟截筹拷 锟斤拷锟秸凤拷锟斤拷徒锟斤拷盏锟�?锟斤拷锟绞点�?
		   {
			 //P0_3 = 1;
			  PWM2DL = 0x8; // 
			  PWM2DTL = 0x8;
			 ADFlag=0;
			 ADFlashFlag=1;
		   }
		  else
		  {
			 //P0_3 = 0; // 
			 PWM2DL = 0x1;
			 PWM2DTL = 0x1;
			 ADFlag=1;
			 ADFlashFlag=1;
		  }
	  }
	  else
	  {
	  	 //P0_3 = 0;
		 PWM2DL = 0;
		 PWM2DTL = 0;
	  }
		//SBUF=(AD5ms[1]>>4);
		//SBUF=AD5ms[2]/16;
	 chanel=0;
	 }
  }
  else
  {
  	 SetAD(chanel);
  }
}
/*
INT8U ReadWallDp(INT8U *p)
{
  INT8U i;
  INT16U temp,tempMin,tempMax;
  temp=0;


  tempMin=*p;
  tempMax=*p;
  for(i=1;i<10;i++)
  {
    
	if(tempMin>*(p+i))
	{
	   tempMin=*(p+i);
	}
	else if(tempMax<*(p+i))
	{
	   tempMax=*(p+i);
	}
	else
	 temp+=*(p+i);
  }
  
  return(temp/8);
}
*/
void CheckWall()
{
 if(ADFlashFlag)
 {
   if(ADFlag)
   {
   	   WallAD[0][0]=(AD5ms[4]>>4);
	   WallAD[1][0]=(AD5ms[3]>>4);
	   WallAD[2][0]=(AD5ms[1]>>4);
 	   WallAD[3][0]=(AD5ms[2]>>4);
	   ADFlashFlag=0;
	 //SBUF=WallAD[0][0];
    if(WallAD[0][1]>WallAD[0][0])
	{
       WallAD100Ms[0][ADTime]=WallAD[0][1]-WallAD[0][0];
	}
	else
       WallAD100Ms[0][ADTime]=WallAD[0][0]-WallAD[0][1];

    if(WallAD[1][1]>WallAD[1][0])
	{
       WallAD100Ms[1][ADTime]=WallAD[1][1]-WallAD[1][0];
	}
	else
	  WallAD100Ms[1][ADTime]=WallAD[1][0]-WallAD[1][1];

    if(WallAD[2][1]>WallAD[2][0])
	{

       WallAD100Ms[2][ADTime]=WallAD[2][1]-WallAD[2][0];
	}
	else
	  WallAD100Ms[2][ADTime]=WallAD[2][0]-WallAD[2][1];

    if(WallAD[3][1]>WallAD[3][0])
	{

       WallAD100Ms[3][ADTime]=WallAD[3][1]-WallAD[3][0];
	}
	else
	  WallAD100Ms[3][ADTime]=WallAD[3][0]-WallAD[3][1];

    LCurrentAD[ADTime]=AD5ms[5];
	RCurrentAD[ADTime]=AD5ms[6];
	FanCurrentAD[ADTime]=AD5ms[7];
	EdgeCurrentAD[ADTime]=AD5ms[8];
	 ADTime++;
   if(ADTime>7)
   {
   	  ADTime=0;
	  WallDp[0]=(WallAD100Ms[0][0]+WallAD100Ms[0][2]+WallAD100Ms[0][4]+WallAD100Ms[0][6])/4;
	  WallDp[1]=(WallAD100Ms[1][0]+WallAD100Ms[1][2]+WallAD100Ms[1][4]+WallAD100Ms[1][6])/4;
	  WallDp[2]=(WallAD100Ms[2][0]+WallAD100Ms[2][2]+WallAD100Ms[2][4]+WallAD100Ms[2][6])/4;
	  WallDp[3]=(WallAD100Ms[3][0]+WallAD100Ms[3][2]+WallAD100Ms[3][4]+WallAD100Ms[3][6])/4;
   }
   //SBUF=AD5ms[6];///16;

	//SBUF=AD5ms[6];  
   }
   else
   {


   	   WallAD[0][1]=(AD5ms[4]>>4);
	   WallAD[1][1]=(AD5ms[3]>>4);
	   WallAD[2][1]=(AD5ms[1]>>4);
 	   WallAD[3][1]=(AD5ms[2]>>4);
	   ADFlashFlag=0;
   }

 }
}
void CheckEdgeCurrent()
{

 //EdgeCurrent=(EdgeCurrent*9+((AD5ms[8])/2))/10;
  EdgeCurrent=(EdgeCurrentAD[0]+EdgeCurrentAD[2]+EdgeCurrentAD[4]+EdgeCurrentAD[6])/4;
 //EdgeCurrent=0xaabb;
 if(EdgeCurrent>0x80)
 EdgeCurrentCount++;
 else 
 {
   if(EdgeCurrentCount>1)
     EdgeCurrentCount--;
 }
}

void CheckFanCurrent()
{

 FanCurrent=(FanCurrentAD[0]+FanCurrentAD[1]+FanCurrentAD[2]+FanCurrentAD[3]+FanCurrentAD[4]+FanCurrentAD[5]+FanCurrentAD[6]+FanCurrentAD[7])/64;
 //FanCurrent=0xaabb;
// FanCurrentCount++;

}

void CheckLCurrent()
{
 INT16U	LCurrentADAvg;
 LCurrent=(LCurrentAD[0]+LCurrentAD[2]+LCurrentAD[4]+LCurrentAD[6])/4;
 //SBUF= (INT8U)LCurrentADAvg;
 //LCurrent=(LCurrent*9+(LCurrentADAvg*9)/2)/10;

}
void CheckRCurrent()
{
 INT16U	RCurrentADAvg;
 RCurrent=(RCurrentAD[0]+RCurrentAD[2]+RCurrentAD[4]+RCurrentAD[6])/4;

 //RCurrent=(RCurrent*9+(RCurrentADAvg*11)/2)/10;
 //RCurrent=(RCurrent*9+(RCurrentADAvg*9)/2)/10;
 //4000*100/4096/22
 
}

void CheckVoltage()
{
	 
    //Voltage=(Voltage*9+((AD5ms[0])/25)*6)/10;
   Voltage=(Voltage*9+(AD5ms[0]/4))/10;
   //4000*3/40960
}
/**********************************************************************
	*
	*Function Name:CheckKeyVoltage(void)
	*Function:AD transform
	*Input Ref: NO
	*Output Ref: NO
	*
**********************************************************************/
INT8U  CheckKeyVoltage(void)
{
   INT8U ad[20],i,j,z;
   INT16U adcValue;
   SetAD(8);
	
   KEY_Voltage=(Voltage*9+(AD5ms[8]/4))/10;
   //KEY_Voltage=adcValue;
   //4000*3/40960
   #if 0
   i++;
   ad[i-1]=adcValue /100;
   if(i==20){
      i=0;
	  z=1;
	 for(j=0;j<20;j++){

       KEY_Voltage=KEY_Voltage+ad[j];
	   
     }
	 
       KEY_Voltage= KEY_Voltage/20;
	   
	}
   if(z==1){
      return KEY_Voltage;
	  z=0;
   }
   #endif 
 }
/***************************************************************************************
  * @说锟斤拷  	ADC锟叫断凤拷锟斤拷锟斤�?
  *	@锟斤拷锟斤拷	锟斤�?
  * @锟斤拷锟斤拷�?锟斤�?
  * @�?	锟斤�?
***************************************************************************************/
void ADC_Rpt() interrupt ADC_VECTOR
{

    IE1 &=~ 0x40;                       //锟截憋拷ADC锟叫讹拷
    ADCC0 &=~ 0x20;						//锟斤拷锟紸DC锟叫断憋拷志�?

} 