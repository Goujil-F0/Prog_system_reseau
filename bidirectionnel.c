/*
 * ============================================================
 *  Communication bidirectionnelle avec deux tubes
 * ============================================================
 * Compilation : gcc -o bidirectionnel bidirectionnel.c
 * Exécution    : ./bidirectionnel
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int p1[2];
    int p2[2];

    pid_t pid;

    int nombres[5] = {1, 2, 3, 4, 5};
    int x;

    /* Création des tubes */
    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* ==================== FILS ==================== */
    if (pid == 0)
    {
        close(p1[1]); // lecture sur p1
        close(p2[0]); // écriture sur p2

        for (int i = 0; i < 5; i++)
        {
            read(p1[0], &x, sizeof(int));

            printf("Fils reçoit : %d\n", x);

            x = x * 2;

            write(p2[1], &x, sizeof(int));
        }

        close(p1[0]);
        close(p2[1]);
    }

    /* ==================== PERE ==================== */
    else
    {
        close(p1[0]); // écriture sur p1
        close(p2[1]); // lecture sur p2

        for (int i = 0; i < 5; i++)
        {
            write(p1[1], &nombres[i], sizeof(int));
        }

        for (int i = 0; i < 5; i++)
        {
            read(p2[0], &x, sizeof(int));

            printf("Père reçoit le double : %d\n", x);
        }

        close(p1[1]);
        close(p2[0]);
    }

    return 0;
}
