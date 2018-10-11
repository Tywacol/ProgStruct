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
  for (int i = 0; i < N; i++) {
    acc += tab[i];
  }
  return acc;
}

// Return the product of a tab containing N elements
int prod_tab(int *tab, int n) {
  int acc = 1;
  for (int i = 0; i < N; i++) {
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
