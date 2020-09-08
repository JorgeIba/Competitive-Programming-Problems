#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

string s, t;
lli n, q;

vector< vector< lli > > dp(3010, vector<lli>(3010, -1));

lli LCS(lli i, lli j)
{
    if(i >= n || j >=q) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == t[j])
    {
        return dp[i][j] = LCS(i+1, j+1) + 1;
    }
    return dp[i][j] = max(LCS(i+1, j), LCS(i, j+1));
}

void rec(lli i, lli j, string &word)
{
    if(i >= n || j >=q) return;

    if(s[i] == t[j])
    {
        word.push_back(s[i]);
        rec(i+1, j+1, word);
        return;
    }
    if(dp[i+1][j] > dp[i][j+1])
    {
        rec(i+1, j, word);
    }
    else
    {
        rec(i, j+1, word);
    }
    return;
}

int main()
{
    fastIO();
    cin>>s>>t;
    n = s.length();
    q = t.length();
    string res;
    LCS(0,0);
    //cout << LCS(0,0) <<endl;
    rec(0,0, res);
    cout << res << endl;


    return 0;
}