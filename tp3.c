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
void insert_end_list(List** list, char* str)
{
    if(*list && (*list)->tail)
    {
        Element *newElement = (Element*) malloc(sizeof(Element));
        newElement->data = str;
        newElement->next = NULL;
        (*list)->tail = newElement;
    }
}
void insert_after_position(List** list, char* str, int p)
{
    if(list && (*list)->tail)
    {
        int i = 0;
        Element* newElement = (Element*) malloc(sizeof(Element));
        newElement = str;
        // à finir
    }
}
