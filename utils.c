#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "tp3.h"

Element* getElementAt(List* list, int index)
{
    Element* result = NULL;
    if(index >= 0 && list != NULL)
    {
        int i = -1;
        result = list->head;
        while(index != i && result != NULL)
        {
            if(strlen(result->data) == 0)
            {
                i++;
            }
            if(i!=index)
                result = result->next;
        }
    }
    return result; // On retourne ici l'�l�ment s�parateur apr�s le index-�me nombre ins�r� dans la liste (et non pas l'�l�ment � l'indice index)
}
int isNumeric (const char * s) // D�termine si la cha�ne de caract�res comporte uniquement des nombres ou non
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
char** splitNumber(char* str)
{
    char** res = NULL;
    if(str != NULL && strlen(str) > 0)
    {
        int nbMaillons = (strlen(str) -1) / N + 1;
        char** ptMaillon = NULL;
        char* stringPart = str;
        ptMaillon = res = (char**) malloc(sizeof(char**) * (nbMaillons + 1)); // Nombre de maillons + �l�ment NULL de la fin
        for(int i = 0; i < nbMaillons; i++, ptMaillon++)
        {
            *ptMaillon = (char*) malloc(sizeof(char) * (N+1));
            strncpy(*ptMaillon, stringPart, N);
            if(strlen(stringPart) > N)
                (*ptMaillon)[N] = '\0'; // Insertion du caract�re nul, pas syst�matique avec strncpy
            stringPart += N; // On skip les N caract�res copi�s
        }
        *ptMaillon = NULL;
        ptMaillon = NULL; // El�ment neutre pour dire qu'il n'y a plus rien (pour �viter de d�border)
    }
    return res;
}
