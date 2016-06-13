#ifndef _MILEAGE_H
#define _MILEAGE_H

#include "kernal.h"

struct turn_direction_s
{
 
    unsigned char current_switchstate; //保存当前的接近开关状态
    unsigned char backup_switchstate;//接近开关状态备份
    unsigned char corotation_state;//小车前进状态标志
    unsigned char driver_direction;//0正方向 1反方向
 
};

struct mileage_record_s
{
    double mmileage;//行驶里程XXXXXXXX.XX mm
    double  mileage;//行驶里程有m表示 xxxxx.xxxM
    unsigned char mileage_sign;//里程MM级符号
};
extern struct mileage_record_s  mileage_record;

VOID MileageInit(VOID);
VOID mileage_init(VOID);
VOID calculate_mileage(VOID);

#endif
