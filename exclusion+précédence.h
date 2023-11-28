//
// Created by loryi on 28/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSION_PRÉCÉDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSION_PRÉCÉDENCE_H
// Structure pour stocker les données d'une opération
typedef struct {
    int operation;
    int temps_execution;
} t_operation;

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
    t_operation* operations;
    int temps_cycle;
    int nombre_operations;
    int nombre_exclusions;
    int nombre_precedences;
} Donnees;

Donnees lire_donnees();
int couleur_presente(int* stations, int couleur, int nombre_operations);
int comparaison_precedence(const void* a, const void* b);
void trier_operations(Donnees* donnees, int* operations_triees);




#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSION_PRÉCÉDENCE_H
