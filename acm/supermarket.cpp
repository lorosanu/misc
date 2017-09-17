#include <stdio.h>
#include <conio.h>

int p[10],d[10],x[10],xsol[10];
int n,prf,prfsol=0,k;

void print_sol(prfsol)
{
FILE *f;
f=fopen("output.out","wt");
fprintf(f,"%d",prfsol);
}

void evalSol(int n)
{
int i;
prf=0;
for (i=0;i<n;i++)
  if (x[i]!=0)
    prf+=p[i];
if (prf>prfsol)
  {
  for (i=0;i<n;i++)
    xsol[i]=x[i];
  prfsol=prf;
  }
}

int posibil(int k)
{
int i,dl;
  if (k==0)
    return 1;
  if (x[k]==0)
    return 1;
  dl=0;
  for (i=0;i<k;i++)
    if (x[i]==1)
      dl=dl+d[i];
  if (d[k]>=dl)
    return 1;
  return 0;
}

void BKT(int k)
{
  k=0;
  x[k]=-1;
  while (k>=0)
    if (x[k]<1)
      {
      x[k]=x[k]+1;
      if (posibil(k))
    if (k==n-1)
      evalSol(n);
    else
      {
        k=k+1;
        x[k]=-1;
      }
      }
    else
      k=k-1;
}

void main()
{
  FILE *f;
  int i,ok,aux;
  f=fopen("input.in","rt");
  fscanf(f,"%d",&n);
  for (i=0;i<n;i++)
    fscanf(f,"%d %d",&p[i],&d[i]);
  fclose(f);
  do
  {
    ok=1;
    for (i=0;i<n-1;i++)
      if (d[i]>d[i+1])
    {
      aux=d[i];
      d[i]=d[i+1];
      d[i+1]=aux;
      aux=p[i];
      p[i]=p[i+1];
      p[i+1]=aux;
      ok=0;
    }
  }
  while (ok==0);

  BKT(0);
  print_sol(prfsol);
}