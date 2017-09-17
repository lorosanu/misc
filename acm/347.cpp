#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

long n;
int v[500];
int s[10], viz[10], c[10];

int round(int p)
{
	int i, j, k, n =0, x, y;

	for (i=0; i<=9; i++)
		viz[i] = c[i] = 0;

	while ( p > 0)
	{
		k = p%10;

		if ( c[k] !=0 )
			return 0;

		c[k] = 1;
		s[n++] = p%10;

		p=p/10;
	}

	i = 0;
	for (k=0; k<n; k++)
	{
		y = s[i];
		x = s[i] % n;

		if ( k!= n-1 && viz[y] ==1)
			return 0;

		viz[y] = 1;
		i=  fabs((double)( n + i - x ));
		i = i%n;
	}

	if ( i != 0)
		return 0;

	return 1;
}

int main(void)
{
	//freopen("in.txt","r", stdin);
	//freopen("out.txt","w", stdout);

	int i, nr;

	v[0]=1; v[1] = 13; v[2] = 31; v[3] = 51; v[4] = 71; v[5] = 91;
	nr = 6;
	for (i=100; i< 10000000; i++)
	{
		if ( round (i) )
			v[nr++] = i;

	}


	int nrc = 1;
	while (cin >> n && n)
	{
		for (i=0; i<nr; i++)
			if (v[i] >= n)
				break;
		cout << "Case " << nrc << ": "<< v[i] << endl;
		nrc++;
	}

	//fcloseall();
	return 0;
}