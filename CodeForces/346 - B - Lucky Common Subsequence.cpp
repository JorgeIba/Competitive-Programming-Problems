#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> PrefixFunction(string &s)
{
    lli n = s.length();
    vector< lli > pi(n);
    pi[0] = 0;
    for(int i = 1; i<n; i++)
    {
        lli j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i]!=s[j]) pi[i] = 0;
        else pi[i] = j + 1;
    }
    return pi;
}

lli n, m, t;
vector< lli > pi;
const lli INF = 1e18;
string s1, s2, virus;

struct Nodo
{
    lli ans, i, j, k;
    bool letter = false;
    Nodo(lli ans, lli i, lli j, lli k): ans(ans), i(i), j(j), k(k) {}
    Nodo():ans(0), i(-1), j(-1), k(-1), letter(false) {}

    bool operator<(Nodo a) const
    {
        return ans < a.ans;
    }
    Nodo operator+(lli a)
    {
        return {ans+a, i, j, k};
    }
};

Nodo dp[110][110][110]; //dp[i][j][k] el LCS al haber procesado i letras de s1 y j de s2, con tamaño k de prefijo de virus
//lli dp[1005][1005];

int main () {
	fastIO();
    cin>>s1>>s2>>virus;
    n = s1.length(), m = s2.length(), t = virus.length();

    pi = PrefixFunction(virus);

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            for(int k = 0; k<t; k++)
            {
                if(s1[i] == s2[j])
                {
                    lli q = k;
                    while(q>0 && s1[i] != virus[q]) q = pi[q-1];
                    if(s1[i] == virus[q]) q++;
                    
                    if( dp[i+1][j+1][q] < (dp[i][j][k] + 1))
                    {
                        dp[i+1][j+1][q].ans = dp[i][j][k].ans + 1;
                        dp[i+1][j+1][q].i = i;
                        dp[i+1][j+1][q].j = j;
                        dp[i+1][j+1][q].k = k;
                        dp[i+1][j+1][q].letter = true;
                    }
                    
                    //dp[i+1][j+1][q] = max(dp[i+1][j+1][q],  dp[i][j][k] + 1);
                }
                dp[i+1][j+1][k] = max( {dp[i+1][j+1][k],  dp[i+1][j][k], dp[i][j+1][k]} );      
            }
        }
    }

    Nodo ans;
    for(int k = 0; k<t; k++)
    {
        ans = max(ans, dp[n][m][k]);
    }
    cerr << ans.ans << endl;
    if(ans.ans == 0) cout << 0 << endl;
    else
    {
        Nodo curr = ans;
        string s;
        while(curr.i != -1)
        {
            if(curr.letter)
            {
                s.push_back(s1[curr.i]);
            }
            curr = dp[curr.i][curr.j][curr.k];
        }
        reverse(all(s));
        cout << s << endl;
    }

	return 0;
}
