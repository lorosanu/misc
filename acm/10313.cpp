#include <iostream>
#include <cstdio>

using namespace std;

int n, l1, l2;
int sol;
unsigned long long int nr[310][310], suma;


int minim(int a, int b)
{
  if (a<b)
    return a;
  return b;
}



int main(void)
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);


  int i,j,k, p;
  char sir[40];

    
  for (i=1; i<=300;i++)
      nr[i][i]=1;

  //nr[i][j] = in cate moduri putem obtine valoarea j cu i monezi

  for (p=2; p<=300; p++)  // completam toata matricea pe rand pentru fiecare moneda de valoare p
  {
	  nr[1][p]=1;

	  for (i=1; i<=300; i++)
		  for (j=i;j<=300;j++)   
  		      if (nr[i][j] != 0)
			  {
			     if (p+j <=300)
			        nr[i+1][p+j]+=nr[i][j];
			  }
			  else
				 break;
  }
		

  while(gets(sir))
  {
		i=0;
		int dim = strlen(sir);
		n=0;
		while(i<dim && sir[i]!=' ')
		{
		  n=n*10+(sir[i]-'0');
		  i++;
		}
    
		while (sir[i]==' ')
			i++;

		if(i>=dim)
			l1=l2=-1;
		else
		{
			  l1=0;
			  while(i<dim && sir[i]!=' ')
			  {
				l1=l1*10+(sir[i]-'0');
				i++;
			  }
			  
			  while (sir[i]==' ')
					i++;

			  if(i>=dim)
			  {
				l2=-1;
			  }
			  else
			  {
				l2=0;
				while(i<dim && sir[i]!=' ')
				{
				  l2=l2*10+(sir[i]-'0');
				  i++;
				}
			  }
		}

		// cout<<n<<" "<<l1<<" "<<l2<<endl;
		    
		sol = -1;

		if (l2==-1)
		{
			  if (l1==-1)
			  {
				  	if (n==0)
					  sol = 1;
					else
					{
						l1=1;
						l2=n;
					}
			  }
			  else
			  {
				  if (n==0)
					  sol = 1;
				  else
				  {
					l2=minim(n,l1);
					if(n == 0 && l1 == 0 )
						 sol=1;
					else
						if (n>0 && l1 == 0)
							sol = 0;
					l1=1;
				  }
			  }
		}
		else
		{
			  if (l1 > n && l2 > n)
					sol=0;
		    
			  if (l1 <=n && l2 > n)
					l2=n;

			  if (n == 0 && l1+l2==0)
					sol=1;
		}


		if (sol == 0)
			  cout<< 0 << endl;
		else
			  if (sol == 1)
				  cout<< 1 << endl;
			  else
				  if (n>0 && l1+l2 ==0)
					  cout << 0 << endl;
				  else
				  {
						 suma=0;
						 for (i=l1; i<=l2; i++)
							 suma+=nr[i][n];
						 cout << suma << endl;
				  }
	}

  
  //fcloseall();
  return 0;
}