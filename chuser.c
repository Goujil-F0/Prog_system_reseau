
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier> <utilisateur>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct passwd *pw = getpwnam(argv[2]);
    if (!pw) {
        fprintf(stderr, "Utilisateur introuvable\n");
        return EXIT_FAILURE;
    }

    struct stat buffer;
    if (stat(argv[1], &buffer) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    if (chown(argv[1], pw->pw_uid, buffer.st_gid) == -1) {
        perror("chown");
        return EXIT_FAILURE;
    }

    printf("Utilisateur modifié avec succès\n");
    return EXIT_SUCCESS;
}



