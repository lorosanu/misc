#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <iostream.h>

int t, n, v[10001];

void main(void)
{
    int i,j;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    for (i=1;i<10000;i++)
        v[i]=i;
    for ( i=1;i<=100;i++)
        v[i*i]=1;
    for (i=2;i<=9999;i++)
    {

        for (j=1;j<=i-1;j++)
            if (v[i]>v[j]+v[i-j])
                v[i]=v[j]+v[i-j];
    }

    cin >>t;
    for (i=0;i<t;i++)
    {
        cin >> n;
        cout << v[n]<<endl;
    }
    //fcloseall();
}