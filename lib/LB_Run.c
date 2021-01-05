/*

---------- file information -----------------------------------------------
file name:
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#include "LB_Usart.h"
#include "..\lib\LB_Key.h"

#endif
#include "..\lib\LB_Key.h"
/*******************************************************
  * @?|¨¬???  	?¡§?¡§o?¨¤o?£¤¡§oy
  * @2?¡§oy  	fui_i : ?¡§?¡§o?¨¤¡§o?¨¤??
  * @?¡è|¨¬???|¨¬ ?T
  * @?¨¢?¨¦ 	Fcpu = 16MHz?¨º?fui_i = 1¡§o?¨¤?¨º??¡§?¡§o?¨¤¡§o?¨¤?????a1Ms
**************************************************************/
void Delay_ms(INT16U fui_i)
{
	INT16U fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}
/*******************************************************
  * @?|¨¬???  	?¡§?¡§o?¨¤o?£¤¡§oy
  * @2?¡§oy  	fui_i : ?¡§?¡§o?¨¤¡§o?¨¤??
  * @?¡è|¨¬???|¨¬ ?T
  * @?¨¢?¨¦ 	Fcpu = 16MHz?¨º?fui_i = 1¡§o?¨¤?¨º??¡§?¡§o?¨¤¡§o?¨¤?????a1Ms
**************************************************************/
INT8U readRunTime()
{
	INT8U i;
	if(Voltage>820)
		i=35;
	else if(Voltage>810)
		i=36;
	else if(Voltage>800)
		i= 36;
	else if(Voltage>790)
		i= 37;
	else if(Voltage>780)
		i= 38;
	else if(Voltage>770)
		i= 38;
	else if(Voltage>760)
		i= 39;
	else if(Voltage>750)
		i= 39;
	else if(Voltage>740)
		i= 40;
	else if(Voltage>730)
		i= 40;
	else if(Voltage>720)
		i= 41;
	else if(Voltage>710)
		i= 42;
	else if(Voltage>700)
		i= 43;
	else if(Voltage>690)
		i= 43;
	else if(Voltage>680)
		i= 44;
	else if(Voltage>670)
		i= 45;
	else if(Voltage>660)
		i= 45;
	else if(Voltage>650)
		i= 46;
	else if(Voltage>640)
		i= 47;
	else if(Voltage>630)
		i= 48;
	else if(Voltage>620)
		i= 49;
	else
		i= 61;
	return (i+40);
}
/***********************************************************************
 * ***
 *Function Name:void ReChargeBattery(void) 
 *Function :Auto recharge batter 
 * 
 * 
 * 
 * 
************************************************************************/
void Auto_ReChargeBattery(void)
{
	static INT8U j,z,i,w;


 
  switch(RunStep)
	{
		case 0:
		{
			InitMotorForward();			
			RunStep=1;
			ClearAllIR();
			RunMs = 0;			
		}
			break;
		
		case 1:
		{
			if(RunMs>30)
			{
				RunMs=0;
				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearPreLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.NearRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarMid>0)
				{
					RunStep=0x40;
					InitMotorForwardSlow();
				}
				else if(IRLocation.FarPreRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarPreLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else
				{

				}
				ClearAllIR();
			}
		}
		break;
		
		//far target 
		case 0x40:
		{
			if(RunMs>30)
			{
				RunMs=0;
				#if 0
				if(SendCount>=12)
				{
					Usart1Send[0]=12;
					Usart1Send[1]=IRLocation.NearMid;
					Usart1Send[2]=IRLocation.NearPreRight;
					Usart1Send[3]=IRLocation.NearPreLeft;
					Usart1Send[4]=IRLocation.NearRight;
					Usart1Send[5]=IRLocation.NearLeft;
					Usart1Send[6]=IRLocation.FarMid;
					Usart1Send[7]=IRLocation.FarPreRight;
					Usart1Send[8]=IRLocation.FarPreLeft;
					Usart1Send[9]=IRLocation.FarRight;
					Usart1Send[10]=IRLocation.FarLeft;
					Usart1Send[11]=RunNoIRsenorLastStep;
					Usart1Send[12]=RunStep;
					SendCount=1;
					SBUF=Usart1Send[SendCount];
				}
				#endif 
				if(IRLocation.FarMid>0 )
				{
                    if(Mid_ReadIR.ReadIR[0] ==0x11|| Mid_ReadIR.ReadIR[0] ==0x86||Mid_ReadIR.ReadIR[0] ==0x84 \
						  ||Mid_ReadIR.ReadIR[0] ==0x18  ||Mid_ReadIR.ReadIR[0] ==0xA8|| Mid_ReadIR.ReadIR[0]==0X44\
							||Mid_ReadIR.ReadIR[0] ==0x8A)
					        InitMotorForwardSlow();
							RunNoIRsenorTime=0;
							RunNoIRsenorLastStep=1;
					        RunStep=0x50;
				}
		
				else if(IRLocation.FarPreRight>0 ||IRLocation.FarRight>0 )
				{
          if(Mid_ReadIR.ReadIR[0] ==0xAA){
						InitMotorForwardSlow();
						RunStep=0x50;
					}
				  else{
						RunStep=0x50; //CCW
						InitMotorForwardSlow();
						RunNoIRsenorTime=0;
						RunNoIRsenorLastStep=2;
				  }
				}
				else if(IRLocation.FarLeft>0 ||IRLocation.FarPreLeft>0)
				{
					if(Mid_ReadIR.ReadIR[0] ==0xA1){
				     InitMotorForwardSlow();// InitMotorForwardRightSlow();
					  RunStep=0x50;
					}
					else{
						  RunStep=0x50; //CW
						  InitMotorForwardSlow();
						RunNoIRsenorTime=0;
						RunNoIRsenorLastStep=3;
							
					
				}
			  }
				else if (Mid_ReadIR.ReadIR[0] !=0){
					
						 
						RunStep=0x47;
						RunMs = 0;

					
				}
				else if (Mid_ReadIR.ReadIR[0] ==0){

						Mid_ReadIR.ReadIR[0]=0;
		                w ++ ;
				        if(w==1){
							 RunStep=0x43; //CCW
							RunMs = 0;
				        }
						else{
							 RunStep=0x47; //CW
							RunMs = 0;
							w=0;
						}
				

				}
				ClearAllIR();
			}
		}
		break;
		
		break;
		

		case 0x43 ://CCW
               if(RunMs< 3){

				InitMotorLeft();//CCW 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x44;


			   }


		break;

		case 0x44 :

	          j++ ;
			 SetStop();
			 Delay_ms(500);
		  
			 if(j ==1)
			   IRLocation.CloseList[0]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[1]=Mid_ReadIR.ReadIR[0];
				 j=0;
              }

			 if(IRLocation.irRightValue==1)
			 {
				RunStep = 0x45; //line 
				RunMs = 0;
				IRLocation.irRightValue=0;

			 }
			 else {
			 if(IRLocation.CloseList[1] >IRLocation.CloseList[0]){

			 			RunStep = 0x45;//line run 
						RunMs = 0;
			           IRLocation.irLeftValue =1 ;
			   }
			 else if(IRLocation.CloseList[1] < IRLocation.CloseList[0]){

			 			RunStep = 0x47;//CW
						RunMs = 0;
             }
			 else if(IRLocation.CloseList[1] ==IRLocation.CloseList[0] && IRLocation.CloseList[0]!=0 ){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
			 
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[1] && IRLocation.CloseList[1]!=0){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
			 else{

			     	  RunMs =0 ;
				      RunStep = 0x01;

				 }
			 	}        
                  


		break;

		case 45:  //line
			 if(RunMs< 10){

                InitMotorForwardSlow();//line run 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x46;

               }


		break;

		case 0x46:
			 
			 SetStop();
			 Delay_ms(500);
		      i++;
			 if(i ==1)
			   IRLocation.CloseList[2]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[3]=Mid_ReadIR.ReadIR[0];
				 i=0;
              }


			 if(IRLocation.CloseList[3] >IRLocation.CloseList[2]){

			 			RunStep = 0x45;
						RunMs = 0;
			 }
//			 else if(IRLocation.CloseList[3] < IRLocation.CloseList[2]){
//
//			 			RunStep = 0x01;
//						RunMs = 0;
//             }
			 else if(IRLocation.CloseList[3] ==IRLocation.CloseList[2] && IRLocation.CloseList[2]!=0 ){
                       // RunStep = 0x45;
                        IRLocation.NearMid++;
						//RunStep = 0x50;
						//RunMs = 0;

						RunStep = 0x45;
						RunMs = 0;
						
			 }
			else{

			
			      RunMs =0 ;
				  RunStep = 0x01;
			 
			}

		break;
		
		case 0x47 : //cw
               if(RunMs< 3){

                InitMotorRight();//CW 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x46;

               }


		break;




		case 0x48:
			   z++ ;
			 SetStop();
			 Delay_ms(500);
			 if(z ==1)
			   IRLocation.CloseList[4]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[5]=Mid_ReadIR.ReadIR[0];
				 z=0;
              }
			 
			 if(IRLocation.irLeftValue ==1){

                        RunStep = 0x45; //line 
						RunMs = 0;
			            IRLocation.irLeftValue =0;



			 }
             else {
			 if(IRLocation.CloseList[5] >IRLocation.CloseList[4]){

			 			RunStep = 0x45; //line 
						RunMs = 0;

             }
			
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[4] && IRLocation.CloseList[4]!=0 ){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
		
			 else if(IRLocation.CloseList[5] <IRLocation.CloseList[4]){
			 	        RunStep = 0x43; //CW
						RunMs = 0;
			 			IRLocation.irRightValue=1;

			 }
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[1] && IRLocation.CloseList[1]!=0){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
              else {
			            RunMs =0 ;
				        RunStep = 0x01;
             
                }
             	}

		break;

       case 0x50:
		{
            i=0;
			if(RunMs>30)
			{
				RunMs=0;
				#if 0
				if(SendCount>=12)
				{
					Usart1Send[0]=12;
					Usart1Send[1]=IRLocation.NearMid;
					Usart1Send[2]=IRLocation.NearPreRight;
					Usart1Send[3]=IRLocation.NearPreLeft;
					Usart1Send[4]=IRLocation.NearRight;
					Usart1Send[5]=IRLocation.NearLeft;
					Usart1Send[6]=IRLocation.FarMid;
					Usart1Send[7]=IRLocation.FarPreRight;
					Usart1Send[8]=IRLocation.FarPreLeft;
					Usart1Send[9]=IRLocation.FarRight;
					Usart1Send[10]=IRLocation.FarLeft;
					Usart1Send[11]=IMP;
					Usart1Send[12]=RunStep;
					SendCount=1;
					SBUF=Usart1Send[SendCount];
				}
				#endif 
				if(IRLocation.NearMid>0)
				{
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.NearPreRight>0)
				{

					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearPreLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.NearRight>0)
				{
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarMid>0)
				{
					//RunStep=0x50;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.FarPreRight>0)
				{
					//RunStep=0x53;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarPreLeft>0)
				{
					//RunStep=0x56;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarRight>0)
				{
					//RunStep=0x59;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarLeft>0)
				{
					//RunStep=0x5c;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else
				{
					RunNoIRsenorTime++;
					if(RunNoIRsenorTime>4)
					{

						RunNoIRsenorTime=0;
						if(RunNoIRsenorLastStep==1)
						{

						}
						else	if(RunNoIRsenorLastStep==2)
						{
							InitMotorForwardRightSlow();
							RunNoIRsenorTime=0;
							RunStep=0x1;
						}
						else	if(RunNoIRsenorLastStep==3)
						{
							InitMotorForwardLeftSlow();
							RunNoIRsenorTime=0;
							RunStep=0x1;
						}


					}
				}
				ClearAllIR();
			}
		}
		
	}
}
		
		
		
	
		
	
    

/***********************************************************************
 * ***
 *Function Name:void ReChargeBattery(void) 
 *Function :void CleanMode_BOW(void)
 * 
 * 
 * 
 * 
************************************************************************/
void CleanMode_BOW(void)
{

// ����
	
		
		switch(RunStep)
		{
		case 0:
		{

		}
		break;
		case 1:
		{
		   //InitMotorLeft();
			InitMotorForward();
			RunStep=2;
		}
		break;
		case 2:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=30;
				CurrentMax++;
			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
			break;
		case 3:
		{
			if(RunMs>90)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}
			break;
        }
		case 4:
		{
			if(RunMs>90)
			{
				SetStop();
				RunMs=0;
				RunStep=5;
			}
		}
			break;
		case 5:
		{
			if(RunMs>20)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=6;
			}
		}
			break;

		case 6:
		{
			if(RunMs>readRunTime())
			{
				SetStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=7;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorRetreat();
				RunMs=30;

			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}

        }
			break;
		case 7:
		{
			if(RunMs>40)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=8;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 8:
		{
			if(RunMs>150)
			{
				SetStop();
				RunMs=0;
				RunStep=9;

			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;
			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorLeftMax();
				RunMs=0;
				CurrentMax++;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=9;
			}
		}
			break;
		case 9:
		{
			if(RunMs>90)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=10;
			}
		}
			break;

		case 10:
			if(RunMs>readRunTime())
			{

				{
					//InitMotorForward();
					SetStop();
					RunMs=0;
					RunStep=11;
					LCurrent=0;
					RCurrent=0;
				}
			}

			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorRetreat();
				RunMs=20;

			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorLeftMax();
				RunMs=0;

			}


			break;
		case 11:
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x12;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;

			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;

			}
			break;
		case 0x12:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=10;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=20;

			}
			else if(IMP>0)
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;
			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
		break;
		case 0x13:
		{
			if(RunMs>30)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x14;
			}
			break;
		}
		case 0x14:
		{
			if(RunMs>90)
			{
				SetStop();
				RunMs=0;
				RunStep=0x15;
			}
		}
			break;
		case 0x15:
		{
			if(RunMs>10)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=0x16;
			}
		}
			break;

		case 0x16:
		{
			if(RunMs>readRunTime())
			{
				SetStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=0x17;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;

			}
 			else if(IMP>0)
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;
			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;

			}

	   }
			break;
		case 0x17:
		{
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x18;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x18:
		{
			if(RunMs>150)
			{
				SetStop();
				RunMs=0;
				RunStep=0x19;

			}
			else  if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		}
			break;
		case 0x19:
		{
			if(RunMs>20)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=0x1a;
			}
			}
			break;

		case 0x1a:
		{
			if(RunMs>readRunTime())
			{
				//InitMotorForward();
				SetStop();
				RunMs=0;
				RunStep=0x1b;
				LCurrent=0;
				RCurrent=0;

			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		}
			break;
		case 0x1b:
		{
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x2;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		   }
			break;

		}
		
	
}
/***********************************************************************
 * ***
 *Function Name:void CleanMode_Random(void)
 *Function :void CleanMode_BOW(void)
 * 
 * 
 * 
 * 
************************************************************************/
void CleanMode_Random(void)
{
	   
	  	switch(RunStep)
		{
		case 0:
		{

		}
		break;
		case 1:
		{

			InitMotorForward();
			RunStep=2;
		}
		break;
		case 2:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=10;
				CurrentMax++;
			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
			break;
		case 3:
		{
			if(RunMs>30)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}
			break;
        }
		case 4:
		{
			if(RunMs>150)
			{
				SetStop();
				RunMs=0;
				RunStep=5;
			}
		}
			break;
		case 5:
		{
			if(RunMs>20)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=6;
			}
		}
			break;

		case 6:
		{
			if(RunMs>readRunTime())
			{
				//SetStop();
				InitMotorForward();
				RunMs=0;
				RunStep=2;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=3;
				InitMotorRetreat();
				RunMs=10;

			}
      else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}

        }
			break;			
			}
}
/**********************************************************************
 * 	*
    *Function Name:void  CheckRun()
	*Function: 
	*Input Ref:NO
	*Return Ref: NO
	*
***********************************************************************/
void  CheckRun()
{
   switch(RunMode) {

	        case 0:
						
			break;    
			case 1 : // powern on
			    
           		    LED_R = 0;
				    RunStep = 0;
				    DiffMode =1;
			        P2_0 =0;
			
            break;

			case 2: //sharp led function
				if(DiffMode ==2 && DiffMode !=1){
					LED_G = 0;
					LED_B=0;
					RunStep = 0x01;
					Sharp_LED(1);
				}
				else{
				
				  RunStep = 0;
				}
				break; 

			case 3: //works mode function
			       LED_B=0; 
					//wallMode();
			
				break;

			case 4: //mode transform function 
				
				break;

			case 5:
			//	Auto_ReChargeBattery();
				rechargeBatMode();
				break;
			
			default:
				break;
   }
   switch(RunStep){

       case 0:
		   
	   break;
	   case 0x01:
          Sharp_LED(1);
          RunStep = 0x01;
      break;





   }
}


/****************************************************************
 * *
 * * * Function Name:void circleMode(void)
 *     Function: 
 * 
 * 
*****************************************************************/
void circleMode(void)
{
 		switch(RunStep)
		{
			case 0:
			{

			}
				break;

			case 1:  //��ʼԭ����תȦ
			{								
				InitMotorRightCircle();
				RunStep=2;
				RunMs=0;
			}
				break;

			case 2:  //normal run
			{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else 
					if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else if(RunMs>600)
				{
					InitMotorForwardRightUp1();
					RunStep = 0x10;
					RunMs = 0;
					CurrentMax = 0;
				}
			}
				break;
			
			case 3:   //����
			{
				if(RunMs>30)
				{
					InitMotorRetreat();
					RunMs=0;
					RunStep=4;
				}
			}
				break;
			
			case 4:  //ֹͣ
			{
				if(RunMs>40)
				{
					SetStop();
					RunMs=0;
					RunStep=5;
				}
			}
				break;

			case 5:  //ת��
			{
				if(RunMs>20)
				{
					InitMotorLeftCircle();
					RunMs=0;
					RunStep=6;
				}
			}
				break;

			case 6:  //ֱ��
			{			
				if(RunMs>150)
				{
					InitMotorForward();
					RunMs=0;
					RunStep=7;
				}	
			}
				break;			
					
			case 7:
			{
			if(RunMs>300)  //ֱ��һ�ξ��룬Ȼ��ת��
				{
					SetStop();				
					RunStep=1;				
					RunMs=0;
					LCurrent=0;
					RCurrent=0;
				}
				else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=3;
					InitMotorRetreat();
					RunMs=10;

				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}			
			}
				break;
			
						
			//����Ȧ
			case 0x10:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2000)
				{
					InitMotorForwardRightUp2();
					RunStep = 0x11;
					RunMs = 0;
					CurrentMax = 0;
				}
			}
				break;
			
			//����Ȧ
			case 0x11:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>1400)
				{
					InitMotorForwardRightUp3();
					RunStep = 0x12;
					CurrentMax = 0;
					RunMs=0;
				}
			}
				break;	

			//����Ȧ
			case 0x12:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>1100)
				{
					SetStop();
					RunStep=0x06;
					RunMs= 75;
					CurrentMax = 0;
				}
			}
				break;	

#if 0   
			case 0x08:   //ԭ����ת
			{
				InitMotorLeftCircle();
				RunStep= 0x02;
				rightLeftFlag = 0;
				RunMs=0;				
			}
				break;			
			
			
			//����Ȧ
			case 0x20:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>1000)
				{
					InitMotorForwardLeftUp2();
					RunStep = 0x21;
					CurrentMax = 0;
					RunMs=0;
				}
			}
				break;
			
			//����Ȧ
			case 0x21:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2000)
				{
					RunMs=0;
					InitMotorForwardLeftUp3();
					RunStep = 0x22;
					CurrentMax = 0;
				}
			}
				break;	

			//����Ȧ
			case 0x22:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2500)
				{
					SetStop();
					RunStep=0x1;
					RunMs=0;
					CurrentMax = 0;
				}
			}
				break;	
	#endif		
	}	
}
/****************************************************************
 * *
 * * * Function Name:void wallMode(void)
 *     Function: 
 * 
 * 
*****************************************************************/
void wallMode(void)
{
	static INT8U findIR;
	
	switch(RunStep){
		case 0:
			break;
		
		case 1:   //init
	//		InitMotorForwardLeft();
			InitMotorForward();
			RunStep=2;				
			RunMs = 0;
		  WallDp[0] = 0;
			WallDp[1] = 0;
			WallDp[2] = 0;
			WallDp[3] = 0;
			findRechargeFlag = 0;
			findIR = 0;
			if(wallRechargeModeFlag){
				SetFan(0);
				SetEdge(0);
			}
			break;

		case 2:  
			if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin)){			
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=10;
				CurrentMax++;
			}
			else if(IMP>0){		
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
				if(IMP == 1){
					RunStep=10;
				}
			}
			else	if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax)){			
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else	if((WallDp[1]>WallModeMin)){  //right IR detection
				NoImpSecond=0;
				InitMoterAdjustLeft();
				RunStep=0x8;
				RunMs = 0;
			}
			else if(findRechargeFlag){
				findRechargeFlag = 0;
				RunStep = 0x04;
				RunMs = 40;
				SetStop();
				findIR = 1;
			}					
			else {		//if(RunMs>800)	//����ǰ���ߣ�һֱ��Ȧ��ⲻ��������ֱ��һ�ξ��룬���¼��
//				RunStep = 0x09;
//				RunMs = 0;
//				InitMotorForward();
//				CurrentMax = 0;			
			}
			break;
		
		case 3: 		//���� retreat
			if(RunMs>30){
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}			
			break;

			case 4:  		//ֹͣ stop
				if(RunMs>40){	
					SetStop();
					RunMs=0;
					RunStep=5;
				}
				break;

			case 5:  //ת�� turn
				if(RunMs>20){			
					InitMotorLeft();
					RunStep=6;
					if(findIR)
						RunMs = 0;
					else
						RunMs = 55;
				}
				break;

			case 6:  //ֱ��	
				if(RunMs>135){
					InitMotorForward();
					RunMs=0;
					RunStep=7;
					if(findIR){
						RunStep = 9;
						RunMs = 100;
					}
//					else if(wallRechargeModeFlag){
//						SetStop();
//						RunStep = 1;
//						RunMs = 100;
//					}
				}	
				break;			
					
			case 7:  //ֱ��һ��С���룬Ȼ��ת��			
				if(RunMs>100){  			
					RunStep=2;				
					RunMs=0;
					LCurrent=0;
					RCurrent=0;
					InitMotorForwardLeft();
				}
				else if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=3;
					InitMotorRetreat();
					RunMs=10;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
					if(IMP == 1){
						RunStep=10;
					}
				}	
				else if(WallDp[1]>WallModeMin){
					RunMs = 0;
					RunStep = 8;
				}				
				break;
						
			case 8:   //right IR check ����
				if(RunMs>10){
					RunMs = 0;
					
					if(findRechargeFlag){
						findRechargeFlag = 0;
						RunStep = 0x03;
						RunMs = 0;
						SetStop();
						findIR = 1;
					}					
					else if(WallDp[1]<WallModeMin){
						InitMotorForwardLeft();
						RunStep = 0x02;
						RunMs = 0;
					}
					else if(WallDp[1]<WallModeNormal){ //ȫ��ֱ��
						RunMs = 0;
						InitMoterAdjustForward();
					}					
					else if(WallDp[1]<WallModeMax){  
						InitMoterAdjustLeft();
						RunMs = 0;
					}
					else{
						InitMoterAdjustLeftMore();
						RunMs = 0;
					}
						
					if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
					{
						NoImpSecond=0;
						RunStep=3;
						InitMotorRetreat();
						RunMs=10;
					}
					else if(IMP>0)
					{
						NoImpSecond=0;
						RunStep=0x3;
						InitMotorRetreat();
						RunMs=0;
						CurrentMax++;			
						if(IMP == 1){
							RunStep=10;
						}
					}	
				}
				break;
				
			case 9:		//��ǰ��һ�γ����룬����Ѱ��ǽ
				if(RunMs>500){
					RunMs = 0;
					RunStep = 2;
					InitMotorForwardLeft();
					if(findIR){
						findIR = 0;
						RunMode = 0x05;
						RunStep = 0;
						ADCtl = 0;
						SetFan(0);
						SetEdge(0);
					}
				}
				break;

			
		case 10: 		//���� retreat
			if(RunMs>10){
				InitMotorRetreat();
				RunStep=11;
				if(wallRechargeModeFlag)
					RunMs = 0;
				else 
					RunMs = 130;			
			}			
			break;

			case 11:  		//ֹͣ stop
				if(RunMs>170){	
					SetStop();
					RunMs=0;
					RunStep=12;
				}
				break;

			case 12:  //תС�� turn
				if(RunMs>20){			
					InitMotorLeft();
					RunMs=0;
					RunStep=13;
					if(wallRechargeModeFlag)
						RunMs = 0;
					else 
						RunMs = 40;					
				}
				break;
				
			case 13:  //С������ת	
				if(RunMs>80){		
					if(wallRechargeModeFlag){
						RunStep=7;	
	//					InitMotorForwardRight();
						InitMotorForwardLeft();
						RunMs = 0;
						ForwardFlag = 19 ;
					}
					else {
						InitMotorRightLittle();
						RunStep=7;		
						RunMs = 80;			
					}						
				}	
				break;	
								
		default:
			break;	
	}
	return;
}




void rechargeBatMode(void)
{
	static INT8U distance = 0;
	static INT8U timeCnt = 0;
	static INT8U lostCnt = 0;
	static INT8U connect = 0;
	static INT8U rightLostFlag = 0;
	static INT8U leftLostFlag = 0;
	static INT16U timeCircle;
	static INT8U findCnt = 0;
	
	switch(RunStep)
	{
		case 0:   //init
		{
			InitMotorRightCircleRecharge();
			RunMs = 0;
			RunStep=1;
//			ADCtl = 0;
			ClearAllIR();
			timeCircle= 50;
			findCnt = 0;
		}
			break;
				
		case 1:
		{
			if(RunMs>30)
			{
				RunMs=0;
				connect++;
				rightLostFlag = 0;
				leftLostFlag = 0;
				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearPreLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.NearRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarMid>0)
				{
					RunStep=0x40;
					InitMotorForwardSlow();
				}
				else if(IRLocation.FarPreRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarPreLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else if(connect>timeCircle){
					connect = 0;
					RunMs = 0;
					RunStep = 6;
					InitMotorForward();
					findCnt++;
					if(findCnt>= 20){
						findCnt = 0;
						RunMode = 2;
						RunStep = 1;
						ADCtl = 1;
//						SetFan(250);
//						SetEdge(250);				
						wallRechargeModeFlag = 1;
						findRechargeFlag = 0;
					}
				}
				else
				{

				}
				ClearAllIR();
			}
		}
			break;
		
		case 0x02:
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=10;
				CurrentMax++;
			}
			else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
				CurrentMax++;			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else if(RunMs>500)
			{
				SetStop();
				RunStep = 0x0;
				RunMs = 0;
			}			
			break;
			
		
			case 3:   //����
			{
				if(RunMs>20)
				{
					InitMotorRetreat();
					RunMs=0;
					RunStep=4;
				}
			}
				break;
			
			case 4:  //ֹͣ
			{
				if(RunMs>60)
				{
					SetStop();
					RunMs=0;
					RunStep=5;
				}
			}
				break;

			case 5:  //ת��
			{
				if(RunMs>20)
				{
					InitMotorLeftCircle();
					RunMs=0;
					RunStep=7;
				}
			}
				break;

			case 6:  //ֱ��	
				if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
					CurrentMax++;			
				}
				else if(RunMs>300)
				{
//					InitMotorForward();
					RunMs=0;
					RunStep=1;
					timeCircle = 50;
					InitMotorRightCircleRecharge();
				}	
				break;						
		
		case 7:
				if(RunMs>250)
				{
					InitMotorForward();
					RunMs=0;
					RunStep=6;
				}				
			break;
				
		case 0x40:   //far away
		{
			if(RunMs>20)
			{
				RunMs=0;
				distance = 0;
				lostCnt = 0;
				rightLostFlag = 0;
				leftLostFlag = 0;
//				if(SendCount>=12)
//				{
//					Usart1Send[0]=12;
//					Usart1Send[1]=IRLocation.NearMid;
//					Usart1Send[2]=IRLocation.NearPreRight;
//					Usart1Send[3]=IRLocation.NearPreLeft;
//					Usart1Send[4]=IRLocation.NearRight;
//					Usart1Send[5]=IRLocation.NearLeft;
//					Usart1Send[6]=IRLocation.FarMid;
//					Usart1Send[7]=IRLocation.FarPreRight;
//					Usart1Send[8]=IRLocation.FarPreLeft;
//					Usart1Send[9]=IRLocation.FarRight;
//					Usart1Send[10]=IRLocation.FarLeft;
//					Usart1Send[11]=RunNoIRsenorLastStep;
//					Usart1Send[12]=RunStep;
//					SendCount=1;
//					SBUF=Usart1Send[SendCount];
//				}

				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					//RunStep=0x53;
					RunStep=0x50;
				}
				else if(IRLocation.NearPreLeft>0)
				{
					//RunStep=0x56;
					RunStep=0x50;
				}
				else if(IRLocation.NearRight>0)
				{
					//RunStep=0x59;
					RunStep=0x50;
				}
				else if(IRLocation.NearLeft>0)
				{
					//RunStep=0x5c;
					RunStep=0x50;
				}
				else if(IRLocation.FarMid>0)
				{
					//RunStep=0x40;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;
				}
				else if(IRLocation.FarPreRight>0)
				{
					InitMotorForwardLeftSlow();
					//RunStep=0x43;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarPreLeft>0)
				{
					InitMotorForwardRightSlow();
					//RunStep=0x46;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else if(IRLocation.FarRight>0)
				{
					//RunStep=0x49;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarLeft>0)
				{
					//RunStep=0x4c;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else
				{
					RunNoIRsenorTime++;
					if(RunNoIRsenorTime>5)
					{

						RunNoIRsenorTime=0;
						if(RunNoIRsenorLastStep==1)
						{

						}
						else	if(RunNoIRsenorLastStep==2)
						{
							InitMotorForwardRightSlow();
							RunNoIRsenorTime=0;
							RunStep=0x41;
						}
						else	if(RunNoIRsenorLastStep==3)
						{
							InitMotorForwardLeftSlow();
							RunNoIRsenorTime=0;
							RunStep=0x42;
						}

					}
				}
				ClearAllIR();
			}
		}
			break;
		case 0x41:  //right side
		{
			if(RunMs>30)
			{
				RunMs=0;
//				if(SendCount>=12)
//				{
//					Usart1Send[0]=12;
//					Usart1Send[1]=IRLocation.NearMid;
//					Usart1Send[2]=IRLocation.NearPreRight;
//					Usart1Send[3]=IRLocation.NearPreLeft;
//					Usart1Send[4]=IRLocation.NearRight;
//					Usart1Send[5]=IRLocation.NearLeft;
//					Usart1Send[6]=IRLocation.FarMid;
//					Usart1Send[7]=IRLocation.FarPreRight;
//					Usart1Send[8]=IRLocation.FarPreLeft;
//					Usart1Send[9]=IRLocation.FarRight;
//					Usart1Send[10]=IRLocation.FarLeft;
//					Usart1Send[11]=RunNoIRsenorLastStep;
//					Usart1Send[12]=RunStep;
//					SendCount=1;
//					SBUF=Usart1Send[SendCount];
//				}

				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					//RunStep=0x53;
					RunStep=0x50;
				}
				else if(IRLocation.NearPreLeft>0)
				{
					//RunStep=0x56;
					RunStep=0x50;
				}
				else if(IRLocation.NearRight>0)
				{
					//RunStep=0x59;
					RunStep=0x50;
				}
				else if(IRLocation.NearLeft>0)
				{
					//RunStep=0x5c;
					RunStep=0x50;
				}
				else if(IRLocation.FarMid>0)
				{
					RunStep=0x40;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;
				}
				else if(IRLocation.FarPreRight>0)
				{
					InitMotorForwardLeftSlow();
					RunStep=0x40;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarPreLeft>0)
				{
					InitMotorForwardRightSlow();
					RunStep=0x40;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else if(IRLocation.FarRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else
				{
					RunNoIRsenorTime++;
//					if(distance)
//						timeCnt = 9;
//					else 
//						timeCnt = 9;
					
//					if(leftLostFlag){
//						leftLostFlag = 0;
//						timeCnt = 18;
//					}
//					else 
						timeCnt = 9;
					if(RunNoIRsenorTime>timeCnt)
					{
							rightLostFlag = 1;
//						RunNoIRsenorTime=0;

//						//else	if(RunNoIRsenorLastStep==3)
//						{
							InitMotorForwardLeftSlow();
							RunNoIRsenorTime=0;
							RunStep=0x42;
//						}
						if(lostCnt++>=2){
							lostCnt = 0;
							RunNoIRsenorTime=0;
							RunStep = 1;
							timeCircle = 50;
							InitMotorRightCircleRecharge();
						}

					}
				}
				ClearAllIR();
			}
		}
			break;
		case 0x42:   //leftt side 
		{
			if(RunMs>30)
			{
				RunMs=0;
//				if(SendCount>=12)
//				{
//					Usart1Send[0]=12;
//					Usart1Send[1]=IRLocation.NearMid;
//					Usart1Send[2]=IRLocation.NearPreRight;
//					Usart1Send[3]=IRLocation.NearPreLeft;
//					Usart1Send[4]=IRLocation.NearRight;
//					Usart1Send[5]=IRLocation.NearLeft;
//					Usart1Send[6]=IRLocation.FarMid;
//					Usart1Send[7]=IRLocation.FarPreRight;
//					Usart1Send[8]=IRLocation.FarPreLeft;
//					Usart1Send[9]=IRLocation.FarRight;
//					Usart1Send[10]=IRLocation.FarLeft;
//					Usart1Send[11]=RunNoIRsenorLastStep;
//					Usart1Send[12]=RunStep;
//					SendCount=1;
//					SBUF=Usart1Send[SendCount];
//				}

				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					//RunStep=0x53;
					RunStep=0x50;
				}
				else if(IRLocation.NearPreLeft>0)
				{
					//RunStep=0x56;
					RunStep=0x50;
				}
				else if(IRLocation.NearRight>0)
				{
					//RunStep=0x59;
					RunStep=0x50;
				}
				else if(IRLocation.NearLeft>0)
				{
					//RunStep=0x5c;
					RunStep=0x50;
				}
				else if(IRLocation.FarMid>0)
				{
					RunStep=0x40;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;
				}
				else if(IRLocation.FarPreRight>0)
				{
					InitMotorForwardLeftSlow();
					RunStep=0x40;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarPreLeft>0)
				{
					InitMotorForwardRightSlow();
					RunStep=0x40;
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else if(IRLocation.FarRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				}
				else if(IRLocation.FarLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;
				}
				else
				{
					RunNoIRsenorTime++;
//					if(distance)
//						timeCnt = 9;
//					else 
//						timeCnt = 9;
					
//					if(rightLostFlag){
//						rightLostFlag = 0;
//						timeCnt = 18;
//					}
//					else 
						timeCnt = 9;
					if(RunNoIRsenorTime>timeCnt)
					{
							leftLostFlag = 1;
//						RunNoIRsenorTime=0;
//						if(RunNoIRsenorLastStep==2)
//						{
							InitMotorForwardRightSlow();
							RunNoIRsenorTime=0;
							RunStep=0x41;
//						}

						if(lostCnt++>=2){
							lostCnt = 0;
							SetStop();
							RunNoIRsenorTime=0;
							RunStep = 1;
							timeCircle = 50;
							InitMotorRightCircleRecharge();
						}

					}
				}
				ClearAllIR();
			}
		}
			break;
		case 0x50:   //near 
		{
			if(RunMs>20)
			{
				RunMs=0;
				distance = 1;
				lostCnt = 0;
				rightLostFlag = 0;
				leftLostFlag = 0;
//				if(SendCount>=12)
//				{
//					Usart1Send[0]=12;
//					Usart1Send[1]=IRLocation.NearMid;
//					Usart1Send[2]=IRLocation.NearPreRight;
//					Usart1Send[3]=IRLocation.NearPreLeft;
//					Usart1Send[4]=IRLocation.NearRight;
//					Usart1Send[5]=IRLocation.NearLeft;
//					Usart1Send[6]=IRLocation.FarMid;
//					Usart1Send[7]=IRLocation.FarPreRight;
//					Usart1Send[8]=IRLocation.FarPreLeft;
//					Usart1Send[9]=IRLocation.FarRight;
//					Usart1Send[10]=IRLocation.FarLeft;
//					Usart1Send[11]=IMP;
//					Usart1Send[12]=RunStep;
//					SendCount=1;
//					SBUF=Usart1Send[SendCount];
//				}
				if(IRLocation.NearMid>0)
				{
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.NearPreRight>0)
				{
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearPreLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.NearRight>0)
				{
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarMid>0)
				{
					//RunStep=0x50;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.FarPreRight>0)
				{
					//RunStep=0x53;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarPreLeft>0)
				{
					//RunStep=0x56;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarRight>0)
				{
					//RunStep=0x59;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarLeft>0)
				{
					//RunStep=0x5c;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else
				{
					RunNoIRsenorTime++;
					if(RunNoIRsenorTime>5)
					{

						RunNoIRsenorTime=0;
						if(RunNoIRsenorLastStep==1)
						{

						}
						else	if(RunNoIRsenorLastStep==2)
						{
							InitMotorForwardRightSlow();
							RunNoIRsenorTime=0;
							RunStep=0x41;
						}
						else	if(RunNoIRsenorLastStep==3)
						{
							InitMotorForwardLeftSlow();
							RunNoIRsenorTime=0;
							RunStep=0x42;
						}


					}
				}
				ClearAllIR();
			}
		}
			break;
		default:
			break;
	}	
	return;
}

/************************************************************************************
 * 	*
    *Function Name:void CheckMode(INT8U Key)
	*Function : motor run of mode three 3 modes
	*           mode 0ne :
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
#if 0
void CheckMode(INT8U Key)
{
if(Key==1)
 {
   Mode =0; 
   cleanWorks.pressPowerKey++;
   if(cleanWorks.pressPowerKey>4)cleanWorks.pressPowerKey=0;
   Step=cleanWorks.pressPowerKey;
   //SBUF =  Step;
 }
  else if(Key==2){ //works mode ----cleaning button        
		Mode =1;
		cleanWorks.worksNumber++;
		if(cleanWorks.worksNumber>5)cleanWorks.worksNumber=0;
		Step=cleanWorks.worksNumber  ;
		//SBUF =  Step;
 }
    ////power on of initial: Mode=2;Step=0;RunMode=1;RunStep=0;
	switch(Mode)
	{
	  case 0 :
		{
		
		switch(Step)
		{	        
			//power On and power key press status 
			case 1: //power on 
			{
				cleanWorks.iPowerFlag =1;
				SetStop();
				LedGreenOff();
				LedRedON();
				SetBuzzerTime(5);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(5);
				Delay_ms(10);
				BuzzerOff();
				Mode = 0x65;
				Step = 0x64;
			}
			break;

        
		case 2:  //input standby mode
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Mode =0x66;
			LedGreenON();
			LedRedOff();
			Step = 0x19 ;	
			break;
		
		case 3: //input recharge status                
				Mode =0x66;
				SetBuzzerTime(4);
			  Delay_ms(10);
				BuzzerOff();

				LedGreenOff();
				LedRedOff();
		
				RunMode =5;
				RunStep=0;
				RunMs = 0;
				break;
		
			case  4: //power off 
				Mode =0x66;
				SetStop();
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerOff();
				LedGreenOff();
				LedRedON();
				Step = 0x19 ;			
				break;
		
		case 0x19:
		//if(cleanWorks.CleanMode == standbyMode)  //  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
		{
			if(Step==0)
			{
				//20
				Step=1;
				ADCtl=1;
				RunSecond=0;
			}
			else if(Step<0x20)
			{
				//LedBlueON();
				Mode=1;
				Step=0;
				RunSecond=0;
				SetStop();
				SetFan(0);
				SetEdge(0);
				RunStep=0;
				//SetBuzzerTime(2);
			}
		}
		
		}//Mode =0 END
	}
	   break;
	/*************************Mode 0 END**************************/
	/**********Mode 1 start******************/
	//power on key =1
	//  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
	case 1:
	{
		switch(Step)
		{
			//������ʾ��1����2��
		case 0:
		{
			
		}
		break;
		case 1://prepare clean mode 
		{
				Mode =0x66;
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerON();
				LedRedON();
		}
		break;
		case 2://randomMode
		{
        RunMode =1; //
				RunStep =1;
			  Mode =0x66;
				SetBuzzerTime(4);
			  Delay_ms(10);
				BuzzerOff();
				LedRedOff();
				ADCtl=1;   //vic 2020.12.24
		 }
		break;
		//��������ʱ���ƹ���Ƶ��2Hz

		case 3://zMode ---wall edge mode 
		    RunMode =2;
				RunStep=1;
		    Mode =0x66;
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
				ADCtl=1;   //vic 2020.12.24
			
				LedGreenON();
				LedRedON();
		break;

		case 4: //bowMode
		    RunMode =3;
				RunStep =1;
        Mode =0x66;   
		    SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
		
				
                LedGreenOff();
				LedRedOff();
				ADCtl=1;   //vic 2020.12.24
				
	
		break;
		// ����еƹ�Ƶ�ￄ1�7?0.5Hz
		case 5: //fixPoint Mode
			    RunMode =4;
				RunStep =1;
			    Mode =0x66;
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
			    Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
				LedGreenON();
				LedRedON();
				ADCtl=1;   //vic 2020.12.24		
		break;

		case 6:
		{
			if(RunSecond>9)
			{
				LedRedOff();
				Step=5;
				RunSecond=0;
			}
			else if(Voltage>840)
			{
				Step=7;
			}
			else if((0==ReadPowerAutoIn())&&(0==ReadPowerDCIn()))
			{
				Step=0;
				Mode=1;
				//SetBuzzerTime(1);
			}
		}
		break;
		//���粻��
		case 7:
		{
			if((0==ReadPowerAutoIn())&&(0==ReadPowerDCIn()))
			{
				Step=0;
				Mode=0;
			}

			else if(Voltage<650)
			{
				Step=5;

				//SetBuzzerTime(3);
			}
			break;
		}
		case 8:
		{
			if(RunSecond>0)
			{
				LedRedON();

				Step=9;
				RunSecond=0;
			}
		}
		break;

		case 9:
		{
			if(RunSecond>0)
			{

				LedRedOff();
				Step=8;
				RunSecond=0;
			}
		}
		break;
		case 20:
		{
			if((WallDp[0]>WallMin)&&(WallDp[1]>WallMin)&&(WallDp[2]>WallMin))
				LedRedON();
			else
				LedRedOff();
		}
		break;

		}
	}
	break;
	/**********************Mode 1 END***********************************/
	
	
	/*************Mode 2 start Battery recharge ***********************/
	// Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
	//power on of initial:	Mode=2;Step=0;RunMode=1;RunStep=0;
	//Mode =2 start 
	case 2:
	{
		switch(Step)
		{
			case 0:
			{
				RunMode=2;
				RunStep=0;
				Step=1;
			}
			break;
			case 1:
			{
				if(P2_1 ==1|| P1_0 ==1)
				{
					RunStep=0x60;
					SetStop();
					LedGreenON();
					Step=2;
				}
			}
			break;
            //battery recharge status
           
			case 2:
				if(P2_1 ==1|| P1_0 ==1){
	        SetStop() ;// AllStop();
					LedGreenON();
					Delay_ms(500);
					LedGreenOff();
					Delay_ms(500);
					Step =2;
					Mode =2;
				}
				break;
		}

	}
	break;
	/*******************Mode 2 END **********************************/
	/**********************************************************/
	/*********************************************************/

    }
}
#endif 

void sysMode(INT8U val)
{
	static INT8U lastMode = 0;
	static INT8U powerUp = 0;
	
	if(!val)
		return;
	
	switch(val){
		case 0x01:     //key1 short put on
			if(!lastMode){
				return;
			}
			if(lastMode == 5){
				SetFan(0);
			  SetEdge(0);	
				lastMode = 6;
			}
			else{
				lastMode = 5;
        SetFan(0);
				SetEdge(0);					
				SysFlag = IDEL;
			}
			break;
		
		case 0x02:  //key1 put on over 500ms 
			if(!powerUp){			
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerOff();
				Delay_ms(150);
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerOff();
				Delay_ms(150);
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerOff();	
				
				SetStop();
				RunStep = 0;
				RunMode = 1;
				lastMode = 0;	
				SetFan(0);
			  SetEdge(0);	
				SysFlag = OVER;
			}
			else{
				powerUp = 0;
			}
			break;
		
		case 0x03:  //key1 put on  500ms
			if(!lastMode){
				SetBuzzerTime(4);
				Delay_ms(10);
				BuzzerOff();
				lastMode = 0xff;
				powerUp = 1;
				LedRedOff();
				LedGreenON();	
        SetFan(0);
			  SetEdge(0);					
				SysFlag = CLEAN;
			}
			break;
		
		case 0x10:   //key2 short put on
			if(lastMode == 0)
				return;
			
			if(lastMode == 0xff){
				lastMode = 5;
			}
			else{
				if(lastMode++>=4)
					lastMode = 1;					
			}
			SysFlag = CLEAN;
			break;
		
		case 0x20:  //key2 put on over 500ms   
			if(lastMode == 0)
				return;			
			break;
		
		case 0x30:   //key2 put on  500ms
			if(lastMode == 0)
				return;			
			break;
		
		case 0x44:  //key1 and  key2 put on 200ms 
			break;
		
		default:
			return;
	}
	
	if(lastMode == Mode)
		return;
	Mode = lastMode;
	
	switch(Mode){
		case 0:
//			SysFlag = IDEL;
			break;
		
		case 1:   //s���
			RunMode =1; //
			RunStep =1;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			ADCtl=1;   //vic 2020.12.24			
			SetFan(250);
			SetEdge(250);
			break;		
		
		case 2:
			RunMode =2; //�ر�
			RunStep =1;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			ADCtl=1;   //vic 2020.12.24		
			SetFan(250);
			SetEdge(250);		
			wallRechargeModeFlag = 0;
			break;
		
		case 3:
			RunMode =3; //��
			RunStep =1;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();		
			ADCtl=1;   //vic 2020.12.24			
				SetFan(250);
				SetEdge(250);		
			break;
		
		case 4:
			RunMode =4; //Բ
			RunStep =1;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
			Delay_ms(150);
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();		
			ADCtl=1;   //vic 2020.12.24		
				SetFan(250);
				SetEdge(250);		
			break;
			
		case 5://����ģʽ
//			RunMode =4; 
//			RunStep =1;
			SetStop();
			RunMode = 1;
			RunStep = 0;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();
      SetFan(0);  //WT.EDIT 
			SetEdge(0);	 //WT.EDIT 	
			SysFlag = IDEL;
			break;
		
		
		case 6: //�س�ģʽ
			RunMode =5;
			RunStep =0;
			SetBuzzerTime(4);
			Delay_ms(10);
			BuzzerOff();	
      SetFan(0);
			SetEdge(0);		
		  ADCtl = 0;
			SysFlag = FIND;	
      RunMs = 0;//WT.EDIT 		
			break;
		
		default:
			break;
	}
	
	return;
}
	


void LedTip(INT8U status)
{
	static INT8U count = 0;	
	static INT8U on_off;
			
	switch(status){
		case IDEL:
			LedRedOff();
			if(count++>=3){
				count = 0;
				if(on_off){
					on_off = 0;
					LED_G = 0;
				}
				else{
					on_off = 1;
					LED_G = 1;				
				}
			}
			break;
		
		case CLEAN:
			LedRedOff();
			LedGreenON();			
			break;
		
		case FIND:
			LedRedON();
			LedGreenOff();			
			break;
		
		case BAT:
			count++;
			if(count>3){
				count = 0;
				if(on_off){
					on_off = 0;
					LED_R = 0;
				}
				else{
					on_off = 1;
					LED_R = 1;				
				}
			}		
			LedGreenON();				
			break;
		
		case BAT_FINISH:
			LedRedON();
			LedGreenON();					
			break;
		
		case WALL:
			if(count++ > 3){
				count =0;
				if(on_off){
					on_off = 0;
					LED_R = 0;
					LED_G = 1;
				}
				else{
					on_off = 1;
					LED_R = 1;
					LED_G = 0;			
				}				
			}
			break;
		
		case OVER:
			LedRedOff();
			LedGreenOff();				
			break;
		
		
		default:
			break;
	}
	
	
	return;
}



