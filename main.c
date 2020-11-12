#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main()
{
    List* listTest;
    initialize(&listTest);
    printf("Adresse liste : %x\n", listTest);
    printf("Head : %x | Tail : %x\n", listTest->head, listTest->tail);
    destruct(&listTest);
    printf("Adresse liste : %d\n", listTest);
    return 0;
}

