#include <stdio.h>
#include <stdbool.h>
void mange_et_reecrit(void)
{
char c;
c = getchar();
while ( c != EOF )
{
putchar(c);
c = getchar();
}
}
int main(void)
{
mange_et_reecrit();
return 0;
}
