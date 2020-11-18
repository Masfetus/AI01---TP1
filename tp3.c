#include <stdlib.h>
#include <string.h>
#include "tp3.h"

void initialize (List **list)
{
    /* Simple initialisation de la liste, que l'on stocke directement dans la liste pass�e en param�tre*/
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    *list = newList;
}

void destruct(List** list)
{
    /* Pour chaque �l�ment de la liste, on va lib�rer la m�moire occup�e par l'�l�ment.
        Une fois tous les �l�ments lib�r�s, on peut lib�rer la m�moire occup�e par la liste elle-m�me*/
    if(list != NULL)
    {
        Element* ptTemp = (*list)->head;
        while(ptTemp != NULL) // Pour chaque �l�ment de la liste
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
    /*
        Insertion en fin de liste
        Si str pass� en param�tre contient plus de N digits, alors on va d�couper en nombre de digits <= N et rappeler la fonction pour chacun de ces nombres
        L'�l�ment s�parateur est mis s'il y a eu d�coupage de la cha�ne ou si le nombre � ins�rer avait un nombre de digits <= N


    */
    if(*list)
    {
        if(str && strlen(str) > N) // Pour chaque �l�ment faisant plus de 5 digits, on les d�compose puis on rappelle la fonction avec un str plus �l�mentaire
        {
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            while(ptList && *ptList) // Pour chaque maillon r�cup�r�
            {
                insert_end_list(list, *ptList, 1); // On ins�re l'�l�ment, faisant maintenant 5 digits ou moins
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else
        {
            Element *newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, (str ? str : "")); // El�m�nt s�parateur repr�sent� par une cha�ne vide dans la data
            newElement->next = NULL;
            (*list)->tail->next = newElement;
            (*list)->tail = newElement;
            if(!subString) // Si on appelle depuis l'ext�rieur la fonction et que le nombre ne n�cessite pas de d�coupage, alors on lui met directement l'�l�ment s�parateur apr�s
                insert_end_list(list, NULL, 1);
        }
    }
}

void insert_begining_list(List** list, char* str)
{
    /*
        Insertion en t�te de liste
        Le premier maillon de 5 digits r�cup�r� est ins�r� en t�te de liste
        Les autres (s'il y a) sont ins�r�s apr�s cette t�te de liste, d'o� la n�cessit� de garder l'�l�ment que l'on a ins�r� au d�but

    */
    if(*list && (*list)->head)
    {
        Element* newElement = (Element*) malloc(sizeof(Element)), *previousElement = NULL, * oldHead = (*list)->head;
        char** listOfNumbers = splitNumber(str), ** ptList = listOfNumbers;
        strcpy(newElement->data, *ptList);
        newElement->next = (*list)->head->next;
        previousElement = (*list)->head =  newElement; // Insertion du premier digit � la t�te de liste
        ptList++;
        while(ptList && *ptList) // Puis Insertion des groupes de 5 digits apr�s la t�te
        {
            newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, *ptList);
            previousElement->next = newElement; // On refixe les liens entre eux
            previousElement = newElement;
            ptList++;
        }
        newElement = (Element*) malloc(sizeof(Element));
        strcpy(newElement->data, ""); // Insertion �l�ment s�parateur � la fin
        newElement->next = oldHead;
        previousElement->next = newElement;
        free(listOfNumbers);
    }
}
void insert_empty_list(List** list, char* str, int subString)
{
    /*
        Insertion dans une liste vide
        Assez similaire � insert_end_list
        A ceci pr�s que l'�l�ment qui ne n�cessitera pas de division en maillon sera d�clar� comme t�te et queue de la liste
    */
    if(*list && !(*list)->head)
    {
        if(str && strlen(str) > N) // Si le nombre est plus grand que N, alors on effectue une d�composition
        {
            char** listOfNumbers = splitNumber(str), ** ptList = listOfNumbers;
            insert_empty_list(list, *ptList, 1); // On ins�re par empty le premier �l�ment
            ptList++;
            while(ptList && *ptList) // Puis il s'agira d'ins�rer les autres �l�ments � la fin de la liste
            {
                insert_end_list(list, *ptList, 1);
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else // S'il s'agit d'un nombre d�compos� ou inf�rieur � N, alors on peut commencer l'insertion
        {
            Element* newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, str);
            newElement->next = NULL;
            (*list)->tail = newElement;
            (*list)->head = newElement;
            if(!subString)
                insert_end_list(list, NULL, 1); // Insertion �l�ment s�parateur
        }
    }
}
int insert_after_position(List** list, char* str, int p)
{
    /*
        Insertion apr�s le p-�me nombre
        La fonction getElementAt r�cup�rera ici l'�l�ment � partir duquel nous devons ins�rer (en fonction de l'indice p pass�)
        A partir de cet �l�ment, on fait le m�me processus que pour insert_begining_list en ins�rant � la suite de cet �l�ment tous les maillons n�cessaires
    */
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
            strcpy(newElement->data, ""); // On ajoute l'�l�ment s�parateur entre deux maillons
            newElement->next = oldSucc;
            if(newElement->next == NULL) // Alors il s'agit de la t�te
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
    /*
        Suppression d'un �l�ment de la liste
        Ici on va une fois de plus r�cup�rer l'�l�ment � supprimer � partir de son indice, et supprimer en cha�ne les maillons qui le succ�dent jusqu'au prochain �l�ment

    */
    if(*list)
    {
        Element* firstElement = getElementAt(*list, (p > 0 ? p - 1 : p)); // On r�cup�re l'�l�ment apr�s le p-�me nombre ins�r�
        // On Commence � - 1 pour r�cup�rer le pr�d�cesseur et actualiser son next, s'il s'agit de la t�te de liste, inutile de commencer � - 1
        if(firstElement)
        {
            Element* ptElement = (p == 0 ? firstElement : firstElement->next); // On se repositionne au bon endroit pour d�buter la suppression
            Element* memElement = NULL;
            while(ptElement && strlen(ptElement)) // Tant que je n'ai pas atteint la case o� il y a aucune data (qui s�pare deux maillons)
            {
                memElement = ptElement->next;
                free(ptElement); // Je lib�re la m�moire
                ptElement = memElement;
            }
            memElement = ptElement->next;
            free(ptElement); // On lib�re l'�l�ment s�parateur aussi
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
    /*
        Comparaison de deux cha�nes de caract�res repr�sentant des nombres
        On exclut les cas triviaux si la longueur d'une cha�ne est sup�rieure � une autre.
        Sinon on compare les caract�res de chaque cha�ne un � un
    */
    int res = 0;
    if(strlen(str1) > strlen(str2))
        res = 1;
    else if(strlen(str2) > strlen(str1))
        res = 2;
    else
    {
        // Sinon ils ont la m�me taille et on va analyser chaque caract�re :
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
    // - 0 : Les deux nombres sont �gaux
    // - 1 : str1 > str2
    // - 2 : str2 > str1
    return res;
}
void sort_list(List** list)
{
    /*
        Tri de la liste
        Ce tri est bas� sur la recherche du minimum de la sous-liste que l'on ins�rera � la fin d'une nouvelle liste.
        Le minimum r�cup�r� de la liste initiale sera
    */
    List* res = NULL;
    if(*list && (*list)->head)
    {
        initialize(&res);
        while((*list)->head != NULL) // Tant qu'il reste des �l�ments dans la liste de d�part
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
            /* Pour le dernier �l�ment de la liste, il faut retester par rapport au minimum car l'�l�ment est null et n'entre pas une derni�re fois dans le while*/
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
            if(!res->head) // S'il n'y avait rien dans la liste on ins�re avec insert_empty sinon on ins�re � la fin
                insert_empty_list(&res, minimum, 0);
            else
                insert_end_list(&res, minimum, 0);
            remove_list(list, indexMinimum); // On retire le minimum trouv� de la sous-liste, pour �purer petit � petit cette liste
        }
        destruct(list); // On d�truit ce qu'il reste de la liste => rien donc complexit� 1 (vu qu'on a retir� tous les �l�ments un par un)
        *list = res; // On update le pointeur de la nouvelle liste tri�e
    }
}
void displayList(List* list)
{
    /*
        Affichage de la liste
        La liste est affich�e de la mani�re suivante :
        ----------------------------------------
        78 X 85964 5897 X 23 X 1 X
        ----------------------------------------

        X repr�sentant l'�l�ment s�parant deux nombres, l'espace s�pare deux maillons du nombre
    */
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
