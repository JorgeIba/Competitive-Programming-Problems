#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

string s; 
lli n;

vector< vector< lli> > dp(5000, vector<lli>(3, -1));

lli funcion(lli i, lli estado) // 0 -> primera a, 1-> b, 2 -> segunda a
{
    if(i >= n) return 0;
    if(dp[i][estado] != -1)
    {
        return dp[i][estado];
    }
    char actual = s[i];

    switch(estado)
    {
        case 0:
            if(actual == 'b')
            {
                return dp[i][estado] = max(funcion(i+1, 0), funcion(i+1, 1)+1);
            }
            return dp[i][estado] = funcion(i+1, 0) + 1;
        case 1:
            if(actual == 'a')
            {
                return  dp[i][estado] = max(funcion(i+1, 1), funcion(i+1, 2) + 1) ;
            }
            return dp[i][estado] =  funcion(i+1, 1) + 1;
        case 2:
            if(actual == 'b')
            {
                return dp[i][estado] = funcion(i+1, 2);
            }
            return  dp[i][estado] = funcion(i+1, 2) + 1;
    }
}


int main()
{
    fastIO();
    cin>>s;
    n = s.length();
    cout<< funcion(0,0) <<endl;

    return 0;
}