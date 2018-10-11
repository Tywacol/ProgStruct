#include<stdio.h>

int main()
{
  int i;
  printf("Hello World\n");
  printf("Entrez un nombre : \n");
  scanf("%d",&i);
  if (i%2 == 0) {
    printf("%d est pair\n",i);
  }
  else {
    printf("%d est impair\n",i);
  }
  return 0;
}

