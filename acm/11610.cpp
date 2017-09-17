#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;


#define D 7000000
int p[D];

int v[100000];
int k[100000];


void set(int x)
{
	p[x/16]|=(1<<(x%16-1));
}

int get(int x)
{
	if(x==2)
		return 1;
	else
		return x%2 && (p[x/16]&(1<<(x%16-1)))==0;
}

void ciur(int N)
{
	int i,j;
	for(i=3; i<N; i+=2)
	{
		int x= N/i;
		for(j=3;j<=x;j+=2)
			set(i*j);
	}
}


int reverse ( int a)
{
	int c = 0;
	while (a > 0)
	{
		c = c * 10 + a%10;
		a = a/10;
	}
	return c;
}

int numar(int a)
{
	int i, nr=0, b=0, p=0;
	
	int s = sqrt((double)a);

	for (i= 2; i<=s; i++)
		if ( a % i == 0)
		{
			p = a/i;
			if (get(i))
			{
				b=a;
				while (b % i ==0 && b>0)
				{
					nr++;
					b/=i;
				}
			}
			else
				if ( p>s && get(p) )
				{
					b=a;
					while(b % p == 0 && b>0)
					{
						nr++;
						b/=p;
					}
				}
		}

	return nr;
}

int cautare_binara(int x, int p, int q)
{
	while ( p <= q )
	{
		int m = (p+q) /2;
		if (v[m] == x)
			return m;
		else
			if (x< v[m])
				q = m-1;
			else
				p = m+1;
	}
	return -1;
}


int main(void)
{
	//freopen("in.txt","r", stdin);
	//freopen("out.txt", "w", stdout);
	
	int x, i;
	char s;

	ciur(2500000);

	int n=0;
	for(i=1000010;i<10000000;i+=10)
	{
		x = reverse(i);
		if(get(x))
		{
			v[n] = i;
			k[n++] = numar(i);
		}
	}

	int nr, suma=0;
	while ( cin >> s >> x )
	{
		if (s == 'q')
		{
			suma = 0;
			nr = i = 0;
			
			while (nr <= x)
			{
				if (k[i] !=-1) 
				{
					suma+= k[i];
					nr++;
				}
				i++;
			}
			cout << suma << endl;
		}
		if (s == 'd')
		{
			i = cautare_binara(x, 0, n-1);
			if (i!=-1)
				k[i] =-1;
		}
	}

	//fcloseall();
	return 0;
}
