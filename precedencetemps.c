#include <stdio.h>
#include <stdlib.h>
#include "precedencetemps.h"

pSommet* CreerArete_prec(pSommet* sommet,int s1,int s2)
{
    sommet[s2]->parent+=1;
    sommet[s1]->degre++;
    sommet[s2]->degre++;
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }
    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->valeur=temp->valeur;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe_prec(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->couleur=0;
        Newgraphe->pSommet[i]->degre=0;
        Newgraphe->pSommet[i]->parent=0;
    }
    return Newgraphe;
}


/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
 */
Graphe * lire_graphe_oriente(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int orientation, taille;
    int ordre=0;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    taille=0;
    int s1,s2;
    
    while(fscanf(ifs,"%d %d",&s1,&s2)==2){
        taille++;
    }
    int** arcs = malloc(taille*sizeof(int*));
    fclose(ifs);
    FILE* f = fopen(nomFichier,"r");
    for(int i=0;i<taille;i++){
        fscanf(f,"%d %d",&s1,&s2);
        arcs[i]=malloc(2*sizeof(int));
        arcs[i][0]=s1-1;
        arcs[i][1]=s2-1;
        if(arcs[i][0] > ordre){
            ordre=arcs[i][0];
        }
        if(arcs[i][1] > ordre){
            ordre=arcs[i][1];
        }
    }
    ordre++;
    graphe=CreerGraphe_prec(ordre); // créer le graphe d'ordre sommets
    graphe->orientation=1;
    graphe->ordre=ordre;
    graphe->taille=taille;
    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    { 
        graphe->pSommet=CreerArete_prec(graphe->pSommet, arcs[i][0],arcs[i][1]);
    }

    return graphe;
}

void enfiler(int* file1, int sommet){
    if(file1[0]==-1){
        file1[0]=sommet;
    }
    else{
        int i = 0;
        while(file1[i]!=-1){
            i++;
        }
        file1[i]=sommet;
    }
}

int defiler(int* file,int taille){
    int elem = file[0];
    for(int i=0;(i<taille-1)||(file[i]==-1);i++){
        file[i]=file[i+1];
    }
    file[taille-1]=-1;
    return elem;
}

void newStation(Station* station){
    station->tab=malloc(sizeof(int));
    station->temps=0;
    station->pos=0;
}

void precedencetemps(Graphe* g, float* temps, float limite){
    int* file=(int*)malloc(g->ordre*sizeof(int));
    int* precedence = malloc(g->ordre*sizeof(int));
    int cpt=0;
    int nb_station=1;
    Station* station = malloc(sizeof(Station));
    newStation(&station[0]);
    for(int i=1;i<g->ordre;i++){
        file[i]=-1;
    }
    for(int i=0;i<g->ordre;i++){
        if(g->pSommet[i]->degre!=0 && g->pSommet[i]->parent==0){
            file[cpt]=i;
            cpt++;
        }
    }
    int id=0;
    int sommet;
    while(file[0]!=-1){
        sommet = defiler(file,g->ordre);
        if(station[id].temps+temps[sommet]<=limite){
            station[id].tab[station[id].pos]=sommet;
            station[id].temps+=temps[sommet];
            station[id].pos+=1;
            station[id].tab=realloc(station[id].tab,(station[id].pos+1)*sizeof(int));
        }
        else{
            station=realloc(station,(nb_station+1)*sizeof(Station));
            newStation(&station[nb_station]);
            id++;
            station[id].tab=realloc(station[id].tab,(station[id].pos+1)*sizeof(int));
            station[id].tab[station[id].pos]=sommet;
            station[id].temps+=temps[sommet];
            station[id].pos+=1;
            nb_station++;
            
        }
        while(g->pSommet[sommet]->arc!=NULL){
            int suiv = g->pSommet[sommet]->arc->sommet;
            g->pSommet[suiv]->parent--;
            if(g->pSommet[suiv]->couleur==0 && g->pSommet[suiv]->parent==0){
                enfiler(file,suiv);
                g->pSommet[suiv]->couleur=1;
            }
            g->pSommet[sommet]->arc=g->pSommet[sommet]->arc->arc_suivant;
        }
    }
    for(int i=0;i<nb_station;i++){
        printf("Station %d, temps d'execution : %.2f\n",i+1,station[i].temps);
        for(int j=0;j<station[i].pos;j++){
            printf("operation %d : %.2f\n",station[i].tab[j]+1,temps[station[i].tab[j]+1]);
        }
        printf("\n");
    }
}

void exec_prec(){
    Graphe * g;
    char nom_fichier[50];
    printf("entrer le nom du fichier precedence:");
    scanf("%s",nom_fichier);
    g = lire_graphe_oriente(nom_fichier);
    float* temps = malloc((g->ordre+1)*sizeof(float));
    printf("entrer le nom du fichier opérations:");
    scanf("%s",nom_fichier);
    FILE* f=fopen(nom_fichier,"r");
    int id;
    float time;
    while(fscanf(f,"%d %f",&id,&time)==2){
        temps[id]=time;
    }
    fclose(f);
    printf("entrer le nom du fichier temps_cycle:");
    scanf("%s",nom_fichier);
    FILE* f2=fopen(nom_fichier,"r");
    float limite;
    fscanf(f,"%f",&limite);
    precedencetemps(g,temps,limite);
    
}