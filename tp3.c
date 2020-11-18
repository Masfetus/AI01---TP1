#include <stdlib.h>
#include <string.h>
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
        while(ptTemp != NULL)
        {
            Element* nextElement = ptTemp->next;
            free(ptTemp);
            ptTemp = nextElement;
        }
        free(*list);
    }
}
void insert_end_list(List** list, char* str, int subString)
{
    if(*list)
    {
        printf("Trying to insert %s\n", str);
        if(str && strlen(str) > N)
        {
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            while(ptList && *ptList)
            {
                insert_end_list(list, *ptList, 1);
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else
        {
            Element *newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, (str ? str : ""));
            newElement->next = NULL;
            (*list)->tail->next = newElement;
            (*list)->tail = newElement;
            printf(" queue : %s |  tête : %s\n", (*list)->tail->data, (*list)->head->data);
            if(!subString)
                insert_end_list(list, NULL, 1);
        }
    }
}

void insert_begining_list(List** list, char* str)
{
    if(*list && (*list)->head)
    {
        Element* newElement = (Element*) malloc(sizeof(Element));
        Element* previousElement = NULL;
        Element* oldHead = (*list)->head;
        char** listOfNumbers = splitNumber(str);
        char** ptList = listOfNumbers;
        strcpy(newElement->data, *ptList);
        newElement->next = (*list)->head->next;
        previousElement = (*list)->head =  newElement;
        ptList++;
        while(ptList && *ptList)
        {
            newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, *ptList);
            previousElement->next = newElement;
            previousElement = newElement;
            ptList++;
        }
        newElement = (Element*) malloc(sizeof(Element));
        strcpy(newElement->data, "");
        newElement->next = oldHead;
        previousElement->next = newElement;
        free(listOfNumbers);
    }
}
void insert_empty_list(List** list, char* str, int subString)
{
    if(*list && !(*list)->head)
    {
        if(str && strlen(str) > N)
        {
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            insert_empty_list(list, *ptList, 1);
            ptList++;
            while(ptList && *ptList)
            {
                insert_end_list(list, *ptList, 1);
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else
        {
            Element* newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, str);
            newElement->next = NULL;
            (*list)->tail = newElement;
            (*list)->head = newElement;
            if(!subString)
                insert_end_list(list, NULL, 1);
        }
    }
}
int insert_after_position(List** list, char* str, int p)
{
    if(list)
    {
        Element* newElement = NULL;
        Element* previousElement = getElementAt(*list, p);
        printf("Data : %s\n", previousElement->next->data);
        if(previousElement)
        {
            Element* oldSucc = previousElement->next;
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            while(ptList && *ptList)
            {
                newElement = (Element*) malloc(sizeof(Element));
                strcpy(newElement->data, *ptList);
                previousElement->next = newElement;
                previousElement = newElement;
                ptList++;
            }
            newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, "");
            newElement->next = oldSucc;
            if(newElement->next == NULL) // Alors il s'agit de la tête
                (*list)->tail = newElement;
            previousElement->next = newElement;
            free(listOfNumbers);
            return 0;
        }
    }
    return -1;
}
Element* getElementAt(List* list, int index)
{
    Element* result = NULL;
    if(index >= 0 && list != NULL)
    {
        int i = -1;
        result = list->head;
        printf("Recherche : %d\n", index);
        while(index != i && result != NULL)
        {
            if(strlen(result->data) == 0)
            {
                i++;
                printf("Fin de l'elem n°%d\n", i);
            }
            if(i!=index)
                result = result->next;
        }
    }
    return result;
}
char** splitNumber(char* str)
{
    char** res = NULL;
    if(str != NULL && strlen(str) > 0)
    {
        int nbMaillons = (strlen(str) -1) / N + 1;
        char** ptMaillon = NULL;
        char* stringPart = str;
        ptMaillon = res = (char**) malloc(sizeof(char**) * (nbMaillons + 1)); // Nombre de maillons + élément NULL de la fin
        for(int i = 0; i < nbMaillons; i++, ptMaillon++)
        {
            *ptMaillon = (char*) malloc(sizeof(char) * (N+1));
            strncpy(*ptMaillon, stringPart, N);
            if(strlen(stringPart) > N)
                (*ptMaillon)[N] = '\0';
            stringPart += N;
        }
        *ptMaillon = NULL;
        ptMaillon = NULL;
    }
    return res;
}
int remove_list(List** list, int p)
{
    if(*list)
    {
        Element* firstElement = getElementAt(*list, (p > 0 ? p - 1 : p));
        if(firstElement)
        {
            Element* ptElement = (p == 0 ? firstElement : firstElement->next);
            Element* memElement = NULL;
            while(ptElement && strlen(ptElement))
            {
                memElement = ptElement->next;
                free(ptElement);
                ptElement = memElement;
            }
            memElement = ptElement->next;
            free(ptElement);
            ptElement = memElement;
            if(p == 0)
                (*list)->head = ptElement;
            else
            {
                firstElement->next = ptElement;
                if(ptElement == NULL)
                    (*list)->tail = firstElement;
            }
            return 0;
        }
    }
    return -1;
}
int compare(char* str1, char* str2)
{
    int res = 0;
    if(strlen(str1) > strlen(str2))
        res = 1;
    else if(strlen(str2) > strlen(str1))
        res = 2;
    else
    {
        // Sinon ils ont la même taille et on va analyser chaque caractère :
        while(*str1 != '\0' && *str2 != '\0' && !res)
        {
            if(*str1 > *str2)
                res = 1;
            else if(*str2 > *str1)
                res = 2;
            str1++;
            str2++;
        }
    }
    return res;
}
void displayList(List* list)
{
    if(list != NULL && list->head != NULL)
    {
        Element* element = list->head;
        printf("Liste :\n--------------------------------------------------\n");
        while(element != NULL)
        {
            if(strlen(element->data))
                printf("%s ", element->data);
            else
                printf("X ");
            element = element->next;
        }
        printf("\n--------------------------------------------------\n");
    }
    else
        printf("EMPTY LIST !\n");
}
