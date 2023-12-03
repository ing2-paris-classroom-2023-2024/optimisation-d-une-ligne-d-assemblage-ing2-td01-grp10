#include <stdio.h>
#include <stdlib.h>
#include "exclusions.h"

pSommet* CreerArete_excl(pSommet* sommet,int s1,int s2)
{
    sommet[s1]->degre++;
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }
    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->valeur=temp->valeur;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe_excl(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->couleur=0;
        Newgraphe->pSommet[i]->degre=0;
    }
    return Newgraphe;
}


/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
 */
Graphe * lire_graphe_non_oriente(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int orientation, taille;
    int ordre=0;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    taille=0;
    int s1,s2;
    
    while(fscanf(ifs,"%d %d",&s1,&s2)==2){
        taille++;
    }
    int** arcs = malloc(taille*sizeof(int*));
    fclose(ifs);
    FILE* f = fopen(nomFichier,"r");
    for(int i=0;i<taille;i++){
        fscanf(f,"%d %d",&s1,&s2);
        arcs[i]=malloc(2*sizeof(int));
        arcs[i][0]=s1-1;
        arcs[i][1]=s2-1;
        if(arcs[i][0] > ordre){
            ordre=arcs[i][0];
        }
        if(arcs[i][1] > ordre){
            ordre=arcs[i][1];
        }
    }
    ordre++;
    graphe=CreerGraphe_excl(ordre); // créer le graphe d'ordre sommets
    graphe->orientation=0;
    graphe->ordre=ordre;
    graphe->taille=taille;
    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    { 
        graphe->pSommet=CreerArete_excl(graphe->pSommet, arcs[i][0],arcs[i][1]);
        graphe->pSommet=CreerArete_excl(graphe->pSommet, arcs[i][1],arcs[i][0]);
    }

    return graphe;
}

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
    int couleur=1;
    int nb=0;
    while(nb<g->ordre){
        for(int i= 0; i<g->ordre;i++){
            if(psommet[i]->couleur!=0){
                continue;
            }
            if(psommet[i]->degre==0){
                nb++;
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
    for(int i = 1;i<couleur;i++){
        printf("Station %d : \n",i);
        for(int j=0;j<g->ordre;j++){
            if(g->pSommet[j]->degre!=0 && g->pSommet[j]->couleur==i){
                printf("Opération %d\n",j+1);
            }
        }
        printf("\n");
    }
}

 ///bon courage ma life ca va le faire t un prince!!!! dans 2 ans on sera faire
void exec_excl(){
    Graphe * g;
    char nom_fichier[50];
    printf("entrer le nom du fichier exclusions:");
    scanf("%s",nom_fichier);
    g = lire_graphe_non_oriente(nom_fichier);
    exclusion(g);
}