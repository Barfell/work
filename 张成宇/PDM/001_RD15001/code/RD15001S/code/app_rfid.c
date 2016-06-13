#include "app_rfid.h"
#include "uart.h"
#include "system.h"
#include "Init.h"

//uchar xdata g_szGetCurrentProgram[5] =      {0xFF, 0x00, 0x0C, 0x1D, 0x03};
//uchar xdata g_szBootFirmware[5] =           {0xFF, 0x00, 0x04, 0x1D, 0x0B};
//uchar xdata g_szSetFrequencyChannel[6] =    {0xFF, 0x01, 0x97, 0x06, 0x4B, 0xBB};//return FF 00 97 00 00 77 9E
//uchar xdata g_szSetProtocol[7] =            {0xFF, 0x02, 0x93, 0x00, 0x05, 0x51, 0x7D};
//uchar xdata g_szSetAntenna[8] =             {0xFF, 0x03, 0x91, 0x02, 0x01, 0x01, 0x42, 0xC5};//return FF 00 91 00 00 17 58
//uchar xdata g_szClearBuffer[5] =            {0xFF, 0x00, 0x2A, 0x1D, 0x25};//return FF 00 2A 00 00 01 E8
//uchar xdata g_szSearchTag[10] =              {0xFF, 0x05, 0x22, 0x00, 0x00, 0x13, 0x01, 0xF4, 0x2B, 0x19};//FF 07 22 00 00 00 00 13 00 00 00 01 8B 58
//uchar xdata g_szGetTagdata[8] =             {0xFF, 0x03, 0x29, 0x01, 0xFF, 0x00, 0x1B, 0x03};
//uchar xdata g_szGetTagIddata[8] =           {0xFF, 0x03, 0x29, 0x00, 0x00, 0x00, 0xF4, 0x22};//获取唯一ID
//uchar xdata g_szPrimeContinueReading[8] =   {0xFF, 0x03, 0x9A, 0x01, 0x0C, 0x00, 0xA3, 0x5D};//不断获取数据
//uchar xdata g_szContinueReading[21] =        {0xFF, 0x10, 0x2F, 0x00, 0x00, 0x01, 0x22, 0x00, 0x00, 0x05, 0x07, 0x22, 0x10, 0x00, 0x1B, 0x03, 0xE8, 0x00, 0x00, 0xDC, 0xD4};//不断获取数据，且为唯一ID
//uchar xdata g_szEnhanceDistance[7] =        {0xFF, 0x02, 0x92, 0x0b, 0xb8, 0x4a, 0xe1};//需要远距离时采用该指令
//uchar xdata g_szEnhanceSpeed1[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x02, 0x02, 0xde, 0xea};//增快速度指令1
//uchar xdata g_szEnhanceSpeed2[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x12, 0x00, 0xce, 0xe8};//增快速度指令2
//uchar xdata g_szEnhanceSpeed3[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x10, 0x00, 0xcc, 0xe8};//增快速度指令3
//uchar xdata g_szEnhanceSpeed4[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x11, 0x00, 0xcd, 0xe8};//增快速度指令4
//uchar xdata g_szEnhanceSpeed5[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x00, 0x00, 0xdc, 0xe8};//增快速度指令5
//uchar xdata g_szEnhanceSpeed6[9] =          {0xFF, 0x04, 0x9b, 0x05, 0x01, 0x00, 0x00, 0xa3, 0xfd};//增快速度指令5
//uchar xdata g_szContinueReadingEx[21] =      {0xFF, 0x10, 0x2F, 0x00, 0x00, 0x01, 0x22, 0x00, 0x00, 0x05, 0x07, 0x22, 0x10, 0x00, 0x1B, 0x03, 0xE8, 0x01, 0xFF, 0xDD, 0x2B};//不断获取数据，且不仅仅只有ID数据
//uchar xdata g_szStopReading[8] =            {0xFF, 0x03, 0x2F, 0x00, 0x00, 0x02, 0x5E, 0x86};//FF 01 2F 00 00 02 30 E6
uchar const code g_szGetCurrentProgram[5] =      {0xFF, 0x00, 0x0C, 0x1D, 0x03};
uchar const code g_szBootFirmware[5] =           {0xFF, 0x00, 0x04, 0x1D, 0x0B};
uchar const code g_szSetFrequencyChannel[6] =    {0xFF, 0x01, 0x97, 0x06, 0x4B, 0xBB};//return FF 00 97 00 00 77 9E
uchar const code g_szSetProtocol[7] =            {0xFF, 0x02, 0x93, 0x00, 0x05, 0x51, 0x7D};
uchar const code g_szSetAntenna[8] =             {0xFF, 0x03, 0x91, 0x02, 0x01, 0x01, 0x42, 0xC5};//return FF 00 91 00 00 17 58
uchar const code g_szClearBuffer[5] =            {0xFF, 0x00, 0x2A, 0x1D, 0x25};//return FF 00 2A 00 00 01 E8
uchar const code g_szSearchTag[10] =              {0xFF, 0x05, 0x22, 0x00, 0x00, 0x13, 0x01, 0xF4, 0x2B, 0x19};//FF 07 22 00 00 00 00 13 00 00 00 01 8B 58
uchar const code g_szGetTagdata[8] =             {0xFF, 0x03, 0x29, 0x01, 0xFF, 0x00, 0x1B, 0x03};
uchar const code g_szGetTagIddata[8] =           {0xFF, 0x03, 0x29, 0x00, 0x00, 0x00, 0xF4, 0x22};//获取唯一ID
uchar const code g_szPrimeContinueReading[8] =   {0xFF, 0x03, 0x9A, 0x01, 0x0C, 0x00, 0xA3, 0x5D};//不断获取数据
uchar const code g_szContinueReading[21] =        {0xFF, 0x10, 0x2F, 0x00, 0x00, 0x01, 0x22, 0x00, 0x00, 0x05, 0x07, 0x22, 0x10, 0x00, 0x1B, 0x03, 0xE8, 0x00, 0x00, 0xDC, 0xD4};//不断获取数据，且为唯一ID
uchar const code g_szEnhanceDistance[7] =        {0xFF, 0x02, 0x92, 0x0b, 0xb8, 0x4a, 0xe1};//需要远距离时采用该指令
uchar const code g_szEnhanceSpeed1[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x02, 0x02, 0xde, 0xea};//增快速度指令1
uchar const code g_szEnhanceSpeed2[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x12, 0x00, 0xce, 0xe8};//增快速度指令2
uchar const code g_szEnhanceSpeed3[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x10, 0x00, 0xcc, 0xe8};//增快速度指令3
uchar const code g_szEnhanceSpeed4[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x11, 0x00, 0xcd, 0xe8};//增快速度指令4
uchar const code g_szEnhanceSpeed5[8] =          {0xFF, 0x03, 0x9b, 0x05, 0x00, 0x00, 0xdc, 0xe8};//增快速度指令5
uchar const code g_szEnhanceSpeed6[9] =          {0xFF, 0x04, 0x9b, 0x05, 0x01, 0x00, 0x00, 0xa3, 0xfd};//增快速度指令5
uchar const code g_szContinueReadingEx[21] =      {0xFF, 0x10, 0x2F, 0x00, 0x00, 0x01, 0x22, 0x00, 0x00, 0x05, 0x07, 0x22, 0x10, 0x00, 0x1B, 0x03, 0xE8, 0x01, 0xFF, 0xDD, 0x2B};//不断获取数据，且不仅仅只有ID数据
uchar const code g_szStopReading[8] =            {0xFF, 0x03, 0x2F, 0x00, 0x00, 0x02, 0x5E, 0x86};//FF 01 2F 00 00 02 30 E6
uchar const code g_szOnceMode[8] = {0xFF, 0x03, 0x9B, 0x05, 0x00, 0x01, 0xDC, 0xE9};
//const U8 g_szTag[13][14] =
//{
//    {0x10 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x11 , 0x03 , 0x04 , 0x00 , 0x03 , 0x24 , 0x1E , 0xB9},
//    {0xE2 , 0x00 , 0x20 , 0x75 , 0x58 , 0x11 , 0x02 , 0x53 , 0x23 , 0x90 , 0x1E , 0x43 , 0x51 , 0x68},
//    {0x10 , 0x05 , 0x00 , 0x23 , 0x00 , 0x00 , 0x20 , 0x14 , 0x05 , 0x10 , 0x04 , 0x65 , 0x8E , 0xFE},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x27 , 0x43 , 0xAF , 0x37},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x29 , 0x51 , 0xBE , 0x4B},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x56 , 0xB8 , 0xF0},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x28 , 0x87 , 0x26 , 0xC1},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x15 , 0x14 , 0x11 , 0xB2 , 0x76},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x23 , 0x70 , 0x65 , 0xC3},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x77 , 0xBF , 0x82},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x11 , 0xB3 , 0xE2},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x26 , 0x22 , 0xE0 , 0x81},
//    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x23 , 0x78 , 0xE4 , 0xCB}
// 
//};

uchar const g_szTag[17][14] =
{
    {0x10 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x11 , 0x03 , 0x04 , 0x00 , 0x03 , 0x24 , 0x1E , 0xB9},
    {0xE2 , 0x00 , 0x20 , 0x75 , 0x58 , 0x11 , 0x02 , 0x53 , 0x23 , 0x90 , 0x1E , 0x43 , 0x51 , 0x68},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x28 , 0x12 , 0xF5 , 0xDD},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x42 , 0xD9 , 0x74},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x06 , 0xD1 , 0x34},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x26 , 0x35 , 0x82 , 0x57},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x57 , 0xA8 , 0xD1},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x21 , 0x85 , 0xB1},   
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x66 , 0xBD , 0x92},   
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x26 , 0x08 , 0x65 , 0xA9}, 
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x14 , 0xE3 , 0x47}, 
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x18 , 0x11 , 0xFA},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x31 , 0x57 , 0x54 , 0x57},  
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x11 , 0x80 , 0xD3},   
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x77 , 0x8C , 0xB3},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x31 , 0xA4 , 0xB1},
    {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x23 , 0x39 , 0xBC , 0x2E},
};



//const U8 g_szTag1[] =                   {0x10 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x11 , 0x03 , 0x04 , 0x00 , 0x03 , 0x24 , 0x1E , 0xB9};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 00 00 00 00 20 11 03 04 00 03 24 1E B9 63 94
//const U8 g_szTag2[] =                   {0xE2 , 0x00 , 0x20 , 0x75 , 0x58 , 0x11 , 0x02 , 0x53 , 0x23 , 0x90 , 0x1E , 0x43 , 0x51 , 0x68};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 E2 00 20 75 58 11 02 53 23 90 1E 43 51 68 63 94
//const U8 g_szTag3[] =                   {0x10 , 0x05 , 0x00 , 0x23 , 0x00 , 0x00 , 0x20 , 0x14 , 0x05 , 0x10 , 0x04 , 0x65 , 0x8E , 0xFE};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 23 00 00 20 14 05 10 04 65 8E FE 63 94
//const U8 g_szTag4[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x27 , 0x43 , 0xAF , 0x37};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 27 43 AF 37 63 94
//const U8 g_szTag5[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x29 , 0x51 , 0xBE , 0x4B};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 29 51 BE 4B 63 94
//const U8 g_szTag6[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x24 , 0x56 , 0xB8 , 0xF0};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 24 56 B8 F0 63 94
//const U8 g_szTag7[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x28 , 0x87 , 0x26 , 0xC1};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 28 87 26 C1 63 94
//const U8 g_szTag8[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x15 , 0x14 , 0x11 , 0xB2 , 0x76};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 15 14 11 B2 76 63 94
//const U8 g_szTag9[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x23 , 0x70 , 0x65 , 0xC3};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 23 70 65 C3 63 94
//const U8 g_szTag10[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x77 , 0xBF , 0x82};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 25 77 BF 82 63 94
//const U8 g_szTag11[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x25 , 0x11 , 0xB3 , 0xE2};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 25 11 B3 E2 63 94
//const U8 g_szTag12[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x26 , 0x22 , 0xE0 , 0x81};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 26 22 E0 81 63 94
//const U8 g_szTag13[] =                   {0x10 , 0x05 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x15 , 0x01 , 0x14 , 0x23 , 0x78 , 0xE4 , 0xCB};//FF 18 22 00 00 10 00 1B 00 00 01 00 80 30 00 10 05 00 00 00 00 20 15 01 14 23 78 E4 CB 63 94

#define TAG_NUMBER  40
STATIC U32 xdata g_u32TagCrcData[TAG_NUMBER] = {0};
STATIC U8 xdata g_u8TagCount = 0;
U8 xdata g_u8TagOffset = 0;

CRfidVar xdata g_cRfidVar = {0};

STATIC U16 const crctable[] = 
{
    0x0000, 0x1021, 0x2042, 0x3063,
    0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b,
    0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
};

VOID GetCmdProc(U8 cCmdType, U8 *pData, U8 *pCount)
{
    switch(cCmdType)
    {
        case GETCURRENTPROGRAM:
            *pCount = sizeof(g_szGetCurrentProgram);
            memcpy(pData, g_szGetCurrentProgram, *pCount);
            break;
        case BOOTFIRMWARE:
            *pCount = sizeof(g_szBootFirmware);
            memcpy(pData, g_szBootFirmware, *pCount);
            break;
        case SETFREQUENCYCHANNEL:
            *pCount = sizeof(g_szSetFrequencyChannel);
            memcpy(pData, g_szSetFrequencyChannel, *pCount);
            break;
        case SETPROTOCOL:
            *pCount = sizeof(g_szSetProtocol);
            memcpy(pData, g_szSetProtocol, *pCount);
            break;
        case SETANTENNA:
            *pCount = sizeof(g_szSetAntenna);
            memcpy(pData, g_szSetAntenna, *pCount);
            break;
        case CLEARBUFFER:
            *pCount = sizeof(g_szClearBuffer);
            memcpy(pData, g_szClearBuffer, *pCount);
            break;
        case SEARCHTAG:
            *pCount = sizeof(g_szSearchTag);
            memcpy(pData, g_szSearchTag, *pCount);
            break;
        case GETTAGDATA:
            *pCount = sizeof(g_szGetTagdata);
            memcpy(pData, g_szGetTagdata, *pCount);
            break;
        case GETTAGDATAId:
            *pCount = sizeof(g_szGetTagIddata);
            memcpy(pData, g_szGetTagIddata, *pCount);
            break;
        case PRIMECONTINUEREADING:
            *pCount = sizeof(g_szPrimeContinueReading);
            memcpy(pData, g_szPrimeContinueReading, *pCount);
            break;
        case CONTINUEREADING:
            *pCount = sizeof(g_szContinueReading);
            memcpy(pData, g_szContinueReading, *pCount);
            break;
        case ENHANCEDISTANCE:
            *pCount = sizeof(g_szEnhanceDistance);
            memcpy(pData, g_szEnhanceDistance, *pCount);
            break;
        case ENHANCESPEED1:
            *pCount = sizeof(g_szEnhanceSpeed1);
            memcpy(pData, g_szEnhanceSpeed1, *pCount);
            break;
        case ENHANCESPEED2:
            *pCount = sizeof(g_szEnhanceSpeed2);
            memcpy(pData, g_szEnhanceSpeed2, *pCount);
            break;
        case ENHANCESPEED3:
            *pCount = sizeof(g_szEnhanceSpeed3);
            memcpy(pData, g_szEnhanceSpeed3, *pCount);
            break;
        case ENHANCESPEED4:
            *pCount = sizeof(g_szEnhanceSpeed4);
            memcpy(pData, g_szEnhanceSpeed4, *pCount);
            break;
        case ENHANCESPEED5:
            *pCount = sizeof(g_szEnhanceSpeed5);
            memcpy(pData, g_szEnhanceSpeed5, *pCount);
            break;
        case ENHANCESPEED6:
            *pCount = sizeof(g_szEnhanceSpeed6);
            memcpy(pData, g_szEnhanceSpeed6, *pCount);
            break;
        case CONTINUEREADINGEX:
            *pCount = sizeof(g_szContinueReadingEx);
            memcpy(pData, g_szContinueReadingEx, *pCount);
            break;
        case STOPREADING:
            *pCount = sizeof(g_szStopReading);
            memcpy(pData, g_szStopReading, *pCount);
            break;             
		case ONCEMODE:
            *pCount = sizeof(g_szOnceMode);
            memcpy(pData, g_szOnceMode, *pCount);
            break;            
        default :
            break;
    }
}



STATIC VOID ReadRfidStateProc(VOID)   
{
    if(READ_RFID_RESET())
    {
        g_cRfidVar.u8RfidState = BOOTLOADER_RUNNING;        
    }
    else
    {
        g_cRfidVar.u8RfidState = APPLICTATION_RUNNING;
    }
}    


BOOL CompareTag(U8 *pBuf)
{
    U8 xdata u8Count;
    BOOL xdata bRet = FALSE;

    for(u8Count = 0;u8Count < 17; u8Count++)
    {
        if(memcmp(g_szTag[u8Count], pBuf, 14) == 0)
        {
            g_cRfidVar.u8Tag = u8Count + 1;
            bRet = TRUE;
            break;
        }
    }
    return bRet;
}
U16 CalculateRfidCrc(U8 *u8Buf, U16 len)
{

    U16 xdata crc;
    int xdata i;

    crc = 0xffff;

    for (i = 0; i < len ; i++)
    {
        crc = ((crc << 4) | (u8Buf[i] >> 4))  ^ crctable[crc >> 12];
        crc = ((crc << 4) | (u8Buf[i] & 0xf)) ^ crctable[crc >> 12];
    }

    return crc;
}

U8 CalcCheckSum(U8* pSrcData, U16 wDataLen)
{
    U8 bCheckSum;
    int i;
    
    if(pSrcData == NULL)
        return 0;
    
    bCheckSum = pSrcData[0];

    if(wDataLen == 0xFFFF)
       return 0;
	   
    for(i = 1; i <= wDataLen - 1; i++)
    {
		pSrcData[i] = pSrcData[i] << 1 + i;
        bCheckSum ^= pSrcData[i]; 
    }
    return bCheckSum;    
}

U32 SoftGenCrc32(U32* puData, U32 uSize) 
{ 
	U32 xdata crc = 0xFFFFFFFF;
	U32 xdata i = 0, xdata j = 0, xdata temp; 
	for(i=0;i<uSize;i++)
	{ 
		temp = puData[i]; 
		for(j=0;j<32;j++)
		{ 
			if( (crc ^ temp) & 0x80000000 )
			{ 
				crc = 0x04C11DB7 ^ (crc<<1); 
			}
			else
			{ 
				crc <<=1; 
			} 
			temp<<=1; 
		} 
	}
	
	return crc; 
} 

//BOOL HandleTag(U8 *pBuf)
//{
//    BOOL bRet = FALSE;
//    U8 xdata u8Count;
////    U8 xdata u8Length;
//	U8 xdata u8Value;
//
////	u8Length = *(pBuf + 1);
//	u8Value = CalcCheckSum(pBuf+25, 4);
//    
//    bRet = TRUE;
//    for(u8Count = 0; u8Count < TAG_NUMBER; u8Count++)
//    {
//        if(u8Value == g_u8TagCrcData[u8Count])
//        {
//            g_u8TagOffset = u8Count;
//            goto CompareTagEx_exit;
//        }
//    }
//    g_u8TagOffset = g_u8TagCount;
//    g_u8TagCrcData[g_u8TagCount++] = u8Value; 
//    if(g_u8TagCount == TAG_NUMBER)
//    {
//        g_u8TagCount = 0;
//    }
//    
//CompareTagEx_exit:  
//    return bRet;
//}


// BOOL HandleTag(U8 *pBuf)
//{
//    BOOL bRet = FALSE;
//    U8 xdata u8Count;
//    U16 xdata u16Value;
//	U8 xdata 	szData[15];
////				MAKELONG(l, h)
////				MAKEWORD(l, h)
//    u16Value_l = MAKEWORD(pBuf+25, pBuf+26);
//	u16Value_h = MAKEWORD(pBuf+27, pBuf+28);
////    Uart1_Tx(pBuf+25, 4);
////	sprintf(szData, "###%x\r\n", u16Value);
////    Uart1_Tx_End(szData);
//    bRet = TRUE;
//    for(u8Count = 0; u8Count < TAG_NUMBER; u8Count++)
//    {
//        if(u16Value == g_u16TagCrcData[u8Count])
//        {
//            g_u8TagOffset = u8Count;
//            goto CompareTagEx_exit;
//        }
//    }
//    g_u8TagOffset = g_u8TagCount;
//    g_u16TagCrcData[g_u8TagCount++] = u16Value; 
//    if(g_u8TagCount == TAG_NUMBER)
//    {
//        g_u8TagCount = 0;
//    }
//   
//CompareTagEx_exit:  
//    return bRet;
//}

/////////////////////////rfid yuanlai start///////////////////////////////////////
//BOOL HandleTag(U8 *pBuf)
//{
//    BOOL bRet = FALSE;
//    U8 xdata u8Count;
//    U16 xdata u16Value_l, u16Value_h;
//	U32 xdata u32Value;
//	U8 xdata u8Value_l,u8Value_h;
//	u8Value_l =  *(pBuf+25);
//	u8Value_h =  *(pBuf+26);
//	u16Value_l = MAKEWORD(u8Value_l, u8Value_h);
//	u8Value_l =  *(pBuf+27);
//	u8Value_h =  *(pBuf+28);
//	u16Value_h = MAKEWORD(u8Value_l, u8Value_h);
//	u32Value = 	MAKELONG(u16Value_l, u16Value_h);
////    u16Value_l = MAKEWORD(pBuf+25, pBuf+26);
////	u16Value_h = MAKEWORD(pBuf+27, pBuf+28);
////	u32Value = 	MAKELONG(u16Value_l, u16Value_h);

//    bRet = TRUE;
//    for(u8Count = 0; u8Count < TAG_NUMBER; u8Count++)
//    {
//        if(u32Value == g_u32TagCrcData[u8Count])
//        {
//            g_u8TagOffset = u8Count;
//            goto CompareTagEx_exit;
//        }
//    }
//    g_u8TagOffset = g_u8TagCount;
//    g_u32TagCrcData[g_u8TagCount++] = u32Value; 
//    if(g_u8TagCount == TAG_NUMBER)
//    {
//        g_u8TagCount = 0;
//    }
//   
//CompareTagEx_exit:  
//    return bRet;
//}
/////////////////////rfid yuanlai end//////////////////////////////////////

BOOL HandleTag(U8 *pBuf)
{
    BOOL bRet = FALSE;
    U8 xdata u8Count;
	U32 xdata u32Value;
	
	U32 xdata szData[14] = {0};
	
	for(u8Count = 0; u8Count < 14; u8Count++)
	{
		szData[u8Count] = pBuf[u8Count];
	}

	u32Value = SoftGenCrc32(szData, 14);
    
    bRet = TRUE;
    for(u8Count = 0; u8Count < TAG_NUMBER; u8Count++)
    {
        if(u32Value == g_u32TagCrcData[u8Count])
        {
            g_u8TagOffset = u8Count;
            goto CompareTagEx_exit;
        }
    }
    g_u8TagOffset = g_u8TagCount;
    g_u32TagCrcData[g_u8TagCount++] = u32Value; 
    if(g_u8TagCount == TAG_NUMBER)
    {
        g_u8TagCount = 0;
    }
    
CompareTagEx_exit:  
    return bRet;
}
BOOL SendAndWaitRfidDataProc(U8 u8CmdType)
{

    BOOL xdata bRet = FALSE; 
    U8 xdata szData[RFIDDATACOUNT];
    U8 xdata u8Count = 0;
    U16 xdata u16Value, xdata u16Length;
    g_cRfidVar.u8CmdType = u8CmdType; 
    GetCmdProc(g_cRfidVar.u8CmdType, g_cRfidVar.szCmdSenddata, &(g_cRfidVar.u8SendCount));
    Uart2_Tx(g_cRfidVar.szCmdSenddata, g_cRfidVar.u8SendCount);

	while(1)
	{
		ReceiveUsart2Data(szData, &u16Length);

		if(u16Length)
		{
			break;
		}
	}
    g_cRfidVar.u8ReceiveCount =  u16Length;

	memcpy(g_cRfidVar.szReceivedata, szData, g_cRfidVar.u8ReceiveCount);
     
    u16Value = CalculateRfidCrc(g_cRfidVar.szReceivedata + 1, g_cRfidVar.u8ReceiveCount - 3);

    if(u16Value == MAKEWORD(g_cRfidVar.szReceivedata[g_cRfidVar.u8ReceiveCount - 1], g_cRfidVar.szReceivedata[g_cRfidVar.u8ReceiveCount - 2]))//数据接收正确
    {
        bRet = TRUE;
    }
    
    return bRet;
}


BOOL SendAndWaitRfidDataProcEnhance(U16 u16Data)
{
				
	U8 xdata szDebugData[7] = {0xFF, 0x02, 0x92, 0x0b, 0xb8};
    BOOL xdata bRet = FALSE; 
    U8 xdata szData[RFIDDATACOUNT];
    U8 xdata u8Count = 0;
    U16 xdata u16Value, xdata u16Length;
    
	szDebugData[3] = HIBYTE(u16Data);
	szDebugData[4] = LOBYTE(u16Data);
	u16Value = CalculateRfidCrc(szDebugData + 1, 4);
	szDebugData[5]	= HIBYTE(u16Value);
	szDebugData[6] = LOBYTE(u16Value);
    Uart2_Tx(szDebugData, 7);

	while(1)
	{
		ReceiveUsart2Data(szData, &u16Length);

		if(u16Length)
		{
			break;
		}
	}
    g_cRfidVar.u8ReceiveCount =  u16Length;

	memcpy(g_cRfidVar.szReceivedata, szData, g_cRfidVar.u8ReceiveCount);
     
    u16Value = CalculateRfidCrc(g_cRfidVar.szReceivedata + 1, g_cRfidVar.u8ReceiveCount - 3);

    if(u16Value == MAKEWORD(g_cRfidVar.szReceivedata[g_cRfidVar.u8ReceiveCount - 1], g_cRfidVar.szReceivedata[g_cRfidVar.u8ReceiveCount - 2]))//数据接收正确
    {
        bRet = TRUE;
    }
    
    return bRet;
}


VOID RfidInitProc(VOID)
{
    U32 xdata u32Tick;
    
    RFID_SHUTDOWN();
    
    DelayMs(650);
    
    RFID_UNSHUTDOWN();
    
//    u32Tick = GetTickCount();
//    
//    do
//    {
//        ReadRfidStateProc();
//        
//    }while((g_cRfidVar.u8RfidState == BOOTLOADER_RUNNING) && ((GetTickCount() - u32Tick) < 2000));
//    
//    if(g_cRfidVar.u8RfidState == BOOTLOADER_RUNNING)
//    {
//        EnterException(ERR_RFID_STEP_1);    
//    }
    
    
    u32Tick = GetTickCount();
    while((SendAndWaitRfidDataProc(GETCURRENTPROGRAM) == FALSE)  && ((GetTickCount() - u32Tick) < (U32)2000));//1.Get Current Program(0Ch)
    if((GetTickCount() - u32Tick) >= (U32)2000)
    {
        EnterException(ERR_RFID_STEP_2);    
    }

    if(g_cRfidVar.szReceivedata[4] & 0x01)//program & 0x1 == 1,则需要执行指令BOOTFIRMWARE,不需要判断返回，但应用起来需要650ms.
    {
        g_cRfidVar.u8CmdType = BOOTFIRMWARE; 
        GetCmdProc(g_cRfidVar.u8CmdType, g_cRfidVar.szCmdSenddata, &(g_cRfidVar.u8SendCount));
        Uart1_Tx(g_cRfidVar.szCmdSenddata, g_cRfidVar.u8SendCount);
        DelayMs(650);
    }

    u32Tick = GetTickCount();
    while((SendAndWaitRfidDataProc(SETFREQUENCYCHANNEL) == FALSE) && ((GetTickCount() - u32Tick) < (U32)2000));    //3.设置频段区域
    if((GetTickCount() - u32Tick) >= (U32)2000)
    {
        EnterException(ERR_RFID_STEP_3);    
    }

    u32Tick = GetTickCount();
    while((SendAndWaitRfidDataProc(SETPROTOCOL) == FALSE) && ((GetTickCount() - u32Tick) < (U32)2000));    //4.设置协议(93h)
    if((GetTickCount() - u32Tick) >= (U32)2000)
    {
        EnterException(ERR_RFID_STEP_4);    
    }

    u32Tick = GetTickCount();
    while((SendAndWaitRfidDataProc(SETANTENNA) == FALSE) && ((GetTickCount() - u32Tick) < (U32)2000));    //5.天线设置(91h)
    if((GetTickCount() - u32Tick) >= (U32)2000)
    {
        EnterException(ERR_RFID_STEP_5);    
    }

    u32Tick = GetTickCount();
    while((SendAndWaitRfidDataProc(CLEARBUFFER) == FALSE) && ((GetTickCount() - u32Tick) < (U32)2000));    //6.清除buffer(2Ah)
    if((GetTickCount() - u32Tick) >= (U32)2000)
    {
        EnterException(ERR_RFID_STEP_6);    
    }
    
}

