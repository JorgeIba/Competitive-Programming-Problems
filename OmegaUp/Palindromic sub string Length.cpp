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
string reversed;
bool isPrime[10010];

void sieve()
{
    isPrime[0] = isPrime[1] = true;
    for(int i = 4; i<=10000; i+=2 )
    {
        isPrime[i] = true;
    }
    for(lli i = 3; i*i <= 10000; i+=2)
    {
        if(!isPrime[i])
        {
            if(i * i <= 10000)
            {
                for(lli j = i*i; j<=10000; j+=2*i)
                {
                    isPrime[j] = true;
                }
            }
        }
    }
}

vector< vector< lli> > dp;



lli lcs(lli i, lli j)
{
    if(i>=s.length() or j>=s.length()) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == reversed[j] )
    {
        return lcs(i+1, j+1) + 1;
    }
    return dp[i][j]  = max( lcs(i+1, j), lcs(i, j+1));
}


void solve()
{   
    cin>>s;
    reversed = s;
    dp.assign(s.length(), vector<lli>(s.length(), -1));
    reverse(all(reversed));
    lli longest = lcs(0, 0);
    if(!isPrime[longest])
    {
        cout<<"PRIME\n";
    }
    else
    {
        cout<<"NOT PRIME\n";
    }
}



int main()
{
    sieve();
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }

    return 0;
}