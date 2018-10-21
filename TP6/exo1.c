#include <stdio.h>
#include <stdbool.h>

void char_count(void) 
{
  int cnt;
  char c;
  c = getchar();
  while ( c != EOF ) {
    c = getchar();
    cnt++;
  }
}

int main(void)
{
  char_countt();
  return 0;
}
