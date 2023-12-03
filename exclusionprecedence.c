
#include "exclusionprecedence.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour lire les données depuis les fichiers
t_donnees lire_donnees() {
    t_donnees donnees;


    // Lire les données depuis le fichier exclusions.txt
    FILE* fichier_exclusions = fopen("exclusions.txt", "r");

    donnees.exclusions = (t_exclusion*)malloc(sizeof(t_exclusion));
    int i = 0;
    while(fscanf(fichier_exclusions, "%d %d", &donnees.exclusions[i].exclusion[0], &donnees.exclusions[i].exclusion[1])==2){
        donnees.exclusions = realloc(donnees.exclusions, sizeof(t_exclusion)*i+1);
        i++;
    }
    donnees.nombre_exclusions=i-1;
    fclose(fichier_exclusions);
    // Lecture du fichier precedence.txt
    FILE *precedence = fopen("precedences.txt", "r");
    if (!precedence) {
        perror("Erreur lors de l'ouverture du fichier precedence.txt");
        exit(EXIT_FAILURE);
    }

    // Lire les données depuis le fichier precedences.txt
    FILE* fichier_precedences = fopen("precedences.txt", "r");
    i=0;
    donnees.precedences = (t_precedence*)malloc(sizeof(t_precedence));
    while(fscanf(fichier_precedences, "%d %d", &donnees.precedences[i].precedences[0], &donnees.precedences[i].precedences[1])==2){
        donnees.precedences=realloc(donnees.precedences,sizeof(t_precedence)*i+1);
        i++;
    }
    donnees.nombre_precedences=i-1;
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



// Utilisation du DFS pour le parcours du graphe
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
void min_stations(t_donnees* donnees, int** graphe) {
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


void exclprec(){
    t_donnees donnees = lire_donnees();
    // Création du graphe
    int** graphe = (int**)malloc(sizeof(int*) * donnees.nombre_operations);
    for (int i = 0; i < donnees.nombre_operations; i++) {
        graphe[i] = (int*)malloc(sizeof(int) * donnees.nombre_operations);
    }
    printf("hi\n");

    creer_graphe(&donnees, graphe);
    printf("hi\n");
    // Minimiser le nombre de stations
    min_stations(&donnees, graphe);
    printf("hi\n");
     // Libération de la mémoire à la fin
     for (int i = 0; i < donnees.nombre_operations; i++) {
        free(graphe[i]);
     }
    free(graphe);
    printf("hi\n");

    free(donnees.exclusions);
    free(donnees.precedences);
    printf("hi\n");

}
