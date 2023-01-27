#include "maxsum.h"
#include <iostream>
using namespace std;

void print_array(int A[], int n)
{
    for (int i=0; i<n; i++)
        cout << A[i] << " ";
    cout << endl;
}

void maxsums::print()
{
    cout << "Sum of entire section of array " << endl << " ";
    entire.print();
    cout << "Starting at beginning index" << endl << "  ";
    begin.print();
    cout << "Ending at ending index" << endl << "  ";
    end.print();
    cout << "Starting and ending anywhere" << endl << "  ";
    best.print();
}

int sum_array(int A[], int lo, int hi)
{
    int sum = 0;
    for (int i=lo; i<=hi; i++)
        sum += A[i];
    return sum;
}

sol maxsol(sol s1, sol s2)
{
    if (s1.sum >= s2.sum)
        return s1;
    else
        return s2;
}

sol concat(sol s1, sol s2)
{
    sol s = sol(s1.lo,s2.hi,s1.sum+s2.sum);
    return s;
}

maxsums maxsum_slow(int A[], int n)
{
    maxsums m;
    m.entire = sol(0,n-1,sum_array(A,0,n-1));
    m.begin = sol(0,0,A[0]);
    for (int i=1; i<n; i++)
        m.begin = maxsol(m.begin,sol(0,i,sum_array(A,0,i)));
    m.end = sol(n-1,n-1,A[n-1]);
    for (int i=n-2; i>=0; i--)
        m.end = maxsol(m.end,sol(i,n-1,sum_array(A,i,n-1)));
    m.best = maxsol(m.begin,m.end);
    for (int i=1; i<n-1; i++)
        for (int j=i; j<n-1; j++)
            m.best = maxsol(m.best,sol(i,j,sum_array(A,i,j)));
    return m;
}

maxsums maxsum_fast(int A[], int start, int stop)
{
    maxsums m;
    if(start==stop){
        sol a(start,stop,A[start]);
        m.entire = m.begin = m.end = m.best = a;
        return m;
    }
    int mid = (start+stop)/2;
    maxsums first,second;
    first = maxsum_fast(A,start,mid);
    second = maxsum_fast(A,mid+1,stop);
    m.entire = concat(first.entire,second.entire);
    m.begin = maxsol(first.begin,concat(first.entire,second.begin));
    m.end = maxsol(second.end,concat(first.end,second.entire));
    m.best = maxsol(maxsol(first.best,second.best),concat(first.end,second.begin));
    return m;
}
