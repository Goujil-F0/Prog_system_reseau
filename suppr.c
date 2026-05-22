
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc != 2) {
       fprintf(stderr, "Usage: %s <nom_fichier>\n", argv[0]);
       return EXIT_FAILURE;
   }

   if (unlink(argv[1]) == -1) {
       perror("unlink");
       return EXIT_FAILURE;
   }

   printf("Fichier supprimé avec succès\n");
   return EXIT_SUCCESS;
}


