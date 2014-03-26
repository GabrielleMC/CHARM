
#include "buffer.h"

#pragma DATA_SECTION(readings, ".readings")
volatile READING_PAIR readings[N_READINGS];

#pragma DATA_SECTION(n_readings, ".n_readings")
volatile unsigned int n_readings = 0;

// always assume the buffer has oldest readings at front and newest at the end.

void AddReading(time_t new_time, int new_reading)
{
	if(n_readings == N_READINGS)
		RemoveOldestTime();
	readings[n_readings].time = new_time;
	readings[n_readings].reading = new_reading;
	n_readings++;
	SortReadings();
}

void SortReadings()
{
	int j, i;
	for(j = 0; j < n_readings; j++)
	{
		for(i = 0; i < (n_readings-1 - j); i++)
		{
			if(readings[i].time > readings[i+1].time)
			{
				READING_PAIR temp = readings[i];
				readings[i] = readings[i+1];
				readings[i+1] = temp;
			}
		}
	}
}

int FindTime(time_t wanted_time)
{
	int i;
	for(i = 0; i < n_readings; i++)
		if(readings[i].time == wanted_time)
			return i;
	return -1;
}

int RemoveTime(time_t dead_time)
{
	int index = FindTime(dead_time);
	if(index != -1)
	{
		while(index < n_readings-1)
		{
			readings[index] = readings[index+1];
			index++;
		}
		readings[index].time = -1;
		readings[index].reading = -1;
		n_readings--;
		SortReadings();
		return 0;
	}
	return 1;
}

READING_PAIR GetReading(int index)
{
	return readings[index];
}

int RemoveOldestTime()
{
	return RemoveTime(readings[0].time);
}
