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
  
  while ( c != EOF) {
    
    if (c == ' ' || c == '\n') {
        if (tmp_size > size) {
            size = tmp_size;
            for (int i = 0; i < tmp_size; i++) {
                longest_word[i] = tmp_longest_word[i];
            }
        }
        for (int i = 0; i < 255; i++) {
            tmp_longest_word[i] = 'Z';
        }
        tmp_size = 0;
        nb_words++;
    } else {
        tmp_longest_word[tmp_size] = c;
        tmp_size++;
    }
    c = getchar();
    
  }
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
