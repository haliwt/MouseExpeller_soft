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
   runWoksStatus =0 ,
   worksModeOne ,
   worksModeTwo,
   worksModeThree,
   worksTransform,
   recharge
};
struct _worksMode{
    INT8U iPowerFlag;
    INT8U worksNumber; 
    INT8U rechargeMode ;
    INT8U works_randomMode;
    INT8U works_wallMode;
    INT8U worksMode_1;
    INT8U worksMode_2;
    INT8U worksMode_3;


};


KAKA_Key_EXT xdata struct _worksMode worksMode;


KAKA_Key_EXT INT8U HDKey_Scan(INT8U mode);

KAKA_Key_EXT INT8U AutoDC_ReChargeStatus(void);
KAKA_Key_EXT void KEY_Handing(INT8U key);
KAKA_Key_EXT void Sharp_LED(INT8U);
 KAKA_Key_EXT INT8U KEY_Scan(void);

#endif 