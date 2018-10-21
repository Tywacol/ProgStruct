#include <stdio.h>
#include <stdbool.h>

/* renvoie vrai si un certain motif est preset dans l'entree standart */
bool substring(char motif[6]) 
{
  int matchs = 0; /* count the numbers of letter who match the begining of motif */
  bool trouve = false;
  char c;
  c = getchar();
  while ( c != EOF && matchs < 6 ) {
    /* loop trough the pattern with using matchs */
    if (motif[matchs] == c) {
        matchs++;
    } else {
        /* start searching from scratch */
        matchs = 0;
    }
    c = getchar();
  }
  return matchs == 6;
}

int main(void)
{
  char motif[6] = {'b','i', 'd','u','l', 'e' }; 
  printf("Debut du programme..\n");
  
  printf(substring(motif) ? "Le motif est dans le fichier" : "Le motif n'est pas dans le fichier");
  printf("\n");
  
  printf("\nFin du progamme..\n");
  return 0;
}
