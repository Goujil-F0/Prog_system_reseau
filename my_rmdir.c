#include <sys/stat.h>   // stat
#include <sys/types.h>
#include <unistd.h>     // rmdir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Vérifier si l'argument est fourni
    if (argc != 2) {
        printf("Usage: %s <nom_dossier>\n", argv[0]);
        return 1;
    }

    char *dirname = argv[1];
    struct stat st;

    // Vérifier si le dossier existe
    if (stat(dirname, &st) != 0) {
        printf("Erreur: le dossier '%s' n'existe pas.\n", dirname);
        return 1;
    }

    // Vérifier que c'est bien un dossier
    if (!S_ISDIR(st.st_mode)) {
        printf("Erreur: '%s' n'est pas un dossier.\n", dirname);
        return 1;
    }

    // Supprimer le dossier (fonctionne seulement s'il est vide)
    if (rmdir(dirname) == 0) {
        printf("Succès: dossier '%s' supprimé.\n", dirname);
    } else {
        printf("Erreur lors de la suppression: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
