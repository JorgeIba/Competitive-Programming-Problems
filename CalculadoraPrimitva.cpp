#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli dp[10000];


lli funcion(lli actual, lli target)
{
    if(actual > target)
    {
        return 1000000000000LL;
    }
    if(dp[actual] != -1)
    {
        return dp[actual];
    }
    if (actual == target)
    {
        return 0;
    }
    lli dos = funcion(actual*2, target) + 1;
    lli tres = funcion(actual*3, target) + 1;
    lli uno = funcion(actual + 1, target) + 1;

    return dp[actual] = min( min(dos, tres), uno   );

}

int main()
{
    memset(dp, -1, sizeof(dp));
    lli n; cin>>n;
    lli x = 1;
    cout<<funcion(x,n);
    return 0;
}