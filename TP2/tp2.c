#include <stdio.h>
#include <stdbool.h>

#define N 3

// Return the maximum of 3 integers a, b, c
int maxi3(int a, int b, int c) {
  if (a>b && a>c) {
    return a;
  }
  if (b>a && b>c) {
      return b;
  }
  return c; 
}

// Return the sum of a tab containing N elements
int sum_tab(int *tab, int n) {
  int acc = 0;
  for (int i = 0; i < n; i++) {
    acc += tab[i];
  }
  return acc;
}

// Return the product of a tab containing N elements
int prod_tab(int *tab, int n) {
  int acc = 1;
  for (int i = 0; i < n; i++) {
    acc *= tab[i];
  }
  return acc;
}

// Return true is x<=y<=z
bool ordrecroissant(int x, int y, int z) {
  return (x <= y && y <= z);
}

// Return true if x = y = z
bool equal3(int x, int y, int z) {
  return (x == y && y == z);
}

// Return true if x, y and z are distinct from each other
bool disctinct3(int x, int y, int z) {
  return (x != y && y != z && x != z);
}

// Return true if a number is greater than the sum of the 2 others
bool exist_big(int x, int y, int z) {
  return (x >(y+z) || y <= (x +z) || z > (x + y));
} 





int main()
{
  printf("Debut du programme..\n");

  int tab[N];
  int input = 0;
  bool res;

  int t,u; // User input
  /*
  for (int i = 0; i <3; i++) {
    printf("Entrez un nombre : \n");
    scanf("%d",&tab[i]);
  }
  printf("Leur somme vaut : %d\n", sum_tab(tab, N));
  printf("Leur produit vaut : %d\n", prod_tab(tab, N));
  */

  printf("Le maximum de 3,7 et -20 est : %d\n", maxi3(3, 7, -20));
  printf("Entrez un nombre  : ");
  scanf("%d", &input);
  printf("Le maximum de 3,7 et %d est : %d\n",input, maxi3(3, 7, input));

  res = ordrecroissant(2,3,4);
  if (res) {
    printf("Oui !\n");
  }
  
  res = ordrecroissant(5,1,60);
  if (res) {
    printf("ordrecroissant(5,1,60) = Oui !\n");
  }  else {
    printf("ordrecroissant(5,1,60) = Non !\n");
  }

  printf("Entrez un nombre t  : ");
  scanf("%d", &t);

  printf("Entrez un nombre u  : ");
  scanf("%d", &u);
  
  res = ordrecroissant(t,u,70);
  if (res) {
    printf("ordrecroissant(t,u,70) = Oui !\n");
  }  else {
    printf("ordrecroissant(t,u,70) = Non !\n");
  }
  


  printf("Fin du programme..\n");
  return 0;
}
