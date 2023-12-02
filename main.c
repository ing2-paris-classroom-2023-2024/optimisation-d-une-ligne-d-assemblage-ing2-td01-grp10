#include <stdio.h>
#include <stdlib.h>
#include "exclusionprecedence.h"
#include "exclusions.h"

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids)
{
    sommet[s1]->degre++;
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->valeur=poids;
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
        Newarc->valeur=poids;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->valeur=temp->valeur;
            temp->sommet=s2;
            temp->valeur=poids;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->couleur=0;
        Newgraphe->pSommet[i]->predecesseur=-1;
        Newgraphe->pSommet[i]->dist=-1;
        Newgraphe->pSommet[i]->degre=0;
    }
    return Newgraphe;
}


/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2,poids;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    fscanf(ifs,"%d",&taille);
    fscanf(ifs,"%d",&orientation);

    graphe->orientation=orientation;
    graphe->ordre=ordre;

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d%d",&s1,&s2,&poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, poids);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);
    }

    return graphe;
}

int main() {
    t_donnees donnees = lire_donnees();

    // Créer le graphe
    int** graphe = (int**)malloc(sizeof(int*) * donnees.nombre_operations);
    for (int i = 0; i < donnees.nombre_operations; i++) {
        graphe[i] = (int*)malloc(sizeof(int) * donnees.nombre_operations);
    }

    creer_graphe(&donnees, graphe);

    // Minimiser le nombre de stations
    minimiser_stations(&donnees, graphe);

    // Libération de la mémoire à la fin
    for (int i = 0; i < donnees.nombre_operations; i++) {
        free(graphe[i]);
    }
    free(graphe);

    free(donnees.exclusions);
    free(donnees.precedences);

    return 0;
}

