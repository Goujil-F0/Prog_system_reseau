
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier> <groupe>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct group *grp = getgrnam(argv[2]);
    if (!grp) {
        fprintf(stderr, "Groupe introuvable\n");
        return EXIT_FAILURE;
    }

    struct stat buffer;
    if (stat(argv[1], &buffer) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    if (chown(argv[1], buffer.st_uid, grp->gr_gid) == -1) {
        perror("chown");
        return EXIT_FAILURE;
    }

    printf("Groupe modifié avec succès\n");
    return EXIT_SUCCESS;
}
