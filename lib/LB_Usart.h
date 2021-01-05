/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_Usart_h
#define  LB_Usart_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//ȫ�ֱ�������
#ifdef  KAKA_Usart_GB
#define KAKA_Usart_EXT
#else
#define  KAKA_Usart_EXT extern
#endif

#define USART_FLAG    0
KAKA_Usart_EXT INT8U SendCount;
KAKA_Usart_EXT INT8U Usart1Send[20];
KAKA_Usart_EXT  void Init_Usart1();

#endif