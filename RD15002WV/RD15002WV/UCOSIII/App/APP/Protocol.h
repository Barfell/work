#ifndef _PROTOCOL_H
#define _PROTOCOL_H

struct UploadType{
	unsigned char guide[2];
	unsigned char length[4];
	unsigned char head[5];
	unsigned char totalpacketnum[4];
	unsigned char currentpacketnum[4];
	unsigned char packetdata[4096];
	unsigned char crc[4];
	unsigned char end[2];
};
void DecodeData(unsigned char *p);
#endif

