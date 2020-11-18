#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "tp3.h"
Element* getElementAt(List* liste, int index); // Récupère l'élément (séparateur) après le index-ème nombre inséré, pour accéder à l'élément juste après : (element->next)
char** splitNumber(char* str); // Découpe une chaîne de caractères en sous-chaîne de caractères de N digits
int isNumeric (const char * s); // Retourne 1 si la chaîne de caractères représente un nombre, sinon 0

#endif // UTILS_H_INCLUDED
