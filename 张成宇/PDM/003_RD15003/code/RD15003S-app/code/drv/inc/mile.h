#ifndef _MILEAGE_H
#define _MILEAGE_H

#include "kernal.h"

typedef struct _tagMileSwitchInfo
{
 
    U16 CurrentSwitchState; //保存当前的接近开关状态
    U16 LastSwitchState;//接近开关状态备份
	U16 LastSwitchStateEx;//接近开关状态备份
	S8 Offset;
	BOOL bMileState;
	S32 MileUnitNumber;
 
}CMileSwitchInfo, *PMileSwitchInfo;

typedef struct _tagMileRecordInfo
{
    float mmileage;//行驶里程XXXXXXXX.XX mm
    float  mileage;//行驶里程有m表示 xxxxx.xxxM
    U8 MileSign;//里程MM级符号
}CMileRecordInfo, *PMileRecordInfo;

EXTERN CMileRecordInfo  cMileARecordInfo;
EXTERN CMileRecordInfo  cMileBRecordInfo;
EXTERN CMileRecordInfo  cMileCRecordInfo;
EXTERN CMileSwitchInfo  cMileASwitchInfo;
EXTERN CMileSwitchInfo  cMileBSwitchInfo;
EXTERN CMileSwitchInfo  cMileCSwitchInfo;
VOID MileageInit(VOID);
VOID MileDataInit(VOID);
VOID CalculateMile(VOID);

#endif
