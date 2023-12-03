#ifndef EXCLUSIONS_H_INCLUDED
#define EXCLUSIONS_H_INCLUDED
#include "graphe.h"

void exclusion(Graphe* g);

Graphe * lire_graphe_non_oriente(char * nomFichier);

void exec_excl();

pSommet* CreerArete_excl(pSommet* sommet,int s1,int s2);

Graphe* CreerGraphe_excl(int ordre);
#endif