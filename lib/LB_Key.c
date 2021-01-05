#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_AD.h"
xdata struct _CleanMode cleanWorks;
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


