#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <iomanip>
#include <unistd.h>
//#include <bits/stdc++.h>

using namespace std;

int merge_counter;
time_t start, end_t;

void Merge(int *data, int const l, int const c, int const r)
{
    int const left_t = c - l + 1;
    int const right_t = r - c;

    int *left  = new int [left_t];
    int *right  = new int [right_t];

    for(int i = 0; i < left_t; i++)
    {
        left[i] = data[l+i];
    }
    for(int i = 0; i < right_t; i++)
    {
        right[i] = data[c+1+i];
    }

    int ix_l = 0;
    int ix_r = 0;
    int ix_d = l;

    while(ix_l < left_t && ix_r < right_t)
    {
        if(left[ix_l]<right[ix_r])
        {
            data[ix_d++] = right[ix_r++];
        }
        else
        {
            data[ix_d++] = left[ix_l++];
        }
    }
    while(ix_l < left_t)
    {
        data[ix_d++] = left[ix_l++];
    }
    while(ix_l < right_t)
    {
        data[ix_d++] = right[ix_r++];
    }

    delete[] left;
    delete[] right;
}

void Merge_sort(int *data, int l, int r)
{
    if(l>=r)
    {
        return;
    }
    int c = (l+r)/2;
    Merge_sort(data,l,c);
    Merge_sort(data,c+1,r);
    Merge(data,l,c,r);
    merge_counter++;
}

void Heap_gen(int *data, int n,int k)
{
        int ix_root = k;
        int big_kid;
        if((ix_root+1)*2-1 < n && (ix_root+1)*2 < n)
        {
           big_kid = min(data[(ix_root+1)*2-1],data[(ix_root+1)*2]);
        }
        else if((ix_root+1)*2-1 < n)
        {
            big_kid = data[(ix_root+1)*2-1];
        }
        else if((ix_root+1)*2 < n)
        {
            big_kid = data[(ix_root+1)*2];
        }
        while((ix_root+1)*2-1 < n && data[ix_root] > big_kid)
        {
            if((ix_root+1)*2-1 < n && (ix_root+1)*2 < n)
            {
                if(data[(ix_root+1)*2-1]<data[(ix_root+1)*2])
                {
                    swap(data[(ix_root+1)*2-1],data[ix_root]);
                    ix_root = (ix_root+1)*2-1;
                }
                else
                {
                    swap(data[(ix_root+1)*2],data[ix_root]);
                    ix_root = (ix_root+1)*2;
                }
            }
            else if((ix_root+1)*2-1 < n)
            {
                swap(data[(ix_root+1)*2-1],data[ix_root]);
                    ix_root = (ix_root+1)*2-1;
            }
            else if((ix_root+1)*2 < n)
            {
                swap(data[(ix_root+1)*2],data[ix_root]);
                    ix_root = (ix_root+1)*2;
            }

            if((ix_root+1)*2-1 < n && (ix_root+1)*2 < n)
            {
            big_kid = min(data[(ix_root+1)*2-1],data[(ix_root+1)*2]);
            }
            else if((ix_root+1)*2-1 < n)
            {
                big_kid = data[(ix_root+1)*2-1];
            }
            else if((ix_root+1)*2 < n)
            {
                big_kid = data[(ix_root+1)*2];
            }

        }
}

void Heap_sort(int *data, int n)
{
    for(int i = n/2; i >= 0; i--)
    {
        Heap_gen(data, n,i);
    }
    
    for(int i = n-1; i > 0; i--)
    {
        swap(data[0],data[i]);
        Heap_gen(data,i,0);
    }
}

void QS(int *data, int l, int r)
{
  if(r <= l) return;
	
	int i = l - 1;
    int j = r + 1;
	int pivot = data[r]; 
	
	while(1)
	{
		while(pivot<data[++i]);
		while(pivot>data[--j]);
		if( i <= j)
        {
            swap(data[i],data[j]);
        }	
		else
        {
            break;
        }
			
	}
	if(i > l)
    {
        QS(data, l, j);
    }	
	if(i+2 < r)
    {
        QS(data, i, r);
    }
	
}

void QSite(int *data, int l, int r)
{
    int stack[1000];
    int SP = -1;

    stack[++SP] = l;
    stack[++SP] = r;
    
    while(SP>=0)
    {
        r = stack[SP--];
        l = stack[SP--];
        
        int pivot = data[r]; 
        
        int i = (l - 1); 
    
        for (int j = l; j <= r - 1; j++) 
        { 
            if (data[j] >= pivot) 
            { 
                i++; 
                swap(data[i], data[j]); 
            } 
        } 
        swap(data[i + 1], data[r]); 
        
        if (i > l) 
        { 
            stack[++SP] = l; 
            stack[++SP] = i; 
        } 
  
        if (i + 2 < r) 
        { 
            stack[++SP] = i + 2; 
            stack[++SP] = r; 
        }
    }

}
void Insert_sort(int *data, int n, int j, int jump)
{
    for(int i = j; i < n; i=i+jump)
    {
        int pivot = data[i];
        int x = i-jump;
        while(x>=0 && pivot>data[x])
        {
            data[x+jump]=data[x];
            x = x - jump;
        }
        data[jump+x] = pivot;
    }
}

void Shell(int *data,int n)
{
    int k = floor(log(n+1)/log(2));
    cout << "k:" << k << endl; 
    int jump;
    for(int i = k; i >= 1; i--)
    {
        jump = pow(2,i) - 1;
        cout << "jump: " << jump << endl;
        for(int j = 0; j < jump; j++)
        {
            Insert_sort(data,n,j,jump);
        }
    }
}

bool rosn(int a, int b)
{
    return a<b;
}

bool nierosn(int a, int b)
{

    return a>b;
}

void dataV(int *data,int n)
{
    int k,t;
    int par[125000];
    int niepar[125000];
    srand(time(NULL));
    k = n/2;
    for(int i=0; i<k; i++)
    {
        t = rand()%(10*n)+1;
        if(t%2==1)
        {
            t=t+1;
        }
        par[i] = t;
    }
    for(int i=0; i<n-k; i++)
    {
        t = rand()%(10*n)+1;
        if(t%2==0)
        {
            t=t-1;
        }
        niepar[i] = t;
    }
    sort(par,par+k,nierosn);
    sort(niepar,niepar+n-k,rosn);
    for(int i= 0 ; i< k ; i++)
    {
        data[i]=par[i];

    }
      for(int i= k ; i<n ; i++)
    {
        data[i]=niepar[i-k];

    }
}

void dataA(int *data,int n)
{
    int k,t;
    int par[125000];
    int niepar[125000];
    srand(time(NULL));
    k = n/2;
    for(int i=0; i<k; i++)
    {
        t = rand()%(10*n)+1;
        if(t%2==1)
        {
            t=t+1;
        }
        par[i] = t;
    }
    for(int i=0; i<n-k; i++)
    {
        t = rand()%(10*n)+1;
        if(t%2==0)
        {
            t=t-1;
        }
        niepar[i] = t;
    }
    sort(par,par+k,nierosn);
    sort(niepar,niepar+n-k,rosn);
    for(int i= 0 ; i< k ; i++)
    {
        data[i]=niepar[i];

    }
      for(int i= k ; i<n ; i++)
    {
        data[i]=par[i-k];

    }
}

void data_random(int *data, int n)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        data[i] = rand()%(n*10)+1;
    }
}

void data_low(int *data, int n)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        data[i] = rand()%(n*10)+1;
    }
    sort(data,data+n,nierosn);
}

void data_high(int *data, int n)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        data[i] = rand()%(n*10)+1;
    }
    sort(data,data+n,rosn);
}

void printer(int *data, int n)
{
    for(int i=0; i<n; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

void algo_choice(int *data, int n)
{
    char choice;
    cout << "1: Shell sort" << endl;
    cout << "2: Quick sort " << endl;
    cout << "3: Quick sort iterative" << endl;
    cout << "4: Merge sort" << endl;
    cout << "5: Heap  sort" << endl;
    cin >> choice;
    start = clock();
    switch (choice)
    {
    case '1':
        Shell(data,n);
        break;
    case '2':
        QS(data,0,n-1);
        break;
    case '3':
        QSite(data,0,n-1);
        break;  
    case '4':
        merge_counter = 0;
        Merge_sort(data,0,n-1);
        cout <<"merge counter:"<< merge_counter<<endl;
        break;
    case '5':
        Heap_sort(data,n);
        break;
    default:
        break;
    }
    //sleep(1.5);
    end_t = clock();
    double time_taken = double(end_t - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

void wanna_print(int *data, int n)
{
    char choice;
    cout << "Print y or n" << endl;
    cin >> choice;
    switch (choice)
    {
    case 'y':
        printer(data,n);
        break;
    case 'n':
        break;
    default:
        break;
    }
    
}

void entering_n(int *data, int n)
{
    for(int i=0; i < n; i++)
        cin >> data[i];
}

void time_exe()
{
    time(&end_t);
    double time_taken = double(end_t - start);
    cout << "time ex: " << fixed << time_taken << setprecision(5); 
    cout << " sec " << endl; 
}

void random_gen_select(int *data, int n)
{
    char choice;
    cout << "1: V" << endl;
    cout << "2: A" << endl;
    cout << "3: random" << endl;
    cout << "4: >" << endl;
    cout << "5: <" << endl;
    cin >> choice;
    switch (choice)
    {
    case '1':
        dataV(data,n);
        break;
    case '2':
        dataA(data,n);
        break;
    case '3':
        data_random(data,n);
        break;
    case '4':     
        data_low(data,n);
        break;
    case '5': 
        data_high(data,n);
        break;  
    default:
        break;
    }
}

int main()
{
    int n;
    cout << "liczba n(250000): " << endl;
    cin >> n;
    //int data[518506];
    //limit to 518506 
    int data[250000];
    if(n<11)
    {
        entering_n(data,n);
    }
    else
    {
        random_gen_select(data,n);
    }
    //data_random(data,n);
    //dataV(data,n);
    //dataA(data,n);
    //Merge_sort(data,0,n-1);
    //wanna_print(data,n);
    printer(data, n);
    algo_choice(data,n);
    //wanna_print(data,n);
    //printer(data, n);
    //QS(data,0,n-1);
    //QSite(data,0,n-1);
    //Shell(data,n);
    printer(data, n);
    return 0;
}