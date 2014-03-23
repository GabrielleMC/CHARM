
#ifndef __COMS_H__
#define __COMS_H__

#include "cc3000_common.h" // for time_t

#define N_READINGS 20


typedef struct _reading_pair{
	time_t time;
	int reading;
} READING_PAIR;



#endif
