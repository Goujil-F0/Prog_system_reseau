
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[10];

    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';

    printf("Droits : %s\n", perms);
}

void print_file_type(mode_t mode) {
    printf("Type : ");
    if (S_ISREG(mode)) printf("Fichier régulier\n");
    else if (S_ISDIR(mode)) printf("Répertoire\n");
    else if (S_ISLNK(mode)) printf("Lien symbolique\n");
    else if (S_ISCHR(mode)) printf("Périphérique caractère\n");
    else if (S_ISBLK(mode)) printf("Périphérique bloc\n");
    else if (S_ISFIFO(mode)) printf("FIFO\n");
    else if (S_ISSOCK(mode)) printf("Socket\n");
    else printf("Inconnu\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat buffer;

    if (lstat(argv[1], &buffer) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    print_file_type(buffer.st_mode);
    print_permissions(buffer.st_mode);

    printf("Taille : %ld octets\n", buffer.st_size);
    printf("Nombre de liens : %ld\n", buffer.st_nlink);

    struct passwd *pw = getpwuid(buffer.st_uid);
    if (pw)
        printf("Propriétaire : %s\n", pw->pw_name);

    printf("Dernière modification : %s", ctime(&buffer.st_mtime));

    return EXIT_SUCCESS;

	}
