//
// Created by loryi on 28/11/2023.
//

#include "exclusion+précédence.h"
// lecture d'un fichier

#include <stdio.h>
#include <stdlib.h>

// Fonction pour lire les données depuis les fichiers
Donnees lire_donnees() {
    Donnees donnees;

    // Lecture du fichier exclusions.txt
    FILE *file = fopen("exclusions.txt", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier exclusions.txt");
        exit(EXIT_FAILURE);
    }

    // Allocation dynamique pour les exclusions
    donnees.exclusions = NULL;
    donnees.nombre_exclusions = 0;

    while (fscanf(file, "%d %d", &donnees.exclusions[donnees.nombre_exclusions].exclusion[0],
                  &donnees.exclusions[donnees.nombre_exclusions].exclusion[1]) == 2) {
        donnees.nombre_exclusions++;

        // Réallouer de la mémoire pour les exclusions
        donnees.exclusions = realloc(donnees.exclusions, sizeof(t_exclusion) * (donnees.nombre_exclusions + 1));
    }

    fclose(file);

    // Faites de même pour les fichiers precedences.txt et operations.txt...

    return donnees;
}

int main() {
    Donnees donnees = lire_donnees();

    // Utilisez les données comme nécessaire
    // Par exemple, donnees.exclusions, donnees.precedences, etc.

    // N'oubliez pas de libérer la mémoire à la fin
    free(donnees.exclusions);
    // Libérez la mémoire pour les autres structures...

    return 0;
}
