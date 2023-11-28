#include <stdio.h>

int main() {
    // Déclaration d'une variable pour stocker le nom de l'utilisateur
    char nom[50];

    // Demander à l'utilisateur d'entrer son nom
    printf("Entrez votre nom : ");

    // Lire le nom de l'utilisateur depuis la console
    scanf("%s", nom);

    // Afficher un message de salutation avec le nom de l'utilisateur
    printf("Bonjour, %s !\n", nom);

    // Indiquer que le programme s'est exécuté avec succès
    return 0;
}
