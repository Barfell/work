1、拨码开关0是指靠近on那边。
使用串口调试的时候拨码开关要拨到：1->on,2->off
使用TestStim300Proc时开关拨到:1-->off,2-->on也就是10
使用TestStim300StorageProc时开关拨到：1-->off,2-->on
2、
flash使用的是MT29F2G08ABAEA  2Gb = 256 MBYTE
1block = 64page
2048block = 2plane * 1024
2048+64

ID = 0x2cda909506
表示支持cache编程，2plane， 64字节spare区，2048/页，128k/块，没有内部ecc

NANDFLASH 测试指令:
//开始测试 (前面三个字节是命令，第四个字节是写的数据，这里写0x32)
//读
01 01 EF 30 00 10 00
//写
01 02 EF 33 00 00 04
//擦除
01 03 EF 38 00 10 00
//擦除全部
01 04 EF 38 00 10 00
//写全部
01 05 EF 38 00 00 00
//读全部
01 06 EF 38 00 01 00

//读spare
01 07 EF 38 00 00 04
//写spare
01 08 EF 42 00 00 04
//测试坏块（格式化）
01 09 EF 61 00 00 00
//测试坏块（new chip）
01 0a EF 00 00 00 00

3、

