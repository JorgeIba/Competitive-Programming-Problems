#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli n; 
vector<lli> stones;

lli dp[100010];

lli funcion(lli index, lli suma)
{
    if(index >= n)
    {
        return 1000000000LL;
    }
    if(index == n-1)
    {
        return suma;
    }
    if(dp[index] != -1)
    {
        return dp[index];
    }
    

    lli uno = funcion(index + 1, suma+abs(stones[index] - stones[index+1]));
    lli dos = funcion(index + 2, suma+abs(stones[index] - stones[index+2]));

    return dp[index] =  min(uno,dos);
}


int main()
{
    memset(dp, -1, sizeof(dp));
    cin>>n;
    stones.resize(n);
    for(auto &x: stones)
    {
        cin>>x;
    }

    cout<<funcion(0, 0)<<endl;


    return 0;
}