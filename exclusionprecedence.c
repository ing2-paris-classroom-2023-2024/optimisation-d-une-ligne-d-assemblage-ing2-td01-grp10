
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


// Fonction pour créer un graphe orienté en tenant compte des contraintes d'exclusion
void creer_graphe(t_donnees* donnees, int** graphe) {
    // Initialiser le graphe avec des zéros (pas d'arcs)
    for (int i = 0; i < donnees->nombre_operations; i++) {
        for (int j = 0; j < donnees->nombre_operations; j++) {
            graphe[i][j] = 0;
        }
    }

    // Remplir le graphe avec les arcs de précédence
    for (int i = 0; i < donnees->nombre_precedences; i++) {
        int operande1 = donnees->precedences[i].precedences[0];
        int operande2 = donnees->precedences[i].precedences[1];
        graphe[operande1][operande2] = 1;
    }

    // Exclure les arêtes entre les opérations mutuellement exclues
    for (int i = 0; i < donnees->nombre_exclusions; i++) {
        int op1 = donnees->exclusions[i].exclusion[0];
        int op2 = donnees->exclusions[i].exclusion[1];
        graphe[op1][op2] = 0;
        graphe[op2][op1] = 0;
    }
}



// Fonction auxiliaire pour le parcours DFS du graphe
void dfs(int** graphe, int sommet, int* visite, int nombre_operations, int* stations, int station_actuelle) {
    visite[sommet] = 1; // Marquer le sommet comme visité

    // Si le sommet a des voisins non visités, incrémente le nombre de stations
    for (int i = 0; i < nombre_operations; i++) {
        if (graphe[sommet][i] == 1 && !visite[i]) {
            stations[i] = station_actuelle;
            dfs(graphe, i, visite, nombre_operations, stations, station_actuelle + 1);
        }
    }
}

// Fonction pour minimiser le nombre de stations en respectant les contraintes
void minimiser_stations(t_donnees* donnees, int** graphe) {
    int* visite = (int*)malloc(sizeof(int) * donnees->nombre_operations);
    int* stations = (int*)malloc(sizeof(int) * donnees->nombre_operations);

    // Initialiser les tableaux
    for (int i = 0; i < donnees->nombre_operations; i++) {
        visite[i] = 0;
        stations[i] = 0;
    }

    int station_actuelle = 0;

    // Parcourir le graphe avec DFS
    for (int i = 0; i < donnees->nombre_operations; i++) {
        if (!visite[i]) {
            stations[i] = station_actuelle;
            dfs(graphe, i, visite, donnees->nombre_operations, stations, station_actuelle);
            station_actuelle++;
        }
    }

    // Afficher le résultat
    printf("Nombre de stations minimales : %d\n", station_actuelle);

    // Libérer la mémoire
    free(visite);
    free(stations);
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