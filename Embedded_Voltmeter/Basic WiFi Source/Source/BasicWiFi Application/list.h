

#ifndef __list_h__
#define __list_h__

#include "cc3000_common.h" // for time_t


#define N_READINGS 20


typedef struct _reading_pair{
	time_t time;
	int reading;
} READING_PAIR;


typedef struct _node {
	READING_PAIR data;
	void *previous;
	void *next;
} NODE;

void InitializeList();
NODE* NewNode();
void AppendNode(time_t new_time, int new_reading);
int FindNode(time_t wanted_time);
READING_PAIR GetDataFromTime(time_t time);
int RemoveTime(time_t dead_time);
void RemoveNode(NODE *dead_node);
int RemoveOldestNode();
void ResetCursor();
int CursorValid();
void CursorStepNext();
void CursorStepPrev();




#endif


