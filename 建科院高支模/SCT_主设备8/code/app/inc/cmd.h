#ifndef _CMD_H
#define _CMD_H




struct CmdType{
  char start;
  char device[8]; //¡°SCT16002¡±
  char cmd;
  char para[20];
  char end;
};

unsigned char cmdExtract(char *datstring, struct CmdType *cmdstructure);
void cmdProc(struct CmdType cmdstructure);
void cmdTask(void);

#endif  