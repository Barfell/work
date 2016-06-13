#ifndef _MILEAGE_H
#define _MILEAGE_H

#include "kernal.h"

typedef struct _tagMileSwitchInfo
{
 
    U16 CurrentSwitchState; //���浱ǰ�Ľӽ�����״̬
    U16 LastSwitchState;//�ӽ�����״̬����
	U16 LastSwitchStateEx;//�ӽ�����״̬����
	S8 Offset;
	BOOL bMileState;
	S32 MileUnitNumber;
 
}CMileSwitchInfo, *PMileSwitchInfo;

typedef struct _tagMileRecordInfo
{
    float mmileage;//��ʻ���XXXXXXXX.XX mm
    float  mileage;//��ʻ�����m��ʾ xxxxx.xxxM
    U8 MileSign;//���MM������
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
