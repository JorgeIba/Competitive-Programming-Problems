#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

string s, t;
lli n, m;
vector< lli > pi;

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

vector< vector< lli > > dp;
vector< vector< lli > > aux;

lli fun(lli i, lli j)
{
    if(i==n)
    {
        if(j==m) return 1;
        else return 0;
    }
    lli &res = dp[i][j];
    if(res != -1) return res;

    if(j == m)
        res = 1;
    else
        res = 0;
    
    char curr = s[i];
    if(curr != '?')
    {
        lli q = j;
        while(q>0 && curr != t[q]) q = pi[q-1];
        if(curr == t[q]) q++;
        return res += fun(i+1, q);
    }
    else
    {
        lli ans = 0;
        for(char c= 'a'; c<='z'; c++)
        {
            lli q;
            if(aux[j][c-'a'] != -1)
            {
                ans = max(ans, fun(i+1, aux[j][c-'a']));
            }
            else
            {
                q = j;
                while(q>0 && c != t[q]) q = pi[q-1];
                if(c == t[q]) q++;
                aux[j][c-'a'] = q;
                lli aux = fun(i+1, q);
                ans = max(ans, aux);
            }
        }
        return res += ans;
    }
}


int main () {
	fastIO();
    cin>>s>>t;
    n = s.length(), m = t.length();
    pi = PrefixFunction(t);
    dp.assign(n+1, vector< lli >(m+1, -1));
    aux.assign(m+1, vector< lli >(28, -1));
    cout << fun(0,0) << endl;

	return 0;
}