
#include "list.h"


NODE *CURSOR;
NODE *FIRST;
NODE *LAST;
unsigned int list_size;

void InitializeList() {
	CURSOR = NULL;
	FIRST = NULL;
	LAST = NULL;
	list_size = 0;
}

NODE* NewNode()
{
	READING_PAIR *new_data = malloc(sizeof(READING_PAIR));
	NODE *new_node = (NODE *) malloc(sizeof(NODE));
	if(!new_data || ! new_node)
		return NULL;
	new_node->data = *new_data;
	new_data->reading = 0;
	new_data->time = 0;
	return new_node;
}

void AppendNode(time_t new_time, int new_reading)
{

	NODE *new_node = NewNode();
	while(new_node == NULL) // can enter infinite loop due if memory leak
		RemoveOldestNode();
	new_node->data.time = new_time;
	new_node->data.reading = new_reading;

	if(FIRST == NULL)
	{
		new_node->previous = NULL;
		FIRST = new_node;
	}
	else
	{
		new_node->previous = LAST;
		NODE *TEMP = new_node->previous;
		TEMP->next = new_node;
	}
	new_node->next = NULL;
	LAST = new_node;
	list_size++;
}

int FindNode(time_t wanted_time)
{
	ResetCursor();
	while(CursorValid())
	{
		if(CURSOR->data.time == wanted_time)
			return 1;
		CursorStepNext();
	}
	return 0;
}

READING_PAIR GetDataFromTime(time_t time)
{
	if(FindNode(time))
		return CURSOR->data;
	CURSOR = NULL;
	return CURSOR->data;
}

int RemoveTime(time_t dead_time)
{
	if(FindNode(dead_time))
	{
		RemoveNode(CURSOR);
		return 1;
	}
	return 0;
}

void RemoveNode(NODE *dead_node)
{
	if(list_size > 1)
	{
		if(dead_node == LAST) // last node
		{
			NODE *TEMP = dead_node->previous;
			TEMP->next = NULL;
			LAST = TEMP;
		} else if(dead_node == FIRST) { // first node
			NODE *TEMP = dead_node->next;
			TEMP->previous = NULL;
			FIRST = FIRST->next;
		} else { // middle node
			NODE *TEMP = dead_node->previous;
			TEMP->next = dead_node->next;
			TEMP = dead_node->next;
			TEMP->previous = dead_node->previous;
		}
	} else { // only node in list
		FIRST = NULL;
		LAST = NULL;
	}
	list_size--;
	if(&dead_node->data.reading) free (&dead_node->data.reading);
	if(&dead_node->data.time) free (&dead_node->data.time);
	free(dead_node);

}

int RemoveOldestNode()
{
	if(list_size == 0)
		return 0;
	ResetCursor();
	time_t temp = CURSOR->data.time;
	while(CursorValid())
	{
		if(CURSOR->data.time < temp)
			temp = CURSOR->data.time;
		CursorStepNext();
	}
	return RemoveTime(temp);
}

int CursorValid()
{
	if(CURSOR == NULL)
		return 0;
	return 1;
}

void ResetCursor()
{
	CURSOR = FIRST;
}

void CursorStepNext()
{
	CURSOR = CURSOR->next;
}


void CursorStepPrev()
{
	CURSOR = CURSOR->previous;
}

