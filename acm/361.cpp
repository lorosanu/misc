#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

struct Punct 
{
	int x, y;
};

double pi=3.14159265358979;

int nc, nr, no;
Punct c[210], r[210], o[210];
Punct solc[210], solr[210];
int nsolc, nsolr;

double dist(Punct P, Punct Q)
{
	double s = sqrt( (double)(P.x-Q.x)*(P.x-Q.x) + (P.y-Q.y)*(P.y-Q.y) );
	return s;
}

double determinant(Punct a, Punct b, Punct c)
{
	double s = a.x*b.y + a.y*c.x + b.x* c.y - c.x * b.y- a.y*b.x - c.y*a.x;
	return s;
}

double aria(Punct a, Punct b, Punct c)
{
	double s = determinant(a, b, c);
	return fabs(s)/2;
}

int sens_trigonometric(Punct P, Punct Q, Punct R)
{
	return determinant(P, Q, R) > 0 ?  1: 0;
}

double phi(Punct P)
{
	if(P.x==0)
	{
		if(P.y==0)
			return 0;
		else
			return pi/2;
	}
	else
		if (P.x > 0)
			return atan((double)P.y / (double)P.x);
		else
			return pi - atan(fabs((double)P.y / (double)P.x));
}

int compara(Punct P, Punct Q)
{
  double p1 = phi(P), p2 = phi(Q);

  if(fabs( p1 - p2 ) < 0.000001)
  {
	  double dp = P.x * P.x + P.y * P.y;
	  double dq = Q.x * Q.x + Q.y * Q.y;

	  if( fabs( dp - dq) < 0.00001)
		  return 0;
	  else
		  if( dp < dq)
			  return -1;
		  else
			  return 1;
  }
  else
	  if(p1 < p2)
		  return -1;
	  else
		  return 1;
}

void sorteaza(Punct P[],int p,int q)
{
	int i = p;
	int j = q;
	Punct Q;
	Q.x= P[(i+j)/2].x;
	Q.y= P[(i+j)/2].y;

	do
	{
		while(compara(P[i],Q)==-1)
			i++;
		while(compara(Q,P[j])==-1)
			j--;

		if(i<=j)
		{
			int aux=P[i].x;
			P[i].x=P[j].x;
			P[j].x=aux;

			aux=P[i].y;
			P[i].y=P[j].y;
			P[j].y=aux;
			i++;
			j--;
		}
	} while(i<j);

	if(p<j)
		sorteaza(P,p,j);
	if(i<q)
		sorteaza(P,i,q);
}

int infas(Punct P[], int n, Punct *sol)
{
	int i, j, nsol;

	Punct m = P[0];

	for (i = 1; i<n; i++)
		if(P[i].y < m.y || (P[i].y == m.y && P[i].x < m.x))
		{
			m.x=P[i].x;
			m.y=P[i].y;
		}

	for(i=0; i<n; i++)
	{
		P[i].x-= m.x;
		P[i].y-= m.y;
	}

	sorteaza(P, 0, n-1);

	sol[0] = P[0];
	nsol = 1;

	for (i=1; i<n; i++)
		if (nsol == 1)
			sol[nsol++] = P[i];
		else
		{
			while (sens_trigonometric(sol[nsol-2], sol[nsol-1], P[i]) == 0 && nsol> 1)
				nsol--;
			sol[nsol++]=P[i];
		}

	sol[nsol] = sol[0];
	nsol++;

	for(i=0; i<nsol; i++)
	{
		sol[i].x+= m.x;
		sol[i].y+= m.y;
	}

	for(i=0; i<n; i++)
	{
		P[i].x+= m.x;
		P[i].y+= m.y;
	}
	return nsol;
}

double ariapol(Punct P[],int n)
{
	double s=0;

	for(int i=0; i<n-1; i++)
		s+= P[i].x * P[i+1].y - P[i].y * P[i+1].x;

	return fabs(s)/2;
}

int pinp(Punct p, int n, Punct s[], double a)
{
	double ar=0;

	for(int i=0; i<n-1; i++)
		ar+= aria(p, s[i], s[i+1]);

	return fabs(ar-a) < 0.000001;
}

int main(void) 
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	int i, nrset=1;
	double ac, ar;

	while(cin>>nc>>nr>>no && nc+nr+no!=0)
	{
		for(i=0;i<nc;i++)
			cin >> c[i].x >> c[i].y;

		nsolc = infas(c, nc, solc);

		for(i=0;i<nr;i++)
			cin >> r[i].x >> r[i].y;

		nsolr = infas(r, nr, solr);

		cout<<"Data set "<<nrset<<":"<<endl;
		
		ac = ariapol(solc, nsolc);
		ar = ariapol(solr, nsolr);

		for(i=0;i<no;i++)
		{
			cin >> o[i].x >> o[i].y;

			int poz = 2;

			//verificare politisti  
			if(nsolc > 3 && pinp(o[i], nsolc, solc, ac))
				poz=0;
			else
			{
				if(nsolc < 4 && nc >= 3)
				{
					if(nsolc==2 && solc[0].x==o[i].x && solc[0].y==o[i].y)
						poz=0;
					else
					{
						if( fabs( dist(o[i], solc[0]) + dist(o[i], solc[1]) - dist(solc[0], solc[1]) ) < 0.000001 )
							poz=0;
					}
				}
			}

			//verificare hoti
			if(poz!=0)
			{
				if(nsolr > 3 && pinp(o[i], nsolr, solr, ar))
					poz=1;
				else
				{
					if(nsolr < 4 && nr >= 3)
					{
						if(nsolr==2 && solr[0].x==o[i].x && solr[0].y==o[i].y)
							poz=1;
						else
						{
							if( fabs( dist(o[i], solr[0]) + dist(o[i], solr[1]) - dist(solr[0], solr[1]) ) < 0.000001 )
								poz=1;
						}
					}
				}
			}


			if(poz == 0)
				cout << "     Citizen at (" << o[i].x << "," << o[i].y << ") is safe." <<endl;
			else 
				if(poz == 1)
					cout << "     Citizen at (" << o[i].x << "," << o[i].y << ") is robbed." << endl;
				else
					cout << "     Citizen at ("<< o[i].x << "," << o[i].y << ") is neither." << endl;
		}
		
	  cout << endl;
	  nrset++;
	}

	//fcloseall();
	return 0;
}
