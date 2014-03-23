
#include "list.h"

void InitializeList() {
	CURSOR = NULL;
	FIRST = NULL;
	LAST = NULL;
	list_size = 0;
}

void AppendNode(READING_PAIR new_data)
{
	NODE *new_node = malloc(sizeof(NODE));
	new_node->data.time = new_data.time;
	new_node->data.reading = new_data.reading;

	if(FIRST == NULL)
	{
		new_node->previous = NULL;
		FIRST = new_node;
	}
	else
	{
		new_node->previous = LAST;
	}

	new_node->next = NULL;
	LAST = new_node;
	list_size++;
}

int FindNode(time_t wanted_time)
{
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
	if(list_size > 2)
	{
		if(dead_node == LAST) // last node
		{
			NODE *TEMP = dead_node->previous;
			TEMP->next = NULL;
			LAST = LAST->previous;
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
	free(dead_node);

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

