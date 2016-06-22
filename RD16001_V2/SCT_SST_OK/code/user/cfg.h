#ifndef _CFG_H
#define _CFG_H

/*
  �ڲ��洢�ṹ��
    11000-- (APP ) ---18000            28K
    FFC0--- (VECTOR)--FFFF      
    B000--- (CFG) ----FF00                      
    3100---��BOOT��---B000             32K
*/

/*116k
(interrrupt )    0x0ffff - 0xffc0
(code memery)    0x01ffff - 0x003100
*/

/*--------FLASH memory organization-------------------------
*MAIN FLASH  INTERRUPT VECTOR   :  0XFFFF       -       0XFFC0  
*MAIN FLASH  CODE MEMORT        :  0X01FFFF     -       0X3100-0XFFC0     0XFFFF-0X01FFFF  
*RAM                            :  0X30FF       -       0X1100
*/




/*cfg:   8000 ---- 9fff*/
#define _LOWPOWER_MODE_
//#define _ONLINE_MODE_


#define MACHINE_ID                              "SCT16012"//��������
#define INTERVAL_TIME                           2  //Ĭ��ʱ���� ��λ��min������Ҫ5����
#define CMD_TIME                                60 //Ĭ�ϵ�cmd�ȴ�ʱ��


/*--------------------------------------------------------------------------------------------------------*/
#define DEVICE_FIRST_TIME_POWERON_ADDR          0xB000//��������Ƿ��ǵ�һ���ϵ���Ϣ
#define INTERVAL_TIME_ADDR                      0xB200//��Ųɼ����ʱ��
#define CMD_TIME_ADDR                           0XB400//���CMD�ȴ�ʱ��
#define CONNECT_TYPE_ADDR                       0xB600//������������ӷ�ʽ��0��RF���� 1:DTU���ӣ�
#define PROTOCOL_TYPE_ADDR                      0xB800//��������Ĵ����Ƿ����Э���־(0:����Э�飬1:��Э��)


/*--------------------------------------------------------------------------------------------------------*/
#define CHANNEL_TYPE_ADDR                       0xBA00//��ű���ͨ�����ͣ�0��VW  1��485��
#define SENSOR_ID_ADDR                          0xBC00//��ű���ͨ�����ӵ�485���������ID (�˸�  ÿ���������ı�ŷ�Χ0 - 255)

/*--------------------------------------------------------------------------------------------------------*/
#define SUB_DEVICE_ID                           0xBE00//������豸���ӵ����豸���豸���ID���˸�  ÿ�����豸��ŷ�ΧΪ��0-255��
#define SUB_DEVICE_TYPE_ADDR                    0xC200//������豸���ӵ����豸��ͨ�����ͣ�0��VW  1��485��
#define SUB_DEVICE_SENSOR_ID_ADDR               0xC400//������豸���ӵ����豸���ӵ�485���������ID (�˸�  ÿ���������ı�ŷ�Χ0 - 255)

/*--------------------------------------------------------------------------------------------------------*/
#define SET_INTERVAL_TIME_FLAG_ADDR             0xC600//�����һ���Ƿ���Ҫ���õ�ʱ�����ı�־
#define NEXT_INTERVAL_TIME_ADDR                 0xC800//�����һ����Ҫ���õ�ʱ����

/*--------------------------------------------------------------------------------------------------------*/
#define RECORD_DATA_ADDR                        114401 //ǰ100K�������洢
#define RECORD_DATA_LEN_ADDR                    102401 //�洢��������ݳ���
#define RECORD_READ_POS_ADDR                    107401 //�洢��ǰ��������

#endif