#ifndef _BOOT_H_
#define _BOOT_H_

/********************************************************************************
//msp�������߸�λ���һ��������ǻ��PCָ�������ж��������ַ����RESETλ�ã���ת����Ӧ�Ĵ�������
//ÿ���̼�����Ӧ��Ӧ���ж����������̼���Ӧ���ж������������������ж��������ַ������λ��ͻ�ֱ��ִ�й̼�
APP�˴�������
//����Ҫ��IAR ����������.XCL�ļ������޸ģ���FLASH���з��䣬����ο�������MSP430��Ƭ���Ķ���������
1.�û�APP�����������
2.Ӳ�����ܵ�������FLASH�����BOOT���ж������������򿽱��������ж�������ַ��
3.���ÿ��Ź���Ӳ����λ����msp430ÿ�θ�λ�����Ȱ�PCָ�������ж��������RESETλ�ã�����λ�ÿ��Կ������������ֲᣩ


BOOT�˵Ĵ�������
1.���뵽BOOT�ĵ�һ��������Ǳ��������ж�������BOOT���ж�������������
	���ܽ��뵽BOOT˵���ǵ�һ��Ӳ�����У�������APP�˽��յ������������ת��BOOT����������£����ǵ�һ��Ӳ�����еĻ�����λ������APP�У�
2.����APP��flash���򣬵ȴ��������ݰ���
3.���������ݰ�������ϣ�д�뵽APP Flash��ɣ���
4.������Ϻ󣬽�APP ���ж�����������������ݿ����������ж�������ַ��׼��APP���л�����
5.���ÿ��Ź���Ӳ����λ��
********************************************************************************
*/

#define APP_ADDR_TOP                    0xe000
#define APP_VECTOR_TOP                  0xDFFF
#define APP_VECTOR_BUTTOM               0xDFE0
#define APP_ADDR_BUTTOM                 0x5000



#define BOOT_ADDR_TOP                   0x4000
#define BOOT_VECTOR_TOP                 0x3FFF
#define BOOT_VECTOR_BUTTOM              0x3FE0
#define BOOT_ADDR_BUTTOM                0x1100


#define HARDWARE_VECTOR_TOP                 0XFFFF
#define HARDWARE_VECTOR_BUTTOM              0XFFE0



void Vector_BOOT2HRAD(void);
void FirmwareUpdate(void);


#endif