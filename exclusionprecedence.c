
#include "exclusionprecedence.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour lire les données depuis les fichiers
t_donnees lire_donnees() {
    t_donnees donnees;

    // Lecture du fichier exclusions.txt
    FILE *exclusion = fopen("exclusions.txt", "r");
    if (!exclusion) {
        perror("Erreur lors de l'ouverture du fichier exclusions.txt");
        exit(EXIT_FAILURE);
    }

    // Lire les données depuis le fichier exclusions.txt
    FILE* fichier_exclusions = fopen("exclusions.txt", "r");
    fscanf(fichier_exclusions, "%d", &donnees.nombre_exclusions);

    donnees.exclusions = (t_exclusion*)malloc(sizeof(t_exclusion) * donnees.nombre_exclusions);
    for (int i = 0; i < donnees.nombre_exclusions; i++) {
        fscanf(fichier_exclusions, "%d %d", &donnees.exclusions[i].exclusion[0], &donnees.exclusions[i].exclusion[1]);
    }
    fclose(fichier_exclusions);

    fclose(exclusion);

    // Lecture du fichier precedence.txt
    FILE *precedence = fopen("precedence.txt", "r");
    if (!precedence) {
        perror("Erreur lors de l'ouverture du fichier precedence.txt");
        exit(EXIT_FAILURE);
    }

    // Lire les données depuis le fichier precedences.txt
    FILE* fichier_precedences = fopen("precedences.txt", "r");
    fscanf(fichier_precedences, "%d", &donnees.nombre_precedences);

    donnees.precedences = (t_precedence*)malloc(sizeof(t_precedence) * donnees.nombre_precedences);
    for (int i = 0; i < donnees.nombre_precedences; i++) {
        fscanf(fichier_precedences, "%d %d", &donnees.precedences[i].precedences[0], &donnees.precedences[i].precedences[1]);
    }
    fclose(fichier_precedences);

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

// Fonction pour attribuer des stations aux opérations
void assigner_stations(Donnees* donnees) {
    // Création d'une liste des opérations triées par précédence
    int* operations_triees = (int*)malloc(sizeof(int) * donnees->nombre_operations);

    // Initialisation des stations
    int* stations = (int*)malloc(sizeof(int) * donnees->nombre_operations);

    // Tri des opérations par précédence
    trier_operations(donnees, operations_triees);

    // Boucle sur les opérations triées
    for (int i = 0; i < donnees->nombre_operations; i++) {
        int op = operations_triees[i];
        int couleur_interdite = 0;

        // Logique pour déterminer la couleur interdite en fonction des contraintes d'exclusion
        for (int j = 0; j < donnees->nombre_exclusions; j++) {
            if (donnees->exclusions[j].exclusion[0] == op || donnees->exclusions[j].exclusion[1] == op) {
                int autre_op;

                if (donnees->exclusions[j].exclusion[0] == op) {
                    autre_op = donnees->exclusions[j].exclusion[1];
                } else {
                    autre_op = donnees->exclusions[j].exclusion[0];
                }
                couleur_interdite = stations[autre_op];
                break;
            }
        }

        // Trouver la première couleur disponible
        int couleur = 1;
        while (couleur_presente(stations, couleur, donnees->nombre_operations) || couleur <= couleur_interdite) {
            couleur++;
        }

        // Affectation de l'opération à la station
        stations[op] = couleur;

        // Affichage des résultats (à des fins de test)
        printf("Opération %d : Station %d\n", op, couleur);
    }

    // Affichage du nombre total de stations
    printf("Nombre total de stations : %d\n", couleur_presente(stations, 0, donnees->nombre_operations));

    // Libération de la mémoire
    free(operations_triees);
    free(stations);
}

int main() {
    Donnees donnees = lire_donnees();

    // Exécution de l'algorithme
    assigner_stations(&donnees);

    // Libération de la mémoire à la fin
    free(donnees.exclusions);
    free(donnees.precedences);
    free(donnees.operations);

    return 0;
}