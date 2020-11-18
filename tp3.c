#include <stdlib.h>
#include <string.h>
#include "tp3.h"

void initialize (List **list)
{
    /* Simple initialisation de la liste, que l'on stocke directement dans la liste passée en paramètre*/
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    *list = newList;
}

void destruct(List** list)
{
    /* Pour chaque élément de la liste, on va libérer la mémoire occupée par l'élément.
        Une fois tous les éléments libérés, on peut libérer la mémoire occupée par la liste elle-même*/
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
    /*
        Insertion en fin de liste
        Si str passé en paramètre contient plus de N digits, alors on va découper en nombre de digits <= N et rappeler la fonction pour chacun de ces nombres
        L'élément séparateur est mis s'il y a eu découpage de la chaîne ou si le nombre à insérer avait un nombre de digits <= N


    */
    if(*list)
    {
        if(str && strlen(str) > N) // Pour chaque élément faisant plus de 5 digits, on les décompose puis on rappelle la fonction avec un str plus élémentaire
        {
            char** listOfNumbers = splitNumber(str);
            char** ptList = listOfNumbers;
            while(ptList && *ptList) // Pour chaque maillon récupéré
            {
                insert_end_list(list, *ptList, 1); // On insère l'élément, faisant maintenant 5 digits ou moins
                ptList++;
            }
            insert_end_list(list, NULL, 1);
            free(listOfNumbers);
        }
        else
        {
            Element *newElement = (Element*) malloc(sizeof(Element));
            strcpy(newElement->data, (str ? str : "")); // Elémént séparateur représenté par une chaîne vide dans la data
            newElement->next = NULL;
            (*list)->tail->next = newElement;
            (*list)->tail = newElement;
            if(!subString) // Si on appelle depuis l'extérieur la fonction et que le nombre ne nécessite pas de découpage, alors on lui met directement l'élément séparateur après
                insert_end_list(list, NULL, 1);
        }
    }
}

void insert_begining_list(List** list, char* str)
{
    /*
        Insertion en tête de liste
        Le premier maillon de 5 digits récupéré est inséré en tête de liste
        Les autres (s'il y a) sont insérés après cette tête de liste, d'où la nécessité de garder l'élément que l'on a inséré au début

    */
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
            previousElement->next = newElement; // On refixe les liens entre eux
            previousElement = newElement;
            ptList++;
        }
        newElement = (Element*) malloc(sizeof(Element));
        strcpy(newElement->data, ""); // Insertion élément séparateur à la fin
        newElement->next = oldHead;
        previousElement->next = newElement;
        free(listOfNumbers);
    }
}
void insert_empty_list(List** list, char* str, int subString)
{
    /*
        Insertion dans une liste vide
        Assez similaire à insert_end_list
        A ceci près que l'élément qui ne nécessitera pas de division en maillon sera déclaré comme tête et queue de la liste
    */
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
                insert_end_list(list, NULL, 1); // Insertion élément séparateur
        }
    }
}
int insert_after_position(List** list, char* str, int p)
{
    /*
        Insertion après le p-ème nombre
        La fonction getElementAt récupèrera ici l'élément à partir duquel nous devons insérer (en fonction de l'indice p passé)
        A partir de cet élément, on fait le même processus que pour insert_begining_list en insérant à la suite de cet élément tous les maillons nécessaires
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
    /*
        Suppression d'un élément de la liste
        Ici on va une fois de plus récupérer l'élément à supprimer à partir de son indice, et supprimer en chaîne les maillons qui le succèdent jusqu'au prochain élément

    */
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
            free(ptElement); // On libère l'élément séparateur aussi
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
        Comparaison de deux chaînes de caractères représentant des nombres
        On exclut les cas triviaux si la longueur d'une chaîne est supérieure à une autre.
        Sinon on compare les caractères de chaque chaîne un à un
    */
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
void sort_list(List** list)
{
    /*
        Tri de la liste
        Ce tri est basé sur la recherche du minimum de la sous-liste que l'on insèrera à la fin d'une nouvelle liste.
        Le minimum récupéré de la liste initiale sera
    */
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
            remove_list(list, indexMinimum); // On retire le minimum trouvé de la sous-liste, pour épurer petit à petit cette liste
        }
        destruct(list); // On détruit ce qu'il reste de la liste => rien donc complexité 1 (vu qu'on a retiré tous les éléments un par un)
        *list = res; // On update le pointeur de la nouvelle liste triée
    }
}
void displayList(List* list)
{
    /*
        Affichage de la liste
        La liste est affichée de la manière suivante :
        ----------------------------------------
        78 X 85964 5897 X 23 X 1 X
        ----------------------------------------

        X représentant l'élément séparant deux nombres, l'espace sépare deux maillons du nombre
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
