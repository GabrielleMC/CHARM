

#ifndef __buffer_h__
#define __buffer_h__

#include "cc3000_common.h" // for time_t


#define N_READINGS 5


typedef struct _reading_pair{
	time_t time;
	int reading;
} READING_PAIR;

void AddReading(time_t new_time, int new_reading);
void SortReadings();
int FindTime(time_t wanted_time);
READING_PAIR GetReading(int index);
int RemoveTime(time_t dead_time);
int RemoveOldestTime();





#endif


