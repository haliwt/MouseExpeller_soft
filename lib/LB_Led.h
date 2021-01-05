/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_Led_h
#define  LB_Led_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//ȫ�ֱ�������
#ifdef  KAKA_Led_GB
#define KAKA_Led_EXT
#else
#define  KAKA_Led_EXT extern
#endif

#define Auto_DCCharge    		P2_1 
#define DC_Recharge             P1_0
#define CloseSwitch_L  			P1_5	
#define CloseSwitch_R  			P3_2
#define BatteryRechargStatus     P1_7
#define LED_R             P2_7
#define LED_G             P2_6
#define LED_B             P3_5

  

KAKA_Led_EXT  INT8U BuzzerTime;
KAKA_Led_EXT  INT8U IMP;
KAKA_Led_EXT  void InitLed(void);

KAKA_Led_EXT  void LedRedOff();
KAKA_Led_EXT  void LedRedON();
KAKA_Led_EXT  void LedGreenON() ;
KAKA_Led_EXT  void LedGreenOff();
KAKA_Led_EXT void InitT1(void);
KAKA_Led_EXT void InitKey(void);
KAKA_Led_EXT INT8U ReadKey(void);
KAKA_Led_EXT void InitIMP(void);
KAKA_Led_EXT void ReadIMP(void);
KAKA_Led_EXT void InitPowerIn(void);
KAKA_Led_EXT INT8U ReadPowerAutoIn(void);
KAKA_Led_EXT INT8U ReadPowerDCIn(void);
KAKA_Led_EXT void InitBuzzer(void);
KAKA_Led_EXT void BuzzerON()	;
KAKA_Led_EXT void BuzzerOff() ;
KAKA_Led_EXT void SetBuzzerTime(INT8U time);
KAKA_Led_EXT void CheckBuzzer();


#endif