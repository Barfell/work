#include "Test.h"
#include "Serial.h" 
#include "Mile.h"


VOID BoardInit(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);
		
	MileageInit();
			
}
STATIC VOID TestProc(VOID)
{
//	TestUart1();
//	TestUart1Timer();
//	TestEtrSynProc();
	TestMileageProc();
//	TestMileageProcEx();
}

STATIC VOID AppProc(VOID)
{

}

int main(void)
{	

	OsInit();
	BoardInit();
	TestProc();
	AppProc();
	return 0;
}

