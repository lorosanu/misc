#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

struct Punct
{
	double x;
	double y;
	double z;
};

char s[15];
Punct start, stop, v[20];
Punct p,q;
double R[20];
int n;


double dist(Punct a, Punct b)
{
	double s = sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	return s;
}

int ppd(Punct p, Punct a, Punct b)  //verificare punct P pe dreapta AB
{

	double d1 = dist(p, a);
	double d2 = dist(p, b);
	double d3 = dist(a, b);

	if ( fabs(d3 - d1 - d2) < 0.00001)
		return 1;
	else
		return 0;
}

int punct_in_sfera(Punct P, Punct v, double R)  //verificare punct P in sfera de centru v si raza R
{
	double a = (P.x - v.x) * (P.x - v.x) + (P.y - v.y)*(P.y - v.y) + (P.z - v.z ) *(P.z - v.z);
	if ( a < R * R)
		return 1;
	else
		return 0;
}

int main(void)
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt","w", stdout);
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);


	int i;
	Punct zero;
	zero.x = 0; zero.y = 0; zero.z = 0;

	double rez = 0;

	while (cin >> s)
	{
		cin >> start.x >> start.y >> start.z;
		cin >> stop.x >> stop.y >> stop.z;

		double a = stop.x - start.x;
		double b = stop.y - start.y;
		double c = stop.z - start.z;
		
		double A = a*a + b*b + c*c;
		double suma = 0;
		double H = dist(start, stop);
		rez = 0;

		cin >> n;
		for (i=0;i<n;i++)
		{
			cin >> v[i].x >> v[i].y >> v[i].z;
			cin >> R[i];

			double B = 2* ( a*(start.x - v[i].x) + b*(start.y - v[i].y) + c*(start.z - v[i].z));
			double D = v[i].x * v[i].x + v[i].y * v[i].y + v[i].z * v[i].z - R[i] * R[i];
			double C = start.x * start.x + start.y * start.y + start.z * start.z - 2*v[i].x * start.x - 2*v[i].y * start.y - 2*v[i].z * start.z + D;

			double delta = B*B - 4*A*C;			

			if (delta > 0)
			{
				double t1 = (-B - sqrt(delta) )/ (2*A);
				double t2 = (-B + sqrt(delta)) / (2*A);
				p = zero;
				q = zero;

				double x1 = a * t1 + start.x;
				double y1 = b * t1 + start.y;
				double z1 = c * t1 + start.z;
				
				p.x = x1; 
				p.y = y1; 
				p.z = z1;

				x1 = a * t2 + start.x;
				y1 = b * t2 + start.y;
				z1 = c * t2 + start.z;
				
				q.x = x1; 
				q.y = y1; 
				q.z = z1;
				// Punctele P si Q vor fi punctele de intersectie dintre dreapta (start, stop) si sfera curenta

				if ( ppd(p, start, stop) && ppd(q, start, stop) )
						suma += dist(p, q);
				else
					if (punct_in_sfera(start, v[i], R[i]))
					{
						if (punct_in_sfera(stop, v[i], R[i]))
							rez = 100;					
						else
						{
							if (ppd (p, start, stop))
								suma+=dist(start, p);
							else
								if (ppd(q, start, stop))
									suma+=dist(start, q);
						}
					}
					else
					{
						if (punct_in_sfera(stop, v[i], R[i]))
						{
							if (ppd (p, start, stop))
								suma+=dist(stop, p);
							else
								if (ppd(q, start, stop))
									suma+=dist(p, stop);
						}
					}
			}
		}	
		cout << s << endl;
		if (rez == 100)
			cout << rez << endl;
		else
			cout << suma/H * 100 << endl;
	}

	//fcloseall();
	return 0;
}