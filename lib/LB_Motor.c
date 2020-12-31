/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Motor_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"

#endif
INT8U ForwardFlag;

void InitMotorIO(void)
{

    P1M1 = 0xC2;                        //P11设置为推挽输出
    P1M2 = 0xC2;                        //P12设置为推挽输出
    P1M3 = 0xC2;                        //P13设置为推挽输出
    P1M4 = 0xC2;                        //P14设置为推挽输出

  P1_1=0;
  P1_2=0;
  
  P1_3=0;
  P1_4=0;

}

void InitFanEdgeIO(void)
{
    P3M0 = 0xC2;                        //P34设置为推挽输出
    P3M1 = 0xC2;                        //P35设置为推挽输出
    P3_0=1;
    P3_1=1;

	PWM1_MAP = 0x30;					//PWM1通道映射P34口
	PWM11_MAP = 0x31;					//PWM11通道映射P35口
    PWM1C = 0x01;						//PWM1高有效，PWM11高有效，时钟8分频 
    PWMM |= 0x20;						//PWM1工作于						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM1PH = 0x01;						//周期高4位设置为0x03
	PWM1PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM1DH = 0x00;						//PWM1高4位占空比0x01
	PWM1DL = 0x00;						//PWM1低8位占空比0x55
	PWM1DTH = 0x00;						//PWM11高4位占空比0x01
	PWM1DTL = 0x00;						//PWM11低8位占空比0x55
	PWMEN |= 0x22;						//使能PWM1以及PWM11
	//SetFan(0);
	//SetEdge(0);
}


 void InitMotorForward(void)
{
    P1_1=0;  //right 
    P1_2=0;
	
    P1_3=0; //left
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P13口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xA0;	//WT.EDIT					//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xA0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=1;
}
 void InitMotorRetreat(void)
{
    P1_1=0;
    P1_2=0;
	
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=1;
}
 void InitMotorRetreatMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xf5;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xf5;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=1;
}
/***************************************************************
	*
	*Function Name:void InitMotorForwardRight(void)
	*Function :Line run 
	*
	*
	*
***************************************************************/
 void InitMotorForwardRight(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P13口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x90;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x90;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=2;
}


 void InitMotorForwardLeft(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
	PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
	PWMM |= 0x10;						//PWM0工作于互补模式						

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x90;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x90;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=3;
}


 void InitMotorForwardRightSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x90;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x90;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=5;
}
 /***************************************************************
	 *
	 *Function Name:void InitMotorForwardRightSlow(void)
	 *Function :Line run slowly
	 *
	 *
	 *
 ***************************************************************/

 void InitMotorForwardLeftSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x90;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x90;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=6;
}
 /***************************************************************
	*
	*Function Name:void InitMotorForwardRightSlow(void)
	*Function :Line run slowly
	*
	*
	*
***************************************************************/
 void InitMotorForwardSlow(void)
{
    P1_1=0;  //right
    P1_2=0;   //left
    P1_3=0;   //right
    P1_4=0;  //left
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xC0;	//WT.EDIT 					//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xC0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=0;
}
 /***************************************************************
	*
	*Function Name:void InitMotorForwardRightSlow(void)
	*Function :Line run slowly
	*
	*
	*
***************************************************************/
 void SetMotorForwardPWMUP()
{
	if(ForwardFlag==1)
	{
	  if(PWM0DL<0xd0)					 
	   PWM0DL += 3;				 
	   //PWM0DTH = 0x00;
	  if(PWM0DTL<0xd0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==2)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xe5)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==3)
	{
	  if(PWM0DL<0xf5)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==4)
	{
	  if(PWM0DL<0xf5)					 
	   PWM0DL += 2;				 
	  if(PWM0DTL<0xf5)						 
	   PWM0DTL += 2;
	}
	else if(ForwardFlag==5)
	{
	  if(PWM0DL<0xb0)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0x90)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==6)
	{
	  if(PWM0DL<0x90)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xb0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==7)
	{
	  if(PWM0DL>0xC0)					 
	   PWM0DL -= 1;				 
	  if(PWM0DTL>0x90)						 
	   PWM0DTL -= 2;
	}
	else if(ForwardFlag==8)
	{
	  if(PWM0DL<0xd0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag==9)
	{
	  if(PWM0DL<0xee)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xb0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag==10)
	{
	  if(PWM0DL>0x90)					 
	   PWM0DL -= 2;				 
	  if(PWM0DTL>0xC0)						 
	   PWM0DTL -= 1;
	}
	else if(ForwardFlag==11)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xD0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag==12)
	{
	  if(PWM0DL<0xb0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xee)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag==13)
	{
	  if(PWM0DL<0xc0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xc0)						 
	   PWM0DTL += 1;
	}	
		else if(ForwardFlag == 14){   //左轮减速，微调角度
		if(PWM0DL<0x90 && PWM0DTL==0xb0){
			PWM0DL -= 1;	
			if(PWM0DL<=0x90)
				PWM0DTL= 0xb1;
		}
		else{		
			if(PWM0DTL<0xc0)
				PWM0DTL += 2;
			PWM0DL += 2;
			if(PWM0DL>=0xc0){
				PWM0DL = 0xc0;
				PWM0DTL = 0xc0;
				ForwardFlag = 15;
			}
		}
	}
	else if(ForwardFlag == 15){   //由右转调节成直走
	  if(PWM0DL>0xc0)					 
	   PWM0DL -= 2;			
		else
			PWM0DL += 2;
		
	  if(PWM0DTL>0xc0)						 
	   PWM0DTL -= 2;
		else
		PWM0DTL += 2;
		
	}
	else if(ForwardFlag == 16){   //左轮减速，微调角度
	  if(PWM0DL>0xb0)					 
	   PWM0DL -= 1;				 
	  if(PWM0DTL<0xd0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag == 17){   //小曲线右转
	  if(PWM0DL>0xC0)
			PWM0DL -= 1;	
	  else
			PWM0DL += 1;	
		
	  if(PWM0DTL<0xB8)					
	   PWM0DTL += 1;
		else
		PWM0DTL -= 1;
	}
	else if(ForwardFlag==18)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag == 19){   //小曲线右转
	  if(PWM0DL>0xf0)
			PWM0DL -= 2;	
	  else
			PWM0DL += 2;	
		
	  if(PWM0DTL<0xb0)					
	   PWM0DTL += 2;
		else
		PWM0DTL -= 2;
	}	
	return;
}
void InitMotorRight(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;	//0x10					//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xA0;	 //WT.EDIT 					//PWM0低8位占空比0x55  //WT.EDTI 
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=4;
}
/***************************************************************
	*
	*Function Name:void InitMotorLeft(void)
	*Function :turn round CCW 
	*
	*
	*
***************************************************************/
 void InitMotorLeft(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P13口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式
     
    	

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xA0;		//WT.EDIT 				//PWM01低8位占空比0x55 
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=4;
}
/***************************************************************
	*
	*Function Name:void InitMotorRight(void)
	*Function :Line run BACK 
	*
	*
	*
***************************************************************/
 void InitMotorRightMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xa0;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xa0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=4;
}
 void InitMotorLeftMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P13口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xa0;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xa0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=4;
}
void InitMotorRightSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xa4;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xa4;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=0;
}

 void InitMotorLeftSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P13口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xa4;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xa4;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=0;
}

void SetStop()
{
  ForwardFlag=0;
   PWMEN &= 0xee;
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
}


void SetFan(INT8U status)
{
   PWM1DTL = status;
}
void SetEdge(INT8U status)
{
   PWM1DL = status;
}





 void InitMotorForwardRightUp1(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
		PWM0_MAP = 0x13;					//PWM0通道映射P14口
		PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xb0;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xc0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=7;
}

 void InitMotorForwardRightUp2(void)
{
	ForwardFlag=8;
}

 void InitMotorForwardRightUp3(void)
{
	ForwardFlag=9;
}


 void InitMotorForwardLeftUp1(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
	PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
	PWMM |= 0x10;						//PWM0工作于互补模式						

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF


	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0xb0;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0xc0;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=10;
}

 void InitMotorForwardLeftUp2(void)
{
	ForwardFlag=11;
}
	 
 void InitMotorForwardLeftUp3(void)
{
	ForwardFlag=12;
}


void InitMotorRightCircle(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
	PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
	PWMM |= 0x10;						//PWM0工作于互补模式						


	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=13;
}

void InitMotorRightCircleRecharge(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0通道映射P14口
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
	PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
	PWMM |= 0x10;						//PWM0工作于互补模式						


	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=18;
}


 void InitMotorLeftCircle(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x14;					//PWM0通道映射P13口
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
  PWM0C = 0x01;						//PWM0高有效，PWM01高有效，时钟8分频 
  PWMM |= 0x10;						//PWM0工作于互补模式						

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x11;						//使能PWM0以及PWM01
	ForwardFlag=13;
}

void InitMoterAdjustLeft(void)
{
	ForwardFlag = 14;
}

void InitMoterAdjustLeftMore(void)
{
	ForwardFlag = 16;
}

void InitMoterAdjustForward(void)
{
	ForwardFlag = 15;
}

void InitMotorRightLittle(void)
{
		ForwardFlag = 17;
}
