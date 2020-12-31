/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_Motor_h
#define  LB_Motor_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_Motor_GB
#define KAKA_Motor_EXT
#else
#define  KAKA_Motor_EXT extern
#endif
KAKA_Motor_EXT void InitMotorIO(void);
KAKA_Motor_EXT void InitMotorForward(void);
KAKA_Motor_EXT void InitFanEdgeIO(void);


KAKA_Motor_EXT  void InitMotorRetreat(void);
KAKA_Motor_EXT  void InitMotorLeft(void);
KAKA_Motor_EXT  void InitMotorRight(void);
KAKA_Motor_EXT  void InitMotorRightSlow(void);
KAKA_Motor_EXT  void InitMotorLeftSlow(void);
KAKA_Motor_EXT  void InitMotorLeftMax(void);
KAKA_Motor_EXT  void InitMotorRightMax(void);

KAKA_Motor_EXT  void InitMotorForwardRight(void);

KAKA_Motor_EXT  void InitMotorForwardRightSlow(void);
KAKA_Motor_EXT  void InitMotorForwardLeftSlow(void);
KAKA_Motor_EXT  void InitMotorRetreatMax(void);
KAKA_Motor_EXT  void InitMotorForwardSlow(void);
KAKA_Motor_EXT  void SetMotorForwardPWMUP();
KAKA_Motor_EXT  void InitMotorRetreatLeft(void);
KAKA_Motor_EXT  void InitMotorRetreatRight(void);
KAKA_Motor_EXT  void SetStop();
KAKA_Motor_EXT  void InitFanEdgeIO(void);
KAKA_Motor_EXT  void SetFan(INT8U status) ;
KAKA_Motor_EXT  void SetEdge(INT8U status);


//vic 2020.12.23 add
KAKA_Motor_EXT  void InitMotorForwardLeft(void);
KAKA_Motor_EXT void InitMotorRightCircle(void);
KAKA_Motor_EXT void InitMotorLeftCircle(void);

KAKA_Motor_EXT void InitMotorForwardRightUp1(void);
KAKA_Motor_EXT void InitMotorForwardRightUp2(void);
KAKA_Motor_EXT void InitMotorForwardRightUp3(void);

KAKA_Motor_EXT void InitMotorForwardLeftUp1(void);
KAKA_Motor_EXT void InitMotorForwardLeftUp2(void);
KAKA_Motor_EXT void InitMotorForwardLeftUp3(void);

KAKA_Motor_EXT void InitMoterAdjustLeft(void);
KAKA_Motor_EXT void InitMoterAdjustLeftMore(void);
KAKA_Motor_EXT void InitMoterAdjustForward(void);
KAKA_Motor_EXT void InitMotorRightLittle(void);


KAKA_Motor_EXT void InitMotorRightCircleRecharge(void);

KAKA_Motor_EXT INT8U ForwardFlag;
#endif