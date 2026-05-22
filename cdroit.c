
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <fichier> <user|group|other> <lecture|ecriture|execution|rien>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat buffer;
    if (stat(argv[1], &buffer) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    mode_t mode = buffer.st_mode;

    // Masques
    mode_t mask_user = S_IRUSR | S_IWUSR | S_IXUSR;
    mode_t mask_group = S_IRGRP | S_IWGRP | S_IXGRP;
    mode_t mask_other = S_IROTH | S_IWOTH | S_IXOTH;

    mode_t *mask = NULL;

    if (strcmp(argv[2], "user") == 0) mask = &mask_user;
    else if (strcmp(argv[2], "group") == 0) mask = &mask_group;
    else if (strcmp(argv[2], "other") == 0) mask = &mask_other;
    else {
        fprintf(stderr, "Type utilisateur invalide\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[3], "rien") == 0) {
        mode &= ~(*mask);
    } else {
        mode_t bit = 0;

        if (strcmp(argv[2], "user") == 0) {
            if (strcmp(argv[3], "lecture") == 0) bit = S_IRUSR;
            else if (strcmp(argv[3], "ecriture") == 0) bit = S_IWUSR;
            else if (strcmp(argv[3], "execution") == 0) bit = S_IXUSR;
        }
        else if (strcmp(argv[2], "group") == 0) {
            if (strcmp(argv[3], "lecture") == 0) bit = S_IRGRP;
            else if (strcmp(argv[3], "ecriture") == 0) bit = S_IWGRP;
            else if (strcmp(argv[3], "execution") == 0) bit = S_IXGRP;
        }
        else {
            if (strcmp(argv[3], "lecture") == 0) bit = S_IROTH;
            else if (strcmp(argv[3], "ecriture") == 0) bit = S_IWOTH;
            else if (strcmp(argv[3], "execution") == 0) bit = S_IXOTH;
        }

        if (bit == 0) {
            fprintf(stderr, "Droit invalide\n");
            return EXIT_FAILURE;
        }

        mode |= bit;
    }

    if (chmod(argv[1], mode) == -1) {
        perror("chmod");
        return EXIT_FAILURE;
    }

    printf("Droits modifiés avec succès\n");
    return EXIT_SUCCESS;
}
