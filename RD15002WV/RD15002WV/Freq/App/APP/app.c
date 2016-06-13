#include  <includes.h>

/***************************************************************/
//������ƿ�
static  OS_TCB   AppTaskTASK1TCB;
static  OS_TCB   AppTaskTASK2TCB;
static  OS_TCB   AppTaskTASK3TCB;
//�����ջ
static  CPU_STK  AppTaskTASK1Stk[APP_CFG_TASK_TASK1_STK_SIZE];
static  CPU_STK  AppTaskTASK2Stk[APP_CFG_TASK_TASK2_STK_SIZE];
static  CPU_STK  AppTaskTASK3Stk[APP_CFG_TASK_TASK3_STK_SIZE];

/***************************************************************/
PQueueInfo pUart3QueueInfo;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ʼ����
void  AppTaskStart (void *p_arg)
{
	OS_ERR  err;
	CPU_Init();//��ʼ��cpu�������жϣ�����ʱ�����
	BSP_Tick_Init();//���õδ�ʱ��
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
				 
	//����������������ɾ���Լ�
    OSTaskDel((OS_TCB*)0,&err);
}




















///////////////////////////////////////////////////////////////////////////////////////////////////////////
//�û�����1
void task1(void)
{
	OS_ERR      err;
	while(1)
	{
		OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_DLY,&err);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void task2(void)
{
	OS_ERR      err;
	
//	RTC_Config(extrnal);
//	set_time(0x15,0x12,0x28,0x23,0x59,0x50,0x01,RTC_H12_PM);
//	set_alarm(0,1,0);
//	printf("%s\r\n",get_time());
	
    while(1)
    {
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_DLY,&err);
		//printf("%s\r\n",get_time());
    }
}

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void task3(void)
{
	OS_ERR      err;
	pUart3QueueInfo = malloc(sizeof(CQueueInfo));//�����ڴ�
	memset(pUart3QueueInfo, 0, sizeof(CQueueInfo));
	
	bsp_io_init();//IO��
	UsartConfig();//������������
	SW_12V(1);//��Դ
	SW_5V(1);//������Դ�����ڼ��ز�Z
	FreqModuleInit();//��Ƶ��ģ���ʼ��
	LTC2402Init();
	voltage_adc_init();
	GetFreq(1);
	SW_VW(1);
	get_time();
	
	while(1)
	{
		AppMain();
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_DLY,&err);//10������һ���Ƿ������
	}
	
	
}



//			SW_12V(0);//��Դ
//			SW_5V(0);//������Դ�����ڼ��ز�
//			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err);
//			ConfigPINToListen();
//			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
//			SetClock();//���ø���CPUʱ��
//			bsp_io_init();//IO��
//			SW_12V(1);//��Դ
//			SW_5V(1);//������Դ�����ڼ��ز�
//			//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err);
//			UsartConfig();//������������
//			FreqModuleInit();//��Ƶ��ģ���ʼ��
//			LTC2402Init();
//			voltage_adc_init();
//			GetFreq(1);
//			read_dev_id(dev_ID);//��ȡID