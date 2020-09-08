#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define MOD 1000000007

using namespace std;

string a, b;

lli dp[100010][15];

lli funcion(lli i, lli j) //i ->a, j->b
{
    if(j == b.size())
    {
        return 1;
    }
    if (i == a.size())
    {
        return 0;
    }

    if(dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if(a[i] == b[j])
    {
        lli si = funcion(i+1, j+1);
        lli no = funcion(i+1, j);
        return dp[i][j] = (si + no)%MOD;
    }

    else
    {
        return dp[i][j] = funcion(i+1, j)%MOD;
    }

}





int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>a>>b;
    cout<<(funcion(0,0)%MOD)<<endl;

    return 0;
}