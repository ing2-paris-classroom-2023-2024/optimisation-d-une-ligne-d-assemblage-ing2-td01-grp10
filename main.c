#include <stdio.h>
#include <stdlib.h>
#include "exclusionprecedence.h"
#include "exclusions.h"


int main() {
    t_donnees donnees = lire_donnees();

    // Création du graphe
    int** graphe = (int**)malloc(sizeof(int*) * donnees.nombre_operations);
    for (int i = 0; i < donnees.nombre_operations; i++) {
        graphe[i] = (int*)malloc(sizeof(int) * donnees.nombre_operations);
    }

    creer_graphe(&donnees, graphe);

    // Minimiser le nombre de stations
    min_stations(&donnees, graphe);

    // Libération de la mémoire à la fin
    for (int i = 0; i < donnees.nombre_operations; i++) {
        free(graphe[i]);
    }
    free(graphe);

    free(donnees.exclusions);
    free(donnees.precedences);

    return 0;
}

