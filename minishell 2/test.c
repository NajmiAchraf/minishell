#include <stdio.h>

void    function(int *i)
{
    (*i)++;
}

int main()
{
    int i = 1;
    function(&i);
    printf("%d\n", i);
}