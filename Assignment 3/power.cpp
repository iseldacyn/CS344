#include "power.h"

long double power_iter(double x, int n)
{
    double x_n = 1;
    for(int i=0; i<n; i++){
        x_n *= x;
    }
    return x_n;
}

long double power_rec(double x, int n)
{
    if(n==0) return 1;
    else return x*power_rec(x,n-1);
}

long double power_half(double x, int n)
{
    if(n==0) return 1;
    else if(n%2==1) return x*power_half(x,n/2)*power_half(x,n/2);
    else return power_half(x,n/2)*power_half(x,n/2);
}

