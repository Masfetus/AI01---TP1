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
        while(ptTemp != NULL) // Pour chaque élément de la liste
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
        if(str && strlen(str) > N) // Pour chaque élément faisant plus de 5 digits, on les décompose puis on rappelle la fonction avec un str plus élémentaire
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
            if(!subString)
                insert_end_list(list, NULL, 1);
        }
    }
}

void insert_begining_list(List** list, char* str)
{
    if(*list && (*list)->head)
    {
        Element* newElement = (Element*) malloc(sizeof(Element)), *previousElement = NULL, * oldHead = (*list)->head;
        char** listOfNumbers = splitNumber(str), ** ptList = listOfNumbers;
        strcpy(newElement->data, *ptList);
        newElement->next = (*list)->head->next;
        previousElement = (*list)->head =  newElement; // Insertion du premier digit à la tête de liste
        ptList++;
        while(ptList && *ptList) // Puis Insertion des groupes de 5 digits après la tête
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
        if(str && strlen(str) > N) // Si le nombre est plus grand que N, alors on effectue une décomposition
        {
            char** listOfNumbers = splitNumber(str), ** ptList = listOfNumbers;
            insert_empty_list(list, *ptList, 1); // On insère par empty le premier élément
            ptList++;
            while(ptList && *ptList) // Puis il s'agira d'insérer les autres éléments à la fin de la liste
            {
                insert_end_list(list, *ptList, 1);
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else // S'il s'agit d'un nombre décomposé ou inférieur à N, alors on peut commencer l'insertion
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
        if(previousElement)
        {
            Element* oldSucc = previousElement->next;
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            while(ptList && *ptList) // Pour chaque groupe de 5 digits, on l'ajoute
            {
                newElement = (Element*) malloc(sizeof(Element));
                strcpy(newElement->data, *ptList);
                previousElement->next = newElement;
                previousElement = newElement;
                ptList++;
            }
            newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, ""); // On ajoute l'élément séparateur entre deux maillons
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

int remove_list(List** list, int p)
{
    if(*list)
    {
        Element* firstElement = getElementAt(*list, (p > 0 ? p - 1 : p)); // On récupère l'élément après le p-ème nombre inséré
        // On Commence à - 1 pour récupérer le prédécesseur et actualiser son next, s'il s'agit de la tête de liste, inutile de commencer à - 1
        if(firstElement)
        {
            Element* ptElement = (p == 0 ? firstElement : firstElement->next); // On se repositionne au bon endroit pour débuter la suppression
            Element* memElement = NULL;
            while(ptElement && strlen(ptElement)) // Tant que je n'ai pas atteint la case où il y a aucune data (qui sépare deux maillons)
            {
                memElement = ptElement->next;
                free(ptElement); // Je libère la mémoire
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
    // Retourne :
    // - 0 : Les deux nombres sont égaux
    // - 1 : str1 > str2
    // - 2 : str2 > str1
    return res;
}
void sort(List** list)
{
    List* res = NULL;
    if(*list && (*list)->head)
    {
        initialize(&res);
        while((*list)->head != NULL) // Tant qu'il reste des éléments dans la liste de départ
        {
            int position = 0, indexMinimum = 0;
            Element* element = (*list)->head;
            char string[64] = "", minimum[64] = "";
            while(element && element != (*list)->tail) // On va chercher le minimum de cette sous liste
            {
                if(strlen(element->data) > 0)
                    strcat(string, element->data);
                else
                {
                    if(strlen(minimum) > 0)
                    {
                        if(compare(minimum, string) == 1) // string plus petit que minimum alors minimum devient string
                        {
                            strcpy(minimum, string);
                            indexMinimum = position;
                        }
                    }
                    else
                        strcpy(minimum, string);
                    strcpy(string, "");
                    position ++;
                }
                element = element->next;
            }
            /* Pour le dernier élément de la liste, il faut retester par rapport au minimum car l'élément est null et n'entre pas une dernière fois dans le while*/
            if(strlen(minimum) > 0)
            {
                if(compare(minimum, string) == 1) // string plus petit que minimum alors minimum devient string
                {
                    strcpy(minimum, string);
                    indexMinimum = position;
                }
            }
            else
                strcpy(minimum, string);
            if(!res->head) // S'il n'y avait rien dans la liste on insère avec insert_empty sinon on insère à la fin
                insert_empty_list(&res, minimum, 0);
            else
                insert_end_list(&res, minimum, 0);
            remove_list(list, indexMinimum);
        }
        destruct(list);
        *list = res;
    }
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
