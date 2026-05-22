/*
 * ============================================================
 *  Sauvegarde lors de Ctrl+C
 * ============================================================
 * Compilation : gcc -o sigint_save sigint_save.c
 * Exécution    : ./sigint_save
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *fichier;

/* Gestionnaire du signal SIGINT */
void handler(int sig)
{
    printf("\n[CTRL+C détecté]\n");

    fichier = fopen("sauvegarde.txt", "w");

    if (fichier == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "Sauvegarde des données avant arrêt du programme.\n");

    fclose(fichier);

    printf("Données sauvegardées dans sauvegarde.txt\n");

    exit(EXIT_SUCCESS);
}

int main()
{
    /* Association du signal SIGINT au gestionnaire */
    signal(SIGINT, handler);

    printf("Programme en cours...\n");
    printf("Appuyez sur Ctrl+C pour arrêter.\n");

    while (1)
    {
        sleep(1);
    }

    return 0;
}
