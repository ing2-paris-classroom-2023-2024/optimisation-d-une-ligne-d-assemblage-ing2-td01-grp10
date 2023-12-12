//
// Created by loryi on 12/12/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONTEMPS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONTEMPS_H

typedef struct tache {
    int exclu1, exclu2;
}t_tache1;

typedef struct tache2 {
    int taille;
    int nbTachesDifferentes;
    struct tache stockage[100] ;
} t_tache2;

typedef struct Graphe_exclusion {
    int nbSom;
    int **adjMatrix;
} t_graphe_exclu;

typedef struct machines{
    int tableau[100];

}t_machines;

struct tempexclu{
    int operation;
    unsigned int couleur;
    float temps;
};


int compter_taches2(int taches[100]);
t_tache2 lire_infos( char* nom_fichier , int taches[100]) ;
void initGraphExclu(struct tache2 exclu,struct Graphe_exclusion *graphe_exclu);
void compter_taches(int taches[100],struct tempexclu *tabexclu) ;
void remplirGrapheExclu(struct tache2 exclu,struct Graphe_exclusion *graphe_exclu) ;
void remplir_tableau( t_machines tab1, t_machines tab2, t_machines tab3, t_machines tab4, t_machines tab5, int taches[100], t_graphe_exclu *graphe_exclu );
int couleurPossible(int sommet, int couleur, int a, t_graphe_exclu *mongraphe_exclu, int *couleurs) ;
//void lireFichier(struct tempexclu *tabexclu) ;
void coloration(int taches[100], struct Graphe_exclusion *graphe_exclu, int taille, struct tempexclu *tabexclu) ;
void afficherColoration(int taille, int *couleurs, int *taches) ;
int exec_excltps() ;

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD01_GRP10_EXCLUSIONTEMPS_H
