#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "tp3.h"
Element* getElementAt(List* liste, int index); // R�cup�re l'�l�ment (s�parateur) apr�s le index-�me nombre ins�r�, pour acc�der � l'�l�ment juste apr�s : (element->next)
char** splitNumber(char* str); // D�coupe une cha�ne de caract�res en sous-cha�ne de caract�res de N digits
int isNumeric (const char * s); // Retourne 1 si la cha�ne de caract�res repr�sente un nombre, sinon 0

#endif // UTILS_H_INCLUDED
