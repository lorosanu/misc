#include <stdio.h>
#include <iostream.h>

int n, P, L, vi[21], vo[21], ni, no, nf, max;

int main(void)
{
    int i, j, x, y;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cin >> n;
    for (i=0;i<n;i++)
    {
        cin >> P >> L;
        for (j=0;j<P;j++)
        {
            vi[j]=0;
            vo[j]=0;
        }
        for (j=0;j<L;j++)
        {
            cin >>x >>y;
            vo[x]++;
            vi[y]++;
        }
        ni=0;
        no=0;
        nf=0;

        for (j=0;j<P;j++)
        {
            if (vi[j]==0 && vo[j] ==0)
                nf++;
            else
            {
                if (vi[j]==0) 
                    ni++;
                if (vo[j]==0)
                    no++;
            }
        }

        for (j=0;j<nf;j++)
        {
            ni--;
            no--;
        }

        if (ni <= no)
            max = no;
        else
            max =ni;

        cout << max + 2*nf << endl;
    }

    //fcloseall();
    return 0;
}