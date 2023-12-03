//
// Created by loryi on 29/11/2023.
//

#ifndef EXCLUSIONPRECEDENCE_H
#define EXCLUSIONPRECEDENCE_H


// Structure pour stocker les contraintes d'exclusion
typedef struct {
    int exclusion[2];
} t_exclusion;

// Structure pour stocker les contraintes de précédence
typedef struct {
    int precedences[2];
} t_precedence;

// Structure pour stocker toutes les données
typedef struct {
    t_exclusion* exclusions;
    t_precedence* precedences;
    int nombre_operations;
    int nombre_exclusions;
    int nombre_precedences;
} t_donnees;

t_donnees lire_donnees();
void creer_graphe(t_donnees* donnees, int** graphe);
void dfs(int** graphe, int sommet, int* visite, int nombre_operations, int* stations, int station_actuelle);
void min_stations(t_donnees* donnees, int** graphe);
void exclprec();





#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONPRECEDENCE_H
