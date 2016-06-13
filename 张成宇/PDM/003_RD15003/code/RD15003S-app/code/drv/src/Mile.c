#include "Mile.h"

//轮子直径是43mm，一周的长度是0.13502m，每周会产生6个感应状态
#define MILE_UNIT               22.5 //接近开关每变化一次 里程的变化值22.5mm

//P3--A
//p4--B
//p2--C
CMileSwitchInfo  cMileASwitchInfo, cMileBSwitchInfo, cMileCSwitchInfo;
CMileRecordInfo  cMileARecordInfo, cMileBRecordInfo, cMileCRecordInfo;

 
/************************************************************************
*Precedure  :       MileGpioInit
*Funtion  :	     里程计IO口创建
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************

************************************************************************/

STATIC VOID MileGpioInit(VOID)
{	
    GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/************************************************************************
*Precedure  :       CalculateMile
*Funtion  :	     计算行驶里程 
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/

STATIC VOID MileACalculateThread(VOID)
{
	if(cMileASwitchInfo.MileUnitNumber < 0)
	{
        cMileARecordInfo.MileSign = '-';
	}
    else 
	{
        cMileARecordInfo.MileSign = '+';
	}
	cMileARecordInfo.mmileage = cMileASwitchInfo.MileUnitNumber*MILE_UNIT;
	
	cMileARecordInfo.mileage = (cMileARecordInfo.mmileage/(float)1000.0);	
}

STATIC VOID MileBCalculateThread(VOID)
{
	if(cMileBSwitchInfo.MileUnitNumber < 0)
	{
        cMileBRecordInfo.MileSign = '-';
	}
    else 
	{
        cMileBRecordInfo.MileSign = '+';
	}
	cMileBRecordInfo.mmileage = cMileBSwitchInfo.MileUnitNumber*MILE_UNIT;
	
	cMileBRecordInfo.mileage = (cMileBRecordInfo.mmileage/(float)1000.0);	
}

STATIC VOID MileCCalculateThread(VOID)
{
	if(cMileCSwitchInfo.MileUnitNumber < 0)
	{
        cMileCRecordInfo.MileSign = '-';
	}
    else 
	{
        cMileCRecordInfo.MileSign = '+';
	}
	cMileCRecordInfo.mmileage = cMileCSwitchInfo.MileUnitNumber*MILE_UNIT;
	
	cMileCRecordInfo.mileage = (cMileCRecordInfo.mmileage/(float)1000.0);	
}


VOID CalculateMile(VOID)
{ 
	MileACalculateThread();
	
	MileBCalculateThread();
	
	MileCCalculateThread();
}

/************************************************************************
*Precedure  :      MileDataInit
*Funtion  :	    初始里程初始化
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/																	
VOID MileDataInit(VOID)
{
    cMileASwitchInfo.LastSwitchState = 0x00;
    cMileASwitchInfo.CurrentSwitchState = 0x00;
	cMileASwitchInfo.MileUnitNumber = 0;
    cMileARecordInfo.mmileage = 0.0;
    cMileARecordInfo.mileage = 0.0;
    cMileARecordInfo.MileSign = '+';
	
	cMileBSwitchInfo.LastSwitchState = 0x00;
    cMileBSwitchInfo.CurrentSwitchState = 0x00;
	cMileBSwitchInfo.MileUnitNumber = 0;
    cMileBRecordInfo.mmileage = 0.0;
    cMileBRecordInfo.mileage = 0.0;
    cMileBRecordInfo.MileSign = '+';
	
	cMileCSwitchInfo.LastSwitchState = 0x00;
    cMileCSwitchInfo.CurrentSwitchState = 0x00;
	cMileCSwitchInfo.MileUnitNumber = 0;
    cMileCRecordInfo.mmileage = 0.0;
    cMileCRecordInfo.mileage = 0.0;
    cMileCRecordInfo.MileSign = '+';
	
}


STATIC U16 g_u16MileACurrentState, g_u16MileALastState;
STATIC U16 g_u16MileBCurrentState, g_u16MileBLastState;
STATIC U16 g_u16MileCCurrentState, g_u16MileCLastState;


STATIC VOID MileAStateThread(VOID)
{
	if(g_u16MileACurrentState != g_u16MileALastState)
	{
		if(g_u16MileACurrentState == 0x00c0)
		{
			cMileASwitchInfo.bMileState = TRUE;
		}
		else
		{
			cMileASwitchInfo.CurrentSwitchState = g_u16MileACurrentState;
			
			if(cMileASwitchInfo.bMileState == TRUE)
			{
				switch(g_u16MileACurrentState)
				{
					case 0x0000:
						if(cMileASwitchInfo.LastSwitchState == 0X0080)
						{
							cMileASwitchInfo.MileUnitNumber--;
							cMileASwitchInfo.Offset = 1;
						}
						else if(cMileASwitchInfo.LastSwitchState == 0X0040)
						{
							cMileASwitchInfo.MileUnitNumber++;
							cMileASwitchInfo.Offset = -1;
						}
						else
						{
							cMileASwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0080:
						if(cMileASwitchInfo.LastSwitchState == 0X0040)
						{
							cMileASwitchInfo.MileUnitNumber--;
							cMileASwitchInfo.Offset = 1;
						}

						else if(cMileASwitchInfo.LastSwitchState == 0X0000)
						{
							cMileASwitchInfo.MileUnitNumber++;
							cMileASwitchInfo.Offset = -1;
						}
						else
						{
							cMileASwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0040:
						if(cMileASwitchInfo.LastSwitchState == 0X0000)
						{
							cMileASwitchInfo.MileUnitNumber--;
							cMileASwitchInfo.Offset = 1;
						}
						else if(cMileASwitchInfo.LastSwitchState == 0X0080)
						{
							cMileASwitchInfo.MileUnitNumber++;
							cMileASwitchInfo.Offset = -1;
						}
						else
						{
							cMileASwitchInfo.Offset = 0;
						}
						break;	
					default:
						break;
				}
				
				cMileASwitchInfo.LastSwitchStateEx = cMileASwitchInfo.LastSwitchState;
				
				cMileASwitchInfo.LastSwitchState = cMileASwitchInfo.CurrentSwitchState;
			}
			else
			{
				
								
				switch(g_u16MileACurrentState)
				{
					case 0x0000:
						cMileASwitchInfo.LastSwitchState = cMileASwitchInfo.LastSwitchStateEx;

						cMileASwitchInfo.MileUnitNumber = cMileASwitchInfo.MileUnitNumber + cMileASwitchInfo.Offset;
						if(cMileASwitchInfo.LastSwitchState == 0X0080)
						{
							cMileASwitchInfo.MileUnitNumber--;
							cMileASwitchInfo.Offset = 1;
						}
						else if(cMileASwitchInfo.LastSwitchState == 0X0040)
						{
							cMileASwitchInfo.MileUnitNumber++;
							cMileASwitchInfo.Offset = -1;
						}
						
						cMileASwitchInfo.LastSwitchStateEx = cMileASwitchInfo.LastSwitchState;
				
						cMileASwitchInfo.LastSwitchState = cMileASwitchInfo.CurrentSwitchState;
						break;
						
					default:
						break;
				}
				
				
				
			}
			
			cMileASwitchInfo.bMileState = FALSE;
		}
	}
	
	
	g_u16MileALastState = g_u16MileACurrentState;
}

STATIC VOID MileBStateThread(VOID)
{
	if(g_u16MileBCurrentState != g_u16MileBLastState)
	{
		if(g_u16MileBCurrentState == 0x000c)
		{
			cMileBSwitchInfo.bMileState = TRUE;
		}
		else
		{
			cMileBSwitchInfo.CurrentSwitchState = g_u16MileBCurrentState;
			
			if(cMileBSwitchInfo.bMileState == TRUE)
			{
				switch(g_u16MileBCurrentState)
				{
					case 0x0000:
						if(cMileBSwitchInfo.LastSwitchState == 0X0008)
						{
							cMileBSwitchInfo.MileUnitNumber--;
							cMileBSwitchInfo.Offset = 1;
						}
						else if(cMileBSwitchInfo.LastSwitchState == 0X0004)
						{
							cMileBSwitchInfo.MileUnitNumber++;
							cMileBSwitchInfo.Offset = -1;
						}
						else
						{
							cMileBSwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0008:
						if(cMileBSwitchInfo.LastSwitchState == 0X0004)
						{
							cMileBSwitchInfo.MileUnitNumber--;
							cMileBSwitchInfo.Offset = 1;
						}

						else if(cMileBSwitchInfo.LastSwitchState == 0X0000)
						{
							cMileBSwitchInfo.MileUnitNumber++;
							cMileBSwitchInfo.Offset = -1;
						}
						else
						{
							cMileBSwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0004:
						if(cMileBSwitchInfo.LastSwitchState == 0X0000)
						{
							cMileBSwitchInfo.MileUnitNumber--;
							cMileBSwitchInfo.Offset = 1;
						}
						else if(cMileBSwitchInfo.LastSwitchState == 0X0008)
						{
							cMileBSwitchInfo.MileUnitNumber++;
							cMileBSwitchInfo.Offset = -1;
						}
						else
						{
							cMileBSwitchInfo.Offset = 0;
						}
						break;	
					default:
						break;
				}
				
				cMileBSwitchInfo.LastSwitchStateEx = cMileBSwitchInfo.LastSwitchState;
				
				cMileBSwitchInfo.LastSwitchState = cMileBSwitchInfo.CurrentSwitchState;
			}
			else
			{
				
								
				switch(g_u16MileBCurrentState)
				{
					case 0x0000:
						cMileBSwitchInfo.LastSwitchState = cMileBSwitchInfo.LastSwitchStateEx;

						cMileBSwitchInfo.MileUnitNumber = cMileBSwitchInfo.MileUnitNumber + cMileBSwitchInfo.Offset;
						if(cMileBSwitchInfo.LastSwitchState == 0X0008)
						{
							cMileBSwitchInfo.MileUnitNumber--;
							cMileBSwitchInfo.Offset = 1;
						}
						else if(cMileBSwitchInfo.LastSwitchState == 0X0004)
						{
							cMileBSwitchInfo.MileUnitNumber++;
							cMileBSwitchInfo.Offset = -1;
						}
						
						cMileBSwitchInfo.LastSwitchStateEx = cMileBSwitchInfo.LastSwitchState;
				
						cMileBSwitchInfo.LastSwitchState = cMileBSwitchInfo.CurrentSwitchState;
						break;
						
					default:
						break;
				}
				
				
				
			}
			
			cMileBSwitchInfo.bMileState = FALSE;
		}
	}
	
	
	g_u16MileBLastState = g_u16MileBCurrentState;
}

STATIC VOID MileCStateThread(VOID)
{
	if(g_u16MileCCurrentState != g_u16MileCLastState)
	{
		if(g_u16MileCCurrentState == 0x00c0)
		{
			cMileCSwitchInfo.bMileState = TRUE;
		}
		else
		{
			cMileCSwitchInfo.CurrentSwitchState = g_u16MileCCurrentState;
			
			if(cMileCSwitchInfo.bMileState == TRUE)
			{
				switch(g_u16MileCCurrentState)
				{
					case 0x0000:
						if(cMileCSwitchInfo.LastSwitchState == 0X0080)
						{
							cMileCSwitchInfo.MileUnitNumber--;
							cMileCSwitchInfo.Offset = 1;
						}
						else if(cMileCSwitchInfo.LastSwitchState == 0X0040)
						{
							cMileCSwitchInfo.MileUnitNumber++;
							cMileCSwitchInfo.Offset = -1;
						}
						else
						{
							cMileCSwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0080:
						if(cMileCSwitchInfo.LastSwitchState == 0X0040)
						{
							cMileCSwitchInfo.MileUnitNumber--;
							cMileCSwitchInfo.Offset = 1;
						}

						else if(cMileCSwitchInfo.LastSwitchState == 0X0000)
						{
							cMileCSwitchInfo.MileUnitNumber++;
							cMileCSwitchInfo.Offset = -1;
						}
						else
						{
							cMileCSwitchInfo.Offset = 0;
						}
						break;
						
					case 0x0040:
						if(cMileCSwitchInfo.LastSwitchState == 0X0000)
						{
							cMileCSwitchInfo.MileUnitNumber--;
							cMileCSwitchInfo.Offset = 1;
						}
						else if(cMileCSwitchInfo.LastSwitchState == 0X0080)
						{
							cMileCSwitchInfo.MileUnitNumber++;
							cMileCSwitchInfo.Offset = -1;
						}
						else
						{
							cMileCSwitchInfo.Offset = 0;
						}
						break;	
					default:
						break;
				}
				
				cMileCSwitchInfo.LastSwitchStateEx = cMileCSwitchInfo.LastSwitchState;
				
				cMileCSwitchInfo.LastSwitchState = cMileCSwitchInfo.CurrentSwitchState;
			}
			else
			{
				
								
				switch(g_u16MileCCurrentState)
				{
					case 0x0000:
						cMileCSwitchInfo.LastSwitchState = cMileCSwitchInfo.LastSwitchStateEx;

						cMileCSwitchInfo.MileUnitNumber = cMileCSwitchInfo.MileUnitNumber + cMileCSwitchInfo.Offset;
						if(cMileCSwitchInfo.LastSwitchState == 0X0080)
						{
							cMileCSwitchInfo.MileUnitNumber--;
							cMileCSwitchInfo.Offset = 1;
						}
						else if(cMileCSwitchInfo.LastSwitchState == 0X0040)
						{
							cMileCSwitchInfo.MileUnitNumber++;
							cMileCSwitchInfo.Offset = -1;
						}
						
						cMileCSwitchInfo.LastSwitchStateEx = cMileCSwitchInfo.LastSwitchState;
				
						cMileCSwitchInfo.LastSwitchState = cMileCSwitchInfo.CurrentSwitchState;
						break;
						
					default:
						break;
				}
				
				
				
			}
			
			cMileCSwitchInfo.bMileState = FALSE;
		}
	}
	
	
	g_u16MileCLastState = g_u16MileCCurrentState;
}

VOID MileRunProc(VOID)
{
	g_u16MileACurrentState = (GPIO_ReadInputData(GPIOA) & 0x00c0);
	
	g_u16MileBCurrentState = (GPIO_ReadInputData(GPIOA) & 0x000c);
	
	g_u16MileCCurrentState = (GPIO_ReadInputData(GPIOB) & 0x00c0);
		
	MileAStateThread();
	
	MileBStateThread();
	
	MileCStateThread();
		
}


VOID MileageInit(VOID)
{
    MileDataInit();
    MileGpioInit();
}
  

