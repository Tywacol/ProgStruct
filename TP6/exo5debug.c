#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* return the longest word in the standart input */
char* longest_word(char * longest_word) 
{
  int size = 0;
  int tmp_size = 0;
  char *tmp_longest_word = malloc(sizeof(char) * 255);
  
  char c;
  c = getchar();
  int iter = 0;
  while ( c != EOF) {
    printf("Iteration %d ",iter++);
    if (c == ' ' || c == '\n') {
        printf("if ");
        if (tmp_size > size) {
            size = tmp_size;
            printf("for : ");
            for (int i = 0; i < tmp_size; i++) {
                longest_word[i] = tmp_longest_word[i];
                printf("%c", longest_word[i]);
            }
        }
        printf(" \nremise à 0 de tmp_longest_word\n");
        printf("c = %d\n",c);
        for (int i = 0; i < 255; i++) {
            tmp_longest_word[i] = 'Z';
        }
        tmp_size = 0;
    } else {
        tmp_longest_word[tmp_size] = c;
        
        printf("\n<test>\n");
        printf("c = %c\n",c);
        printf("tmp_longest_word[%d] = %c\n",tmp_size, tmp_longest_word[tmp_size]);
        printf("</test>\n");
        printf("else , tmp_longest_word[%d]=%c, tmp_size = %d\n",tmp_size, tmp_longest_word[tmp_size], tmp_size);
        
        tmp_size++;
    }
    c = getchar();
    
  }
  printf("FIN :\n");
  printf("tmp_longest_word = ");
  for (int i = 0; i < size; i++) {
            printf("tmp_longest_word[%d] = %c\n",i, tmp_longest_word[i]);
        }
    printf("/FIN\n");
  
  printf("\n");
  return longest_word;
}

int main(void)
{
  printf("Debut du programme..\n\n");
  
  char *longest = malloc(sizeof(char) * 255);
  longest_word(longest);
  int i = 0;
  
  printf("Le mot le plus long du fichier est : ");

  while (longest[i]) {
    printf("%c", longest[i]);
    i++;
  } 
  
  printf("\n\nFin du progamme..\n");
  return 0;
}
