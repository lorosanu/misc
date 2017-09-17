#include <iostream.h>
#include <stdio.h>
#include <math.h>


double r;
int i, j, n, l, ok;
char c, s[10001];


int main(void)
{
	//freopen("in.txt","r", stdin);
	//freopen("out.txt","w",stdout);

	scanf("%d", &n);
	scanf("%c", &c);
	for (i=0;i<n; i++)
	{
		l=0;
		while (scanf("%c", &c) && c!= '\n')
		{
			if (c >= 'A' && c <= 'z')
				s[l++]= c;
		}
		s[l]='\0';
	
		cout << "Case #"<<i+1<<":"<< endl;
		r= sqrt(l);

		if (r != (int)r)
			cout <<"No magic :("<<endl;
		else
		{
			ok=1;
			for (j=0;j<l/2;j++)
				if (s[j]!= s[l-j-1])
				{
					ok=0;
					break;
				}
			if (ok==0)
				cout <<"No magic :("<<endl;
			else
				cout << r << endl;

		}
	}
			
	//fcloseall();
	return 0;
}