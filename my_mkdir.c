#include <sys/stat.h>   // mkdir, stat
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>      // gestion des erreurs

int main(int argc, char *argv[]) {
    // Vérifier si l'argument est fourni
    if (argc != 2) {
        printf("Usage: %s <nom_dossier>\n", argv[0]);
        return 1;
    }

    char *dirname = argv[1];
    struct stat st;

    // Vérifier si le dossier existe déjà
    if (stat(dirname, &st) == 0) {
        printf("Erreur: le dossier '%s' existe déjà.\n", dirname);
        return 1;
    }

    // Créer le dossier avec les permissions 0755
    if (mkdir(dirname, 0755) == 0) {
        printf("Succès: dossier '%s' créé.\n", dirname);
    } else {
        // Afficher l'erreur système
        printf("Erreur lors de la création: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
