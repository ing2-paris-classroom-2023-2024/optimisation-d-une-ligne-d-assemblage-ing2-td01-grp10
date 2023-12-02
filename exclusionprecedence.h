//
// Created by loryi on 29/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONPRECEDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONPRECEDENCE_H


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




#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONPRECEDENCE_H
