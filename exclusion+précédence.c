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

// Fonction pour déterminer si une couleur est déjà utilisée
int couleur_presente(int* stations, int couleur, int nombre_operations) {
    for (int i = 0; i < nombre_operations; i++) {
        if (stations[i] == couleur) {
            return 1;  // Couleur déjà utilisée
        }
    }
    return 0;  // Couleur disponible
}

// Fonction de comparaison pour le tri en fonction des contraintes de précédence
int comparaison_precedence(const void* a, const void* b) {
    const t_precedence* prec_a = (const t_precedence*)a;
    const t_precedence* prec_b = (const t_precedence*)b;
    return prec_a->precedences[1] - prec_b->precedences[1];
}


// Fonction pour trier les opérations en fonction des contraintes de précédence
void trier_operations(Donnees* donnees, int* operations_triees) {
    // Copie des contraintes de précédence dans un tableau temporaire
    t_precedence* prec_temp = malloc(sizeof(t_precedence) * donnees->nombre_precedences);
    for (int i = 0; i < donnees->nombre_precedences; i++) {
        prec_temp[i] = donnees->precedences[i];
    }

    // Trier le tableau temporaire en fonction des contraintes de précédence
    qsort(prec_temp, donnees->nombre_precedences, sizeof(t_precedence), comparaison_precedence);

    // Remplir le tableau d'opérations triées en suivant l'ordre de tri des contraintes de précédence
    for (int i = 0; i < donnees->nombre_precedences; i++) {
        operations_triees[i] = prec_temp[i].precedences[0];
    }

    // Libération de la mémoire
    free(prec_temp);
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
