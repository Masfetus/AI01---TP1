#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tp3.h"
#include "utils.h"

int main()
{
    int choice = 0;
    List* listTest = NULL;
    initialize(&listTest);
    while(choice != 8)
    {
        fflush(stdin);
        if(!listTest)
        {
            printf("|- La liste a ete detruite, fermeture du programme...\n");
            choice = 8;
        }
        else
        {
            char userInput[64];
            if(listTest->head == NULL) // La liste est vide alors on demande comment initialiser le premier élément
            {
                printf("|- La liste est vide, ajoutez un nombre : -|\n");
                inputValidNumber(userInput);

                insert_empty_list(&listTest, userInput, 0);
            }
            else
            {
                char index[4];
                displayList(listTest);
                showMenu(&choice);
                switch(choice)
                {
                    case 7:
                        destruct(&listTest);
                        listTest = NULL; break;
                    case 1:
                        inputValidNumber(userInput);
                        insert_begining_list(&listTest, userInput); break;
                    case 2:
                        inputValidNumber(userInput);
                        insert_end_list(&listTest, userInput, 0); break;
                    case 3:
                        inputValidNumber(userInput);
                        inputValidNumber(index);
                        insert_after_position(&listTest, userInput, atoi(index)); break;
                    case 4:
                        inputValidNumber(index);
                        remove_list(&listTest, atoi(index)); break;
                    case 5: sort(&listTest); break;
                    case 6: displayList(listTest); break;
                    default: printf("Pas encore implemente !\n"); break;
                }
            }
        }
    }
    if(listTest)
        destruct(&listTest);
    return 0;
}
//********************************************************************************************************//
//------------------------ Fonctions de gestion des entrées/sorties utilisateur --------------------------//
//********************************************************************************************************//
void inputValidNumber(char* inputDest)
{
    *inputDest = "";
    do
    {
        printf("|- Saisissez un nombre : -|\n");
        scanf("%s", inputDest);
    }
    while(!isNumeric(inputDest));
}

void showMenu(int* choice)
{
    int res = 0;
    do
    {
        printf("\n|- Manipulation de la liste :\n\------------------------------------------------\n\
           1 - Ajouter un nombre en debut de liste\n\
           2 - Ajouter un nombre en fin de liste\n\
           3 - Ajouter un nombre a une certaine position\n\
           4 - Supprimer un nombre d'une certaine position\n\
           5 - Trier la liste par ordre croissant\n\
           6 - Afficher la liste\n\
           7 - Détruire la liste\n\
           8 - Quitter\n------------------------------------------------\n");
       scanf("%d", choice);
    }
    while(*choice < 1 || *choice > 8);
}
