#include <stdio.h>

int main(void)
{
    long i;
    long n=5;
    long s;

    while(n>=3)
    {
        scanf("%ld", &n);

        s = 0;

        for(i=2; i<=n-2; i++)
        {
                    
            if(n >= 2*i)
            {
                s += (n - 2*i + 1) * (i - 1);
                s += (i - 2) * (i - 1) / 2;
            }

            else
                s += (n - i - 1) * (n - i) / 2;
        }

        printf("%ld\n", s);
    }

    return 0;
}