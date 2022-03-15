#include<stdio.h>
int main(void)
{
    int i, num;
    int g, s, b;
    
    while(scanf("%d", &num) == 1)
    {
        b = num / 100;
        s = num / 10 - b*10;
        g = num - b*100 - s*10;
        for(i = 0; i < b; i++)
            printf("B");
        for(i = 0; i < s; i++)
            printf("S");
        for(i = 1; i <= g; i++)
            printf("%d", i);
    }
    return 0;
}
