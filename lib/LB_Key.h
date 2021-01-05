#ifndef __LB_KEY_H
#define __LB_KEY_H

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif

//globle vaiable
#ifdef  KAKA_Key_GB
#define KAKA_Key_EXT
#else
#define  KAKA_Key_EXT extern
#endif

typedef INT8U uint8_t ;

#define Power_Key            P3_4    //---Other board
#define Cleaning_Key         P3_5    //
#define POWER_PRES             1
#define CLEANING_PRES          2 
#define GROUP_PRES            3   

enum  woksmode{
   runWoksStatus =1 ,
   randomMode  ,
   zMode ,
   bowMode,
   fixpointMode ,
   standbyMode,
   recharge
};
struct _CleanMode{
    INT8U iPowerFlag;
    INT8U worksNumber; 
    INT8U CleanMode ;
    INT8U rechargeMode ;
    INT8U pressPowerKey;
    INT8U Clean_randomMode;
    INT8U Clean_bowMode;
    INT8U Clean_wallMode;
    INT8U Clean_fixpointMode;


};


KAKA_Key_EXT xdata struct _CleanMode cleanWorks;


KAKA_Key_EXT INT8U HDKey_Scan(INT8U mode);

KAKA_Key_EXT INT8U AutoDC_ReChargeStatus(void);

#endif 