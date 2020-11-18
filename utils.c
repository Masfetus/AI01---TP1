#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "tp3.h"

Element* getElementAt(List* list, int index)
{
    /*
        Recherche de l'élément à la position index
        On va parcourir toute la liste à la recherche de l'élément à la fin du "index"-ème nombre
    */
    Element* result = NULL;
    if(index >= 0 && list != NULL)
    {
        int i = -1;
        result = list->head;
        while(index != i && result != NULL) // Si on atteint l'indice ou qu'il n'y a plus rien dans la liste à analyser
        {
            if(strlen(result->data) == 0) // On augmente l'indice que si on est passé à un nouveau nombre (que donc on a atterri sur l'élément séparateur)
            {
                i++;
            }
            if(i!=index) // On passe au suivant si on a pas atteint l'objectif
                result = result->next;
        }
    }
    return result; // On retourne ici l'élément séparateur après le index-ème nombre inséré dans la liste (et non pas l'élément à l'indice index)
}
int isNumeric (const char * s) // Détermine si la chaîne de caractères comporte uniquement des nombres ou non
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
char** splitNumber(char* str)
{
    /*
        Découpage d'une chaîne de caractères en chaîne de N digits maximum
        Libération de la mémoire occupée par le résultat nécessaire !! (free (splitNumber)))
        Ici, on utilisera la fonction native de string.h : strncpy pour prendre les 5 prochains caractères puis on se déplacera de 5 caractères pour reexécuter cette fonction
    */

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
                (*ptMaillon)[N] = '\0'; // Insertion du caractère nul, pas systématique avec strncpy
            stringPart += N; // On skip les N caractères copiés
        }
        *ptMaillon = NULL;
        ptMaillon = NULL; // Elément neutre pour dire qu'il n'y a plus rien (pour éviter de déborder)
    }
    return res;
}
