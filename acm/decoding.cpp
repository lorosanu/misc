#include <iostream.h>
#include <stdio.h>

int i, n, j, k, ok;
char c;


int main(void)
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w", stdout);

	scanf("%d", &n);
	scanf("%c", &c);
	scanf("%c", &c);

	for (i=0;i<n;i++)
	{
		cout << "Case #"<<i+1<<":";
		ok=0;
		j=0; 
		k=1;
		while (ok ==0)
		{
			ok=1;
			cout << endl;
			while (scanf("%c", &c) && c!= '\n')
			{
				j=j+1;
				if (c == ' ')
					j=0;
				if (j == k)
				{
					cout << c;
					k=k+1;
					j=k+1;
				}
				ok=0;
			}

			k=1;
			j=0;
		}

		if (i< n-1)
			cout << endl;
	}


	//fcloseall();
	return 0;
}