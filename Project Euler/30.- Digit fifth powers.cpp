#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli sumDigits(lli n)
{
    lli sum = 0;
    while(n)
    {
        lli res = n % 10;
        n/=10;
        sum += res*res*res*res*res;
    }
    return sum;
}


int main()
{
    lli res = 0;
    for(int i = 2; i<=354294; i++)
    {
        if(sumDigits(i) == i)
        {
            res += i;
        }
    }
    cout<<res<<endl;
    return 0;
}