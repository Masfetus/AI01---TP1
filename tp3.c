#include <stdlib.h>
#include "tp3.h"

void initialize (List **list)
{
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    *list = newList;
}

void destruct(List** list)
{
    if(list != NULL)
    {
        Element* ptTemp = (*list)->head;
        if(ptTemp != NULL)
        {
            do
            {
                Element* nextElement = ptTemp->next;
                free(ptTemp);
                ptTemp = nextElement;
            }
            while(ptTemp != (*list)->tail);
        }
        free(*list);
    }
}
