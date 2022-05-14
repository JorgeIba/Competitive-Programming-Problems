#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;
 
string solve()
{
    string s, t = "facebook";
    cin>>s;
    int ss = s.length(), ts = t.length();
    vector< vector<int> > dp(ss+1, vector<int>(ts+1));
    //dp[i][j] -> lo mejor que se puede hacer con s de tama;o i y con t de tama;o j
    
    for(int i = 1; i <= ss; i++)
        for(int j = 1; j<= ts; j++)
        {
            if(s[i-1] == t[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                continue;
            }
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    
    if(dp[ss][ts] == ts) return "YES";
    else return "NO";
}


int main()
{
    fastIO();

    lli t; cin>>t;

    for(int i = 1; i <= t; i++)
    {
        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}



