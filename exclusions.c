#include <stdio.h>
#include <stdlib.h>
#include "exclusions.h"

void exclusion(Graphe* g){

    pSommet* psommet = (pSommet*)malloc(g->ordre*sizeof(pSommet));
    for(int i = 0; i<g->ordre;i++){
        psommet[i]=g->pSommet[i];
    }
    for (int i=0 ; i < g->ordre-1; i++){
        for (int j=0 ; j < g->ordre-i-1; j++){
            if (psommet[j]->degre < psommet[j+1]->degre) {
                pSommet tmp = psommet[j+1];
                psommet[j+1] = psommet[j];
                psommet[j] = tmp;
            }
        }
    }
    for(int i = 0;i<g->ordre;i++){
        printf("p %d\n",psommet[i]->valeur);
    }
    int couleur=1;
    int nb=0;
    while(nb<g->ordre){
        for(int i= 0; i<g->ordre;i++){
            if(psommet[i]->couleur!=0){
                continue;
            }
            while(psommet[i]->arc != NULL){
                if(g->pSommet[psommet[i]->arc->sommet]->couleur==couleur){
                    break;
                }
                if(psommet[i]->arc->arc_suivant==NULL){
                    psommet[i]->couleur=couleur;
                    nb++;
                }
                psommet[i]->arc=psommet[i]->arc->arc_suivant;
            }
        }
        couleur++;
    }
    

}
