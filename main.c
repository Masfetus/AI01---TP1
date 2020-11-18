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
        fflush(stdin); // Nettoyage du flux de donn�e entrant
        if(!listTest) // Si la liste a �t� d�truite (par l'utilisateur) on consid�re qu'elle n'occupe plus de place en m�moire, il faut donc relancer le programme pour la r�initialiser
        {
            printf("|- La liste a ete detruite, fermeture du programme...\n");
            choice = 8;
        }
        else
        {
            char userInput[64];
            if(listTest->head == NULL) // La liste est vide alors on demande comment initialiser le premier �l�ment
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
                    case 7: // Destruction de la liste => on ne vide pas la liste en la d�truisant ! On supprime son espace m�moire
                        destruct(&listTest);
                        listTest = NULL; break;
                    case 1: // Insertion au d�but de liste
                        inputValidNumber(userInput);
                        insert_begining_list(&listTest, userInput); break;
                    case 2: // Insertion en fin de liste
                        inputValidNumber(userInput);
                        insert_end_list(&listTest, userInput, 0); break;
                    case 3: // Insertion apr�s une position sp�cifique
                        inputValidNumber(userInput);
                        inputValidNumber(index);
                        insert_after_position(&listTest, userInput, atoi(index)); break;
                    case 4: // Suppression d'un �l�ment
                        inputValidNumber(index);
                        remove_list(&listTest, atoi(index)); break;
                    case 5: sort_list(&listTest); break; // Tri de la liste
                    case 6: displayList(listTest); break; // Affichage de la liste
                    default: printf("Pas encore implemente !\n"); break; // Si jamais un choix est entr� et valide mais pas encore d�velopp�
                }
            }
        }
    }
    if(listTest) // Si la liste n'a pas encore �t� d�truite, alors on lib�re la m�moire
        destruct(&listTest);
    return 0;
}
//********************************************************************************************************//
//------------------------ Fonctions de gestion des entr�es/sorties utilisateur --------------------------//
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
           7 - D�truire la liste\n\
           8 - Quitter\n------------------------------------------------\n");
       scanf("%d", choice);
    }
    while(*choice < 1 || *choice > 8); // Tant que le choix de l'utilisateur est diff�rent de ceux pr�sent�s dans le menu, on redemande un choix
}
