#include <bits/stdc++.h>

#define lli long long int
using namespace std;

lli evalK(lli k)
{
    return (pow(10, k)*(9*k -1) + 1) / 9;
}

lli solve(lli possition, lli maximPower)
{
    if(possition <= 9) return possition;
    lli l = 1, r = maximPower, k=-1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( evalK(mid)  <= possition )
        {
            k = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    lli lower = evalK(k);
    lli residue = possition - lower;
    lli power = pow(10, k);
    lli number = power + (residue / (k+1));
    if(residue%(k+1) == 0)
    {
        number--;
        return number % power;
    }
    else
    {
        string aux = to_string(number);
        return aux[residue%(k+1) - 1] - '0';
    }
}

int main()
{
    lli res = 1;
    const lli MAXPOWER = 6;
    for(int i = 0; i<=MAXPOWER; i++)
    {
        res = res * solve( pow(10, i) , MAXPOWER );
    }
    cout << res << endl;
    return 0;
}