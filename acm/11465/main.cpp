#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

int C[50][50];
int n, m, k; 
int a[50], b[50], h[50];
int v1[100000], v2[100000];
int dim1, dim2;
unsigned long long s1[100000], s2[100000], max1[100000], max2[100000], P;
unsigned long long nr = 0;


int sume(unsigned long long s[], int v[], int a[], unsigned long long max[], int n)
{
	int dim, i, j;
	int l = pow((double)2, n);

	for (i = 0; i<= l; i++)
	{
		s[i] = 0;
		v[i] = 0;
		max[i] = 0;
	}

	dim = 1;
	s[0] = a[0];
	max[0] = a[0];
	v[0] = 1;
	for (i = 1; i<n; i++)
	{
		for (j = dim; j>=0; j--)
			if (s[j] !=0 )
			{
				s[dim] = a[i] + s[j];
				v[dim] = 1+ v[j];

				if ( a[i] > max[dim])
					max[dim] = a[i];
				dim++;
			}
		s[dim] = a[i];
		v[dim] = 1;
		max[dim] = a[i];
		dim++;
	}
	return dim;
}


void QSort(int p, int q, unsigned long long s[], int v[], unsigned long long max[])
{
	int i= p;
	int j = q;
	unsigned long long x = v[(i+j)/2];
	do
	{
		while ( v[i] < x ) i++;
		while ( v[j] > x ) j--;

		if (i<=j)
		{
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;

			unsigned long long ax = s[i];
			s[i] = s[j];
			s[j] = ax;

			unsigned long long ay = max[i];
			max[i] = max[j];
			max[j] = ay;

			i++;
			j--;
		}
	}while (i<j);

	if ( p<j ) QSort(p,j,s,v, max);
	if ( i<q ) QSort(i,q,s,v, max);
}


int main(void)
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt","w", stdout);


	int i, j, nrc, dim;

	for (i=0; i<=40; i++)
		C[i][0] = 1;

	for (i=1; i<=40; i++)
		for (j = 1; j<=i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];

	cin >> nrc;
	for (int c = 1; c<=nrc; c++)
	{
		cin >> n >> k;
		nr = 0;

		for (i = 0; i<n/2; i++)
			cin >> a[i];

		dim =0;
		for (i = n/2; i<n; i++)
		{
			cin >> b[dim];
			dim++;
		}

		if (k>n/2 && k < n-3 )
			k= n-k;

		if (k <= 2 || k > n)
			cout << "Case "<< c <<": "<<nr << endl;
		else
		{
			n = n/2;
			m = dim;

			dim1 = sume(s1, v1, a, max1, n);
			QSort(0, dim1-1, s1, v1, max1);

			dim2 = sume(s2, v2, b, max2, m);
			QSort(0, dim2-1, s2, v2, max2);

			h[0]= h[1] = 0;
			h[2]= m;
			for (i=3; i<=m; i++)
				h[i] = h[i-1] + C[m][i-1];		// cautare_binara(i, v2, h[i-1], dim2);
			h[m+1] = dim2;
			h[m+2] = 0;
				
			for (i=0; i < dim1 && v1[i]<k ; i++)
			{
				int x = k - v1[i];

 				for (j = h[x]; j < h[x+1]; j++)
				{
					P = (s1[i] + s2[j] +1)/2;

					if (max1[i] < P && max2[j] < P)
						nr++;
				}
			}

			for( ; i < dim1 && v1[i] == k; i++)
				if ( max1[i] < ( s1[i]+1 )/2 )
					nr++;

			for( j = h[k]; j<h[k+1]; j++)
				if ( max2[j] < ( s2[j]+1 )/2 )
					nr++;

			cout << "Case "<< c <<": "<<nr << endl;
		}
	}

	fcloseall();
	return 0;
}