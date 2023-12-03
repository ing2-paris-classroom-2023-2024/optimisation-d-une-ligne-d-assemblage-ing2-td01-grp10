#include <stdio.h>
#include <stdlib.h>
#include "exclusionprecedence.h"
#include "exclusions.h"
#include "precedencetemps.h"



int main() {
    // t_donnees donnees = lire_donnees();

    // // Création du graphe
    // int** graphe = (int**)malloc(sizeof(int*) * donnees.nombre_operations);
    // for (int i = 0; i < donnees.nombre_operations; i++) {
    //     graphe[i] = (int*)malloc(sizeof(int) * donnees.nombre_operations);
    // }

    // creer_graphe(&donnees, graphe);

    // // Minimiser le nombre de stations
    // min_stations(&donnees, graphe);

    // // Libération de la mémoire à la fin
    // for (int i = 0; i < donnees.nombre_operations; i++) {
    //     free(graphe[i]);
    // }
    // free(graphe);

    // free(donnees.exclusions);
    // free(donnees.precedences);

    int n;

    while(1){
        printf("---------MENU---------\n");
        printf("1) Exclusions\n");
        printf("2) precendence + temps\n");
        printf("3) exclusion + precedence\n");
        printf("4) exclusion + temps\n");
        printf("5) Exit\n");

        printf("\n\nVeuillez entrer votre choix : ");
        scanf("%d",&n);
        switch(n){
            case 1:
                exec_excl();
                break;
            case 2:
                exec_prec();
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                return 0;
                break;
            default:
                printf("Veuillez entrer un chiffre compris entre 1 et 5\n");
                break;
        }
    }

    return 0;
}

