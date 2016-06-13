#ifndef _MILEAGE_H
#define _MILEAGE_H

#include "kernal.h"

struct turn_direction_s
{
 
    unsigned char current_switchstate; //���浱ǰ�Ľӽ�����״̬
    unsigned char backup_switchstate;//�ӽ�����״̬����
    unsigned char corotation_state;//С��ǰ��״̬��־
    unsigned char driver_direction;//0������ 1������
 
};

struct mileage_record_s
{
    double mmileage;//��ʻ���XXXXXXXX.XX mm
    double  mileage;//��ʻ�����m��ʾ xxxxx.xxxM
    unsigned char mileage_sign;//���MM������
};
extern struct mileage_record_s  mileage_record;

VOID MileageInit(VOID);
VOID mileage_init(VOID);
VOID calculate_mileage(VOID);

#endif
