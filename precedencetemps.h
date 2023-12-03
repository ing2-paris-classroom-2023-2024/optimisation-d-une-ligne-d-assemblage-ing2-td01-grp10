#ifndef PRECEDENCETEMPS_H
#define PRECEDENCETEMPS_H
#include "graphe.h"


typedef struct station{
    int* tab;
    int pos;
    float temps;
}Station;

Graphe * lire_graphe_oriente(char * nomFichier);

void enfiler(int* file1, int sommet);

int defiler(int* file,int taille);

void newStation(Station* station);

void precedencetemps(Graphe* g, float* temps, float limite);

void exec_prec();

pSommet* CreerArete_prec(pSommet* sommet,int s1,int s2);

Graphe* CreerGraphe_prec(int ordre);
#endif
