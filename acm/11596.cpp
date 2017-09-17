#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

int d[200];
unsigned long long A0, B0, An, C0, delta, s;
unsigned long long sol[200], nr, n;

void divizori(int b)
{
	n=0;
	if (b%2 == 0)
	{
		d[n] = 2;
		n++;
	}

	for (int i=1;i<=sqrt((double)b);i=i+2)
		if (b%i == 0)
		{
			d[n] = i;
			n++;
		}
}


void sortare()
{
	int ok;
	
	do
	{
		ok = 0;
		for (int i=0;i<nr-1;i++)
			if (sol[i]>sol[i+1])
			{
				int aux = sol[i];
				sol[i]=sol[i+1];
				sol[i+1]=aux;
				ok=1;
			}
	}
	while (ok);
}



int main(void)
{
	//freopen("in.txt","r", stdin);
	//freopen("out.txt","w", stdout);

	int i;

	while (cin >> A0 >> An >> B0 && (A0!=0 || An!=0 || B0!=0) )
	{
		n=0; nr = 0;

		if (B0 < A0  || A0 > An)
			cout << "-1" << endl;
		else
			{
				divizori(B0);

				for (i = 0; i<n; i++)
				{
					C0 =  d[i] + ( B0/d[i] );			// C0 = 2* ( d[i] + (B0/d[i]))  ...
					delta = C0 * C0 + 4 * (An - A0);
					s = sqrt((double)delta);
					if (s*s == delta)
						if ( (s-C0)>=0 && (s-C0) % 4 == 0 )
						{
							int n1 = (s-C0)/4;
							sol[nr]=n1;
							nr++;
						}		
				}

				if (nr > 0)
				{
					sortare();
					for (i=0;i<nr-1;i++)
						if (sol[i]!=sol[i+1])
							cout << sol[i]<<endl;
					cout << sol[nr-1]<<endl;
				}
				else
					cout << "-1" <<endl;
			}

		cout <<endl;
	}

	//fcloseall();
	return 0;
}