#include "board.h"
#include "iap.h"
extern iapfun jump2app; 
STATIC VOID BoardInit(VOID)
{
	uart2_init(115200, 256, 2060);

}


VOID RCC_Configuration(VOID)
{
	RCC_DeInit();//������ RCC�Ĵ�������Ϊȱʡֵ

	RCC_HSICmd(ENABLE);//ʹ��HSI  
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)//�ȴ�HSIʹ�ܳɹ�
	{
	}

	if(1)
	{
		//FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//FLASH_SetLatency(FLASH_Latency_2);

		RCC_HCLKConfig(RCC_SYSCLK_Div1);   
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);

		//���� PLL ʱ��Դ����Ƶϵ��
		RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 2, 7);                
		//ʹ�ܻ���ʧ�� PLL,�����������ȡ��ENABLE����DISABLE
		RCC_PLLCmd(ENABLE);//���PLL������ϵͳʱ��,��ô�����ܱ�ʧ��
		//�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		//����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
		//�ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ
		//  0x00��HSI ��Ϊϵͳʱ�� 
		//  0x04��HSE��Ϊϵͳʱ�� 
		//  0x08��PLL��Ϊϵͳʱ��  
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}

INT main(VOID)
{
//	RCC_Configuration();
    OsInit();
    BoardInit();

    TestBoot();
 
    return 0;
}

