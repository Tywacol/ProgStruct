#include <stdio.h>
#include <stdbool.h>

/* affiche les lettres non recontrees dans l'entree standart */
void unincluded_letters(void) 
{
  char lettre_rencontre[26] = { false };
  char c;
  c = getchar();
  while ( c != EOF ) {
    if (c >= 'a' && c <= 'z') {
        lettre_rencontre[c- 'a'] = true;
    }
    c = getchar();
  }
  printf("Les lettres non rencontrees sont : ");
  for (int i = 0; i<26; i++) {
      if (!lettre_rencontre[i])
          printf("%c ", i + 'a');
}
  printf("\n");
}

int main(void)
{
  printf("Debut du programme..\n");
  
  unincluded_letters();
  
  printf("Fin du progamme..\n");
  return 0;
}
