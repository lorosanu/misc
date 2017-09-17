#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

double PI = 3.14159265358979323846264338327950288;


double R, n;

double dist(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));
}

double Aria(double a, double b, double c)
{
	double p = (a+b+c)/2;
	double ar= sqrt ( p * (p-a) * (p-b) * (p-c));
	return ar;
}

int main(void)
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w", stdout);

	double alfa;
	double x0,y0,x1,y1;
	double coss, sinn;
	double aria;

	while (scanf("%lf %lf", &R, &n)==2)
	{
		x0= R; y0 = 0;
		alfa = (2 * PI)/n;
		coss = cos(alfa);
		sinn = sin(alfa);
		x1 = R * coss;
		y1 = R * sinn;

		double l = dist (x0, y0, x1, y1);
		aria = Aria(l, R, R);
		aria*=n;
		printf("%.3lf\n", aria);
	}

	//fcloseall();
	return 0;
}