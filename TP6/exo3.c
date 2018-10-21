#include <stdio.h>
#include <stdbool.h>

/* ecrit l'entree à l'envers */
void str_reverse(void) 
{
  char input[1024] = { false };
  int i = 0;
  char c;
  c = getchar();
  while ( c != EOF ) {
    input[i] = c;
    i++;
    c = getchar();
  }
  for (i; i>-1; i--) {
      putchar(input[i]);
  }
}

int main(void)
{
  printf("Debut du programme..\n");
  
  str_reverse();
  printf("\n");
  
  printf("\nFin du progamme..\n");
  return 0;
}
