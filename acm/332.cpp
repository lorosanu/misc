#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

int j, k, n;
long x;
char s[200];
long p, q, r;
int v[200];

int gcd(long a, long b)
{
	if ( a%b ==0)
		return b;
	else
		return gcd(b, a%b);
}

int main(void)
{
	//freopen("in.txt","r", stdin);
	//freopen("out.txt","w", stdout);

	int i, nrc = 1, nr;

	while (cin >> j && j!=-1)
	{
		cin >> s;
		n = strlen(s); 
		k = n - 2 -j;
		x=0;
		
		nr = 1; v[0]=0;
		for (i = 2; i<n; i++)
		{
			x = x*10 + (s[i]-'0');
			v[nr++] = x;
		}
		
		if (j==0)
		{
			p = x;
			q = pow(10.0, k);
		}
		else
		{
			p = x - v[k];
			q = pow(10.0, k+j) - pow(10.0, k);
		}

		r = gcd(p, q);
		p = p/r;
		q = q/r;
		cout << "Case "<<nrc<<": "<< p<<"/"<<q<<endl;
		nrc++;
	}

	//fcloseall();
	return 0;
}