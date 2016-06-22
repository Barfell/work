#include "Mileage.h"
#include "key.h"

#define chang_mileage 5.236 //接近开关每变化一次 里程的变化值5.236mm
#define corotation   0x18   //轮子正转
#define reversal     0x19   //轮子反转
#define no_change     0x3d  //不转动



struct turn_direction_s  turn_direction;
struct mileage_record_s  mileage_record;
volatile unsigned char Firstmileage_check;
unsigned char car_direction;

U16 switch_value;


/************************************************************************
*Precedure  :       Mileage_Gpio_Greate
*Funtion  :	     里程计IO口创建
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************

************************************************************************/

STATIC VOID Mileage_Gpio_Greate(VOID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure ;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
        
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;                
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure); 


    switch_value = (GPIO_ReadInputData(GPIOE) & 0x6000);
    switch_value = ((switch_value >> 13) & 0x03);
}

STATIC VOID Calculate_Mileage(VOID)
{
    turn_direction.current_switchstate=switch_value;
    if (turn_direction.driver_direction=='+')
    {
        switch(turn_direction.current_switchstate)
        {
            case 0x0000:
                if(turn_direction.backup_switchstate==0X0002)
                {

                    turn_direction.corotation_state=corotation;
                    mileage_record.mmileage=mileage_record.mmileage+chang_mileage;

                    break; 
                }
                else if(turn_direction.backup_switchstate==0X0001)
                {
                    turn_direction.corotation_state=reversal;
                    mileage_record.mmileage=mileage_record.mmileage-chang_mileage;

                    break;
                }
                else if(turn_direction.backup_switchstate==0X0000)
                {
                    turn_direction.corotation_state=no_change;
                    mileage_record.mmileage=mileage_record.mmileage;
                    break;
                }
            case 0x0001:

                if(turn_direction.backup_switchstate==0X0000)
                {
                turn_direction.corotation_state=corotation;
                mileage_record.mmileage=mileage_record.mmileage+chang_mileage;
                break;  
                }

                else if(turn_direction.backup_switchstate==0X0003)
                {
                turn_direction.corotation_state=reversal;
                mileage_record.mmileage=mileage_record.mmileage-chang_mileage;
                break;
                }
                else if(turn_direction.backup_switchstate==0X0001)
                {
                turn_direction.corotation_state=no_change;
                mileage_record.mmileage=mileage_record.mmileage;
                break;
                }

            case 0x0002:

                if(turn_direction.backup_switchstate==0X0003)
                {
                turn_direction.corotation_state=corotation;
                mileage_record.mmileage=mileage_record.mmileage+chang_mileage;
                break;  
                }
                else if(turn_direction.backup_switchstate==0X0000)

                {
                turn_direction.corotation_state=reversal;
                mileage_record.mmileage=mileage_record.mmileage-chang_mileage;
                break;
                }
                else if(turn_direction.backup_switchstate==0X0002)
                {
                turn_direction.corotation_state=no_change;
                mileage_record.mmileage=mileage_record.mmileage;
                break;
                }
            case 0x0003:

                if(turn_direction.backup_switchstate==0X0001)
                {
                turn_direction.corotation_state=corotation;
                mileage_record.mmileage=mileage_record.mmileage+chang_mileage;
                break; 
                }
                else if(turn_direction.backup_switchstate==0X0002)
                {
                turn_direction.corotation_state=reversal;
                mileage_record.mmileage=mileage_record.mmileage-chang_mileage;
                break;
                }

                else if(turn_direction.backup_switchstate==0X0003)
                {
                turn_direction.corotation_state=no_change;
                mileage_record.mmileage=mileage_record.mmileage;
                break;
                }

            default:
                break;
        }
        turn_direction.backup_switchstate=turn_direction.current_switchstate;
    }

}

/************************************************************************
*Precedure  :       calculate_mileage
*Funtion  :	     计算行驶里程 
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/
VOID calculate_mileage(VOID)
{ 

    long mileage_int;
    if(mileage_record.mmileage>=0)
        mileage_record.mileage_sign='+';
    else 
        mileage_record.mileage_sign='-';

    mileage_int=(long)mileage_record.mmileage;
    mileage_record.mileage=((double)mileage_int/1000.000);	             
					
}

/************************************************************************
*Precedure  :      mileage_init
*Funtion  :	    初始里程初始化
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/																	
VOID mileage_init(VOID)
{
    turn_direction.backup_switchstate=0x00;
    turn_direction.current_switchstate=0x00;
    turn_direction.corotation_state= corotation;
    Firstmileage_check=0x00;

    mileage_record.mmileage=00000000.000;
    mileage_record.mileage=00000.000;
    mileage_record.mileage_sign='+';
    car_direction='+';
    turn_direction.driver_direction='+';
}

//里程中断服务函数，发生移动时候，进行轨距记录
VOID EXTI15_10_IRQHandler(VOID)
{

    //里程ISR
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        switch_value = (GPIO_ReadInputData(GPIOE) & 0x6000);
        switch_value = ((switch_value >> 13) & 0x03);
        Calculate_Mileage();

        EXTI_ClearITPendingBit(EXTI_Line13); 
    }
	//里程ISR
    else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        switch_value = (GPIO_ReadInputData(GPIOE) & 0x6000);
        switch_value = ((switch_value >> 13) & 0x03);
        Calculate_Mileage();

        EXTI_ClearITPendingBit(EXTI_Line14);
    }
	//按键
	else if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{	
		EXTI_ClearITPendingBit(EXTI_Line10); //清除LINE上的中断标志位
		KeyScan();
  
	}
}


VOID MileageInit(VOID)
{
    mileage_init();
    Mileage_Gpio_Greate();
}
  

