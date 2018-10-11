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

// From Grisoni

bool ordre_croissant(int a, int b, int c)
{
  int res;
  res = (a<b && b<c); // true si a<b<c, false sinon.
  return res;
}

/* Retourne true si et seulement si a,b,c sont tous impairs */ 
bool tous_impairs(int a, int b, int c)
{
  int res;
  res = (a%2==1) && (b%2==1) && (c%2==1); // formule "tous impairs"
  return res;
}

/* Retourne true ssi a==b==c */  
bool egaux(int a, int b, int c)
{
  return ((a==b) && (b==c)); // directement !
}

/* Retourne true ssi a,b,c tous distincts */  
bool distincts(int a, int b, int c)
{
  return ((a!=b) && (b!=c) && (a!=c)); 
}

/* Retourne true ssi l'un est plus grand que la somme des 2 autres */
bool somme(int a, int b, int c)
{
  return ((a>=b+c) || (b>=c+a) || (c>=a+b));
}

/*Retourne true ssi les trois mesures sont celles d'un triangle rect*/
bool rectangle(int a, int b, int c)
{
  return((a*a==b*b+c*c) || (b*b==c*c+a*a) || (c*c==b*b+a*a));
} 
