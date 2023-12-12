#include "exclusiontemps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int compter_taches2(int taches[100]){

    FILE *file = fopen("exclusion.txt", "r");

    t_tache1 exclusion1;


    int nb_taches_differentes = 0;
    while (fscanf(file, "%d %d", &exclusion1.exclu1, &exclusion1.exclu2) == 2) {
        int i;
        for (i = 0; i < nb_taches_differentes; i++) {
            if (taches[i] == exclusion1.exclu1) {
                break;
            }
        }
        if (i == nb_taches_differentes) {
            taches[nb_taches_differentes++] = exclusion1.exclu1;
        }

        // Vérifier si exclusion1.exclu2 est une nouvelle tâche
        for (i = 0; i < nb_taches_differentes; i++) {
            if (taches[i] == exclusion1.exclu2) {
                break;  // Tâche déjà présente, sortir de la boucle
            }
        }
        if (i == nb_taches_differentes) {
            taches[nb_taches_differentes++] = exclusion1.exclu2;
        }
    }
    printf("Taches differentes : ");
    for (int j = 0; j < nb_taches_differentes; j++) {
        printf("%d ", taches[j]);
    }
    printf("\n\n ");
    printf("il y a %d taches differentes\n\n",nb_taches_differentes);

    return nb_taches_differentes;

}

t_tache2 lire_infos( char* nom_fichier , int taches[100]) {

    FILE *file = fopen("exclusion.txt", "r");
    t_tache2 exclu;

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur de lecture du fichier\n");
        exit(-1);
    }
    else{printf("lecture ok\n");
    }
    for(int i=0;i<100;i++){
        exclu.stockage[i].exclu1=0;
        exclu.stockage[i].exclu2=0;
    }

    exclu.taille = 0;
    int valeur1, valeur2;
    while(fscanf(fichier,"%d %d",&valeur1,&valeur2)==2){
        exclu.stockage[exclu.taille].exclu1=valeur1;
        exclu.stockage[exclu.taille].exclu2=valeur2;
        exclu.taille=exclu.taille+1;
    }
    fclose(fichier);
    printf("taille:%d\n",exclu.taille);

    exclu.nbTachesDifferentes = compter_taches2(taches);


    fclose(fichier);
    return exclu;
}

void initGraphExclu(struct tache2 exclu,struct Graphe_exclusion *graphe_exclu) {
    /*graphe mongraphe = (graphe*)malloc(sizeof(graphe));
    if (mongraphe == NULL) {
        printf("Erreur d'allocation\n");
    }*/
     graphe_exclu->nbSom = exclu.nbTachesDifferentes;
    graphe_exclu->adjMatrix = malloc(2* sizeof(int *));
    for (int i = 0; i < 2; ++i) {
        graphe_exclu->adjMatrix[i] = calloc(graphe_exclu->nbSom, sizeof(int));
    }
    if (graphe_exclu->adjMatrix == NULL) {
        printf("Erreur d'allocation de mémoire pour la matrice d'adjacence.\n");
    }
    for (int i = 0; i < graphe_exclu->nbSom; i++) {
        graphe_exclu->adjMatrix[i] = (int*)malloc(graphe_exclu->nbSom * sizeof(int));
        // Initialiser la matrice à zéro
    }
    if (graphe_exclu->adjMatrix == NULL) {
        printf("Erreur d'allocation de mémoire pour la matrice d'adjacence.\n");
    }
    //printf("taille1:%d\n",exclu.taille);

    printf("matrice initialise\n");
}

void compter_taches(int taches[100],struct tempexclu *tabexclu) {

    FILE *file = fopen("exclusion.txt", "r");

    t_tache1 exclusion1;


    int nb_taches_differentes = 0;


    while (fscanf(file, "%d %d", &exclusion1.exclu1, &exclusion1.exclu2) == 2) {
        int i;
        for (i = 0; i < nb_taches_differentes; i++) {
            if (taches[i] == exclusion1.exclu1) {
                break;
            }
        }
        if (i == nb_taches_differentes) {
            taches[nb_taches_differentes++] = exclusion1.exclu1;
        }

        // Vérifier si exclusion1.exclu2 est une nouvelle tâche
        for (i = 0; i < nb_taches_differentes; i++) {
            if (taches[i] == exclusion1.exclu2) {
                break;  // Tâche déjà présente, sortir de la boucle
            }
        }
        if (i == nb_taches_differentes) {
            taches[nb_taches_differentes++] = exclusion1.exclu2;
        }
    }

    printf("Taches differentes : ");
    for (int j = 0; j < nb_taches_differentes; j++) {
        printf("%d ", taches[j]);
        tabexclu[j].operation = taches[j];
    }
    printf("\n\n ");
    printf("il y a %d taches differentes\n\n", nb_taches_differentes);

}


void remplirGrapheExclu(struct tache2 exclu,struct Graphe_exclusion *graphe_exclu) {

    /*for (int i = 0; i<exclu.taille; i++) {
        printf("ligne %d valeur: %d %d\n", i, exclu.stockage[i].exclu1, exclu.stockage[i].exclu2);
    }*/

    for(int b=0;b<exclu.taille;b++){
        //printf("b=%d et taille=%d\n",b,exclu.taille);
        graphe_exclu->adjMatrix[0][b]=exclu.stockage[b].exclu1;
        graphe_exclu->adjMatrix[1][b]=exclu.stockage[b].exclu2;
        printf("|%d||%d|\n",graphe_exclu->adjMatrix[0][b],graphe_exclu->adjMatrix[1][b]);
    }
} /// lire le fichier a l'envers pour gerer les doublons

void remplir_tableau( t_machines tab1, t_machines tab2, t_machines tab3, t_machines tab4, t_machines tab5, int taches[100], t_graphe_exclu *graphe_exclu ){

    if (tab1.tableau[100]==0 ){

        if (tab2.tableau[100]==0 ){
            if (tab3.tableau[100]==0 ){
                if (tab4.tableau[100]==0 ){
                    if (tab5.tableau[100]==0 ){
                    }
                }
            }
        }
    }
}

int couleurPossible(int sommet, int couleur, int a, t_graphe_exclu *mongraphe_exclu, int *couleurs) {
    for (int i = 0; i < a; i++) {
        if (mongraphe_exclu->adjMatrix[sommet][i] && couleur == couleurs[i]) {
            return 0; // La couleur est déjà utilisée par un sommet voisin
        }
    }
    return 1; // La couleur est possible
}

/*void lireFichier(struct tempexclu *tabexclu) {
    FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    int operation;
    float temps;
    int taille = 0;

    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {
        tabexclu[taille].operation = operation;
        tabexclu[taille].temps = temps;
        taille++;

        if (taille >= 100) {
            printf("Erreur: Tableau de taille dépassée\n");
        }
    }
    fclose(fichier);
    for(int i=0;i<taille;i++){
        printf("operation:%d   duree:%d\n",tabexclu[i].operation,tabexclu[i].temps);
    }

}*/

void coloration(int taches[100], struct Graphe_exclusion *graphe_exclu, int taille, struct tempexclu *tabexclu) {
    FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    int operation;
    float temps;
    int taille1 = 0;

    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {
        for(int i=0;i<taille;i++){
            if(operation==tabexclu[i].operation){
                tabexclu[i].temps=temps;
            }
        }
        taille1++;

        if (taille1 >= 100) {
            printf("Erreur: Tableau de taille dépassée\n");
        }
    }
    fclose(fichier);
    for (int i = 0; i < taille; i++) {
        tabexclu[i].couleur = 1; // Initialise la couleur à 1 par défaut
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < taille; b++) {
                if (taches[i] == graphe_exclu->adjMatrix[a][b]) {
                    if (a == 0) {
                        for (int c = 0; c < taille; c++) {
                            if (taches[c] == graphe_exclu->adjMatrix[1][b]) {
                                tabexclu[i].couleur = tabexclu[i].couleur + 1;
                            }
                        }
                    }
                }
            }
        }
        // Appliquer les exclusions
        for (int j = 0; j < taille; j++) {
            if (j != i) {
                for (int k = 0; k < taille; k++) {
                    if (taches[j] == graphe_exclu->adjMatrix[0][k] && taches[i] == graphe_exclu->adjMatrix[1][k]) {
                        if (tabexclu[i].couleur == tabexclu[j].couleur) {
                            tabexclu[i].couleur = tabexclu[i].couleur + 1;
                        }
                    }
                    if (taches[j] == graphe_exclu->adjMatrix[1][k] && taches[i] == graphe_exclu->adjMatrix[0][k]) {
                        if (tabexclu[i].couleur == tabexclu[j].couleur) {
                            tabexclu[i].couleur = tabexclu[i].couleur + 1;
                        }
                    }
                }
            }
        }
    }

    // Tri du tableau par couleur (utilisation de l'algorithme de tri à bulles pour la simplicité)
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tabexclu[j].couleur > tabexclu[j + 1].couleur) {
                // Échanger les éléments
                struct tempexclu temp = tabexclu[j];
                tabexclu[j] = tabexclu[j + 1];
                tabexclu[j + 1] = temp;
            }
        }
    }
    printf("taille:%d\n",taille1);
    // Affichage des résultats triés
    float tempstot=0;
    for (int i = 0; i < taille; i++) {
        if(tabexclu[i].couleur!=tabexclu[i-1].couleur){
            tempstot=0;
            printf("---------------------------------\n");
        }
        tempstot=tempstot+tabexclu[i].temps;
        printf("l'operation: %d --> machine: %u  temps:%.2f\n", tabexclu[i].operation, tabexclu[i].couleur, tempstot);

    }
    /*FILE *fichier = fopen("operations.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    int operation;
    float temps;
    int taille1 = 0;

    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {

        for(int i=0; i<taille; i++){

        }
        tabexclu[taille1].temps = temps;
        taille1++;

        if (taille1 >= 100) {
            printf("Erreur: Tableau de taille dépassée\n");
        }
    }
    fclose(fichier);
    for(int i=0;i<taille;i++){
        printf("oparation:%d  temps:%.2f\n",tabexclu[i].operation,tabexclu[i].temps);
    }*/


}

void afficherColoration(int taille, int *couleurs, int *taches) {
    for (int i = 0; i < taille; i++) {
        printf("Tache %d : Machine %d\n", taches[i], couleurs[i]);
    }
}

int exec_excltps() {
    t_tache1 exclusion1 ;
    t_machines tab1;
    t_machines tab2;
    t_machines tab3;
    t_machines tab4;
    t_machines tab5;

    for(int i =0 ; i<100 ; i++){
        tab1.tableau[i]=0;
        tab2.tableau[i]=0;
        tab3.tableau[i]=0;
        tab4.tableau[i]=0;
        tab5.tableau[i]=0;
    }
    struct tempexclu tableau_exclusion[100];

    int taches[100];
    t_tache2 essai = lire_infos( "exclusion.txt" , taches);

    //printf("taille %d",essai.taille);

    struct Graphe_exclusion graphe_exclu;
    int *bool2= calloc(essai.taille, sizeof(int));
    if (bool2 == NULL) {
        printf("Erreur d'allocation bool\n");
    }
    compter_taches(taches,&tableau_exclusion);
    int a= compter_taches2(taches);

    initGraphExclu(essai, &graphe_exclu);
    remplirGrapheExclu(essai, &graphe_exclu);
    remplir_tableau(tab1,tab2,tab3,tab4,tab5,taches, &graphe_exclu);

    int* couleurs = calloc(essai.taille, sizeof(int));


    printf("%d\n", essai.taille);
    //lireFichier(&graphe_exclu);
    coloration(taches,&graphe_exclu,a,&tableau_exclusion);

    /*if (colorerGraphe( essai.taille, &graphe_exclu, couleurs, a)) {
        printf("Attribution de machines réussie.\n");
        afficherColoration(a, couleurs, taches);
    } else {
        printf("Aucune attribution de machines possible.\n");
    }*/
    free(couleurs);

    return 0;
}
