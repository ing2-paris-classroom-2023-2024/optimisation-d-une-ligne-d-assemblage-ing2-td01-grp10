#include <stdio.h>
#include <stdlib.h>
#include "exclusionprecedence.h"


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

