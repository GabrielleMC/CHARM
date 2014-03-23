

#ifndef __list_h__
#define __list_h__

#include "coms.h" // for reading_pair
#include "cc3000_common.h" // for time_t

typedef struct _node {
	READING_PAIR data;
	void *previous;
	void *next;
} NODE;

NODE *CURSOR;
NODE *FIRST;
NODE *LAST;
unsigned int list_size;

void InitializeList();
void AppendNode(READING_PAIR new_data);
int FindNode(time_t wanted_time);
READING_PAIR GetDataFromTime(time_t time);
int RemoveTime(time_t dead_time);
void RemoveNode(NODE *dead_node);
void ResetCursor();
int CursorValid();
void CursorStepNext();
void CursorStepPrev();




#endif


