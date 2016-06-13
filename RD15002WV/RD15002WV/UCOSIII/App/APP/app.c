/*//���ڶ�����֮����л�-
1.�ڶ������ʱ��ÿ��������Ҫһ����ʱ����������������������������
2.ֻ���������������ʱ����������л������л����õ����ȼ�������õ����У�
3.��������������̬����һֱִ�и����ȼ����Ǹ���
*/
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
		if(UploadFlag == 0)
		{
			SW_12V(0);//��Դ
			SW_5V(0);//������Դ�����ڼ��ز�
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err);
			ConfigPINToListen();
			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
			SetClock();//���ø���CPUʱ��
			BoardGPIOConfig();//IO��
			SW_12V(1);//��Դ
			SW_5V(1);//������Դ�����ڼ��ز�
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err);
			UsartConfig();//������������
			Nvic_Config();
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//�û�����2
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
	BoardGPIOConfig();//IO��
	UsartConfig();//������������
	Nvic_Config();
	SW_12V(1);//��Դ
	SW_5V(1);//������Դ�����ڼ��ز�Z
	FreqModuleInit();//��Ƶ��ģ���ʼ��
	GetFreq(1);

	while(1)
	{			
		
//		OSTimeDlyHMSM(0,0,500,0,OS_OPT_TIME_DLY,&err);
//		printf("SCT200T15002-Channel: 1  FREQUENCY:%f\r\n",GetFreq(1));
//		printf("SCT200T15002-Channel: 2  FREQUENCY:%f\r\n",GetFreq(2));
//		printf("SCT200T15002-Channel: 3  FREQUENCY:%f\r\n",GetFreq(3));
//		printf("SCT200T15002-Channel: 4  FREQUENCY:%f\r\n",GetFreq(4));
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_DLY,&err);
		if(UploadFlag == 1)//ȷ����Ҫ�ϴ�������
		{
			
			FreqModuleInit();//��Ƶ��ģ���ʼ��
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
			SW_12V(0);//��Դ
			SW_5V(0);//������Դ�����ڼ��ز�
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err);
			ConfigPINToListen();
			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
			SetClock();//���ø���CPUʱ��
			BoardGPIOConfig();//IO��
			SW_12V(1);//��Դ
			SW_5V(1);//������Դ�����ڼ��ز�
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err);
			UsartConfig();//������������
			Nvic_Config();
		}
	}
}



