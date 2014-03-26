
#ifndef __COMS_H__
#define __COMS_H__

#include "buffer.h"



void FakeList();
int LowBattery();
int CreateReadingsRaw(char *buf, int size);
int ProcessConfirmRaw(char *buf, int size);

#endif
