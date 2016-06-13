#ifndef _CFG_H
#define _CFG_H

/*116k
(interrrupt )    0x0ffff - 0xffc0
(code memery)    0x01ffff - 0x003100
*/

/*--------FLASH memory organization-------------------------
*MAIN FLASH  INTERRUPT VECTOR   :  0XFFFF       -       0XFFC0  
*MAIN FLASH  CODE MEMORT        :  0X01FFFF     -       0X3100  
*RAM                            :  0X30FF       -       0X1100
*/

/*cfg:   8000 ---- 9fff*/
#define MACHINE_ID                              "SCT16002"//��������
#define SUB_NUM                                 2      //��������Ϊ�ڼ������豸
#define INTERVAL_TIME                           8  //Ĭ��ʱ���� ��λ��min
#define CMD_TIME                                60 //Ĭ�ϵ�cmd�ȴ�ʱ��



/*--------------------------------------------------------------------------------------------------------*/
#define DEVICE_FIRST_TIME_POWERON_ADDR          0x9000//��������Ƿ��ǵ�һ���ϵ���Ϣ

#define INTERVAL_TIME_ADDR                      0x9200//��Ųɼ����ʱ��

#define CMD_TIME_ADDR                           0X9400//���CMD�ȴ�ʱ��

#define CONNECT_TYPE_ADDR                       0x9600//������������ӷ�ʽ��0��RF���� 1:DTU���ӣ�

#define PROTOCOL_TYPE_ADDR                      0x9800//��������Ĵ����Ƿ����Э���־(0:����Э�飬1:��Э��)


/*--------------------------------------------------------------------------------------------------------*/
#define CHANNEL_TYPE_ADDR                       0x9A00//��ű���ͨ�����ͣ�0��VW  1��485��

#define SENSOR_ID_ADDR                          0x9C00//��ű���ͨ�����ӵ�485���������ID (�˸�  ÿ���������ı�ŷ�Χ0 - 255)


/*--------------------------------------------------------------------------------------------------------*/
#define SUB_DEVICE_ID                           0x9E00//������豸���ӵ����豸���豸���ID���˸�  ÿ�����豸��ŷ�ΧΪ��0-255��

#define SUB_DEVICE_TYPE_ADDR                    0xA200//������豸���ӵ����豸��ͨ�����ͣ�0��VW  1��485��

#define SUB_DEVICE_SENSOR_ID_ADDR               0xA400//������豸���ӵ����豸���ӵ�485���������ID (�˸�  ÿ���������ı�ŷ�Χ0 - 255)




/*rain:  12000 ---- 1A000*/
//32K
/*rain temp:   1B000*/
//
#define RAIN_ADDR                               0x12000//���������λ��
#define RAIN_TEMP_ADDR                          0x1A000//�������ݽ����Ļ���λ��
#define RAIN_NUM_ADDR                           0x1B000//������Ŀ��λ��

#endif