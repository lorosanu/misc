#include <iostream.h>
#include <cstdio>
#include <string.h>
#include <ctype.h>

int N,n,k[26];
int a[27][27];
char s[27][27][27], sir [27];
char sol[27][27];

void lower(char sir[27])
{    
	for (int i=0;i<strlen(sir);i++)        
		sir[i]=tolower(sir[i]);
}

int main()
{    
	int i, j, t , nr, v1, v2, nev;    
	//freopen("in.txt","r",stdin);    
	//freopen("out.txt","w",stdout);    
	cin>>N;    
	
	for(int p=0;p<N;p++)    
	{        
		cin>>n;        
		for (j=0;j<n;j++)
			for (t=0;t<n;t++)            
				a[j][t]=0;       
				for(i=0;i<n;i++)        
				{
					cin>>k[i];            
					for(j=0;j<k[i];j++)            
					{
						cin >> sir;
						if (toupper(sir[0]) <= (char)(65 + n) )                
						{                    
							t= (int) (toupper(sir[0])-65 );
							strcpy(s[i][t], sir);         
							a[i][t]=1;             	
						}          
					}       
				}        
				
				nev=n;     
				while (nev!=0)     
					for (j=0;j<n;j++)     
					{            
						v1= -1;     
						v2= -1;     
						nr = 0;     
						for (i=0;i<n;i++)   
						if (a[i][j] == 1)   
						{                   
							nr++;              
							v1 = i;                 
							v2 = j;                
						}            
						if (nr == 1)      
						{               
							nev--;         
							strcpy(sol[v2],s[v1][v2]);     
							for (i=0;i<n;i++)            
								a[v1][i]=0;   
						}      
					}     
				cout << "Case #" << p+1<< ":"<<endl;  
				for (i=0;i<n;i++)      
				{            
					lower(sol[i]);    
					sol[i][0]=toupper(sol[i][0]);    
					cout<<sol[i]<<endl;     
				}  
			}   
		//fcloseall();  
	return 0;
}

