#include <stdio.h>
#include <conio.h>

void main(void)
{
int i,n,j,k,p,x,nr;
FILE *f;
clrscr();
f=fopen("input.txt","rt");
while (!feof(f))
{
 nr=0;
 fscanf(f,"%d",&n);
 for (i=0;i<n;i++)
   {
    fscanf(f,"%d",&p);
    fscanf(f,":(%d)",&k);
    if (i==0&&k==1)
       nr--;
    if (k>0)
       nr++;
    for (j=0;j<k;j++)
       fscanf(f,"%d",&x);
   }
  printf("\nNumarul minim de soldati: %d",nr);
}
fclose(f);
getch();
}