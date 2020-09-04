#include <stdio.h>


int main() 
{
    int initNum = 3;
    for (int i=1; i<=5; i++)
    {
        static int n1 = initNum;
    {
        int *p = &n1;
        p++;
        *p = 0;
    }
        n1++;
        printf("%d\n", n1);
    }
    return 0;
}