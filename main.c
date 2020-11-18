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
    while(choice != 8) // Tant que l'utilisateur ne veut pas quitter
    {
        fflush(stdin); // Nettoyage du flux de donnée entrant
        if(!listTest) // Si la liste a été détruite (par l'utilisateur) on considère qu'elle n'occupe plus de place en mémoire, il faut donc relancer le programme pour la réinitialiser
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
                    case 7: // Destruction de la liste => on ne vide pas la liste en la détruisant ! On supprime son espace mémoire
                        destruct(&listTest);
                        listTest = NULL; break;
                    case 1: // Insertion au début de liste
                        inputValidNumber(userInput);
                        insert_begining_list(&listTest, userInput); break;
                    case 2: // Insertion en fin de liste
                        inputValidNumber(userInput);
                        insert_end_list(&listTest, userInput, 0); break;
                    case 3: // Insertion après une position spécifique
                        inputValidNumber(userInput);
                        inputValidNumber(index);
                        insert_after_position(&listTest, userInput, atoi(index)); break;
                    case 4: // Suppression d'un élément
                        inputValidNumber(index);
                        remove_list(&listTest, atoi(index)); break;
                    case 5: sort_list(&listTest); break; // Tri de la liste
                    case 6: displayList(listTest); break; // Affichage de la liste
                    default: printf("Pas encore implemente !\n"); break; // Si jamais un choix est entré et valide mais pas encore développé
                }
            }
        }
    }
    if(listTest) // Si la liste n'a pas encore été détruite, alors on libère la mémoire
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
    while(!isNumeric(inputDest)); // Tant que l'utilisateur ne rentre pas un nombre on lui demande d'en rentrer un
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
    while(*choice < 1 || *choice > 8); // Tant que le choix de l'utilisateur est différent de ceux présentés dans le menu, on redemande un choix
}
