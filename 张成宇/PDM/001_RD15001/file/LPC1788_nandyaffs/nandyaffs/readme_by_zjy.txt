20121118
嘟一声写一个sector，调用f_mks()，嘟嘟想个不停，说明在操作。就是太慢了。

写两个扇区，读两个扇区。都能够正常实现，而且调用的是disk_read和disk_write函数。

startup_LPC177X_8x.s文件修改，否则malloc分配不出空间。
;edit by zhangjy,old value is 0x00000800
Stack_Size      EQU     0x00008000
;edit by zhangjy,old value is 0x00000400
Heap_Size       EQU     0x00004000