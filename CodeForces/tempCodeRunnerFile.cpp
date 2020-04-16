#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
lli n, h, l, r; 
vector<lli> hours;
 
lli dp[2010][2010];

bool check(lli num)
{
    num %= h;
    if ((num >= l) and (num <= r))
    {
        return true;
    }
    return false;
}


lli funcion(lli index, lli suma)
{
    if(index >= hours.size())
    {
        return 0;
    }
    if( dp[index][suma] != -1 )
    {
        return dp[index][suma];
    }
    lli si = 0, no = 0;
    if( check(suma+hours[index]) )
    {
        si = 1;
    }
    if( check(suma-1 + hours[index]) )
    {
        no = 1;
    }
    
    si += funcion(index+1, (suma+hours[index]) % h);
    no += funcion(index+1, (suma+hours[index]-1) % h);
    return dp[index][suma] = max(si,no);
}


int main()
{
    cin>>n>>h>>l>>r;
    memset(dp, -1, sizeof(dp));
    hours.resize(n);
    for(auto &x: hours)
    {
        cin>>x;
    }
    cout<<funcion(0,0)<<endl;
 
    return 0;
}