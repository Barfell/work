/*//关于多任务之间的切换-
1.在多任务的时候，每个任务需要一个延时函数或者其他动作来阻塞本任务，
2.只有在阻塞本任务的时候进行任务切换才能有机会让低优先级的任务得到运行，
3.假如任务不在阻塞态，会一直执行高优先级的那个。
*/
#include  <includes.h>

/***************************************************************/
//任务控制块
static  OS_TCB   AppTaskTASK1TCB;
static  OS_TCB   AppTaskTASK2TCB;
static  OS_TCB   AppTaskTASK3TCB;
//任务堆栈
static  CPU_STK  AppTaskTASK1Stk[APP_CFG_TASK_TASK1_STK_SIZE];
static  CPU_STK  AppTaskTASK2Stk[APP_CFG_TASK_TASK2_STK_SIZE];
static  CPU_STK  AppTaskTASK3Stk[APP_CFG_TASK_TASK3_STK_SIZE];

OS_SEM EnterStopFlag;
/***************************************************************/
extern unsigned char RXData;
extern unsigned char UploadFlag;
extern unsigned char Reciv[20];
extern unsigned char RecivNum;
unsigned char aaa[19] = {	0xfe,0x01,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0xff };

unsigned char bbb[6] = {	0x00,0x00,0x00,0x00,0x00,
							0x00};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//开始任务
void  AppTaskStart (void *p_arg)
{
	OS_ERR  err;
	CPU_Init();//初始化cpu，禁用中断，开启时间戳等
	BSP_Tick_Init();//设置滴答定时器
/*------------------------------*/		 
	OSTaskCreate((OS_TCB       *)&AppTaskTASK1TCB,              
                 (CPU_CHAR     *)"task1",
                 (OS_TASK_PTR   )task1, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_TASK1_PRIO,
                 (CPU_STK      *)&AppTaskTASK1Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK1_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK1_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
/*------------------------------*/
	OSTaskCreate((OS_TCB       *)&AppTaskTASK2TCB,              
                 (CPU_CHAR     *)"task2",
                 (OS_TASK_PTR   )task2, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_TASK2_PRIO,
                 (CPU_STK      *)&AppTaskTASK2Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK2_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK2_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);  
/*-------------------------------*/
	OSTaskCreate((OS_TCB       *)&AppTaskTASK3TCB,              
                 (CPU_CHAR     *)"task3",
                 (OS_TASK_PTR   )task3, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_TASK3_PRIO,
                 (CPU_STK      *)&AppTaskTASK3Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK3_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_TASK3_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
				 
	//创建好其他任务后就删除自己
    OSTaskDel((OS_TCB*)0,&err);
}




















///////////////////////////////////////////////////////////////////////////////////////////////////////////
//用户任务1
void task1(void)
{
	OS_ERR      err;
	while(1)
	{
		OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_DLY,&err);
		if(UploadFlag == 0)
		{
			SW_12V(0);//电源
			SW_5V(0);//正负电源，用于检测回波
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err);
			ConfigPINToListen();
			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
			SetClock();//配置各级CPU时钟
			BoardGPIOConfig();//IO口
			SW_12V(1);//电源
			SW_5V(1);//正负电源，用于检测回波
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err);
			UsartConfig();//串口设置配置
			Nvic_Config();
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//用户任务2
void task2(void)
{
	OS_ERR      err;
	while(1)
	{
		OSTimeDlyHMSM(0,0,15,0,OS_OPT_TIME_DLY,&err);
		//printf("xxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
	}
}

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void task3(void)
{
	OS_ERR      err;
	BoardGPIOConfig();//IO口
	UsartConfig();//串口设置配置
	Nvic_Config();
	SW_12V(1);//电源
	SW_5V(1);//正负电源，用于检测回波Z
	FreqModuleInit();//测频率模块初始化
	GetFreq(1);

	while(1)
	{			
		
//		OSTimeDlyHMSM(0,0,500,0,OS_OPT_TIME_DLY,&err);
//		printf("SCT200T15002-Channel: 1  FREQUENCY:%f\r\n",GetFreq(1));
//		printf("SCT200T15002-Channel: 2  FREQUENCY:%f\r\n",GetFreq(2));
//		printf("SCT200T15002-Channel: 3  FREQUENCY:%f\r\n",GetFreq(3));
//		printf("SCT200T15002-Channel: 4  FREQUENCY:%f\r\n",GetFreq(4));
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_DLY,&err);
		if(UploadFlag == 1)//确认需要上传数据了
		{
			
			FreqModuleInit();//测频率模块初始化
			GetFreq(1);
			printf("%s",aaa);
			printf("SCT200T15003-2015/7/8/Wednesday-15-36-9\r\n");
			printf("SCT200T15003-ID=0x87031923 53578748 66eff48\r\n");
			printf("SCT200T15003-Mode = 10 minutes Internal\r\n");
			printf("SCT200T15003-Current voltage = 10.90V\r\n");
			printf("SCT200T15003-Channel: 1  Temperature :34.47\r\n");
			printf("SCT200T15003-Channel: 2  Temperature :34.43\r\n");
			printf("SCT200T15003-Channel: 3  Temperature :30.40\r\n");
			printf("SCT200T15003-Channel: 4  Temperature :25.90\r\n");
			printf("SCT200T15003-Channel: 1  FREQUENCY:%f\r\n",GetFreq(1));
			printf("SCT200T15003-Channel: 2  FREQUENCY:%f\r\n",GetFreq(2));
			printf("SCT200T15003-Channel: 3  FREQUENCY:%f\r\n",GetFreq(3));
			printf("SCT200T15003-Channel: 4  FREQUENCY:%f\r\n",GetFreq(4));
			printf("%s",bbb);

			UploadFlag = 0;
			SW_12V(0);//电源
			SW_5V(0);//正负电源，用于检测回波
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err);
			ConfigPINToListen();
			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
			SetClock();//配置各级CPU时钟
			BoardGPIOConfig();//IO口
			SW_12V(1);//电源
			SW_5V(1);//正负电源，用于检测回波
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err);
			UsartConfig();//串口设置配置
			Nvic_Config();
		}
	}
}



