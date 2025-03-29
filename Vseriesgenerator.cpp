#include <iostream>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <algorithm>

using namespace std;
bool rosn(int a, int b)
{
    return a<b;
}
bool nierosn(int a, int b)
{

    return a>b;
}

int main()
{
    int n,k,t;
    int par[1000];
    int niepar[1000];
    int Vciag[2000];
    srand(time(NULL));

    cout << "podaj dlugosc" << endl;
    cin >> n;
    k = n/2;
    for(int i=0; i<k; i++)
    {
        t = rand()%1000+1;
        if(t%2==1)
        {
            t=t+1;
        }
        par[i] = t;
    }
    for(int i=0; i<n-k; i++)
    {
        t = rand()%1000+1;
        if(t%2==0)
        {
            t=t-1;
        }
        niepar[i] = t;
    }
    sort(par,par+k,rosn);
    sort(niepar,niepar+n-k,nierosn);
    for(int i= 0 ; i< k ; i++)
    {
        Vciag[i]=niepar[i];

    }
      for(int i= k ; i<n ; i++)
    {
        Vciag[i]=par[i-k];

    }
    for(int i = 0; i<n;i++)
    {
        cout << Vciag[i] << " ";
    }
    return 0;
}
