#include <bits/stdc++.h>
#define lli long long int
#define end "\n"

using namespace std;

string a, b;


lli dp[5001][5001];

lli funcion(lli i, lli j) // i->a, j->b
{
    if((i == a.size())or(j == b.size()))
    {
        return 0;
    }

    if(dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if( a[i] == b[j] )
    {
        lli si = funcion(i+1, j+1) + 1;
        lli no = funcion(i, j+1);
        return dp[i][j] =  max(si,no);
    }
    else
    {
        lli seguir = funcion(i, j+1);
        lli noSeguir = funcion(i+1, j);
        return dp[i][j] = max(seguir, noSeguir);
    }

}



int main()
{  
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>a>>b;

    cout<<funcion(0,0)<<endl;

    return 0;
}