#include <stdio.h>
#include <stdlib.h>
#include "exclusionprecedence.h"
#include "exclusions.h"
#include "precedencetemps.h"
#include "exclusiontemps.h"



int main() {

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
                exclprec();
                break;
            case 4:
                exec_excltps();
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

