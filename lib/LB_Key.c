#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_AD.h"
xdata struct _CleanMode cleanWorks;
/****************************************************
	*
	*Function Name: uint8_t HDKey_Scan(uint8_t mode)
	*Function :
	*Inpute Ref: 0 ---不支持连续按键
	*Return Ref: 0 --没有按键按下， 1---有按键按下
	*
*****************************************************/
#if 0
INT8U HDKey_Scan(INT8U mode)
{
	
  static INT8U key_up=1;  //°´¼üËÉ¿ª±êÖ¾
  static INT8U keyOnFlag = 0;
 
  if(keyOnFlag){
   if(Power_Key==0 && Cleaning_Key==0){
    keyOnFlag = 0;
   }
   else
    return 0;
  }
   
 
  if(mode==1)key_up=1; // 支持连续按键
    if(key_up&&(Power_Key==1||Cleaning_Key==1)){
       Delay_ms(5);
       key_up =0 ;
       keyOnFlag = 1;
       if((Power_Key== 0) && Cleaning_Key ==0)  return GROUP_PRES ;
   
       else if (Cleaning_Key ==0) return CLEANING_PRES;
  
        else if(Power_Key== 0)  return POWER_PRES;

       }
     else if(Power_Key==0 && Cleaning_Key==0 )key_up=1;
  return 0; //没有按键按下
}
#endif 
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


