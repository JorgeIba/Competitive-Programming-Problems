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


int main()
{
    //fastIO();
    string s; cin>>s;
    vector< lli > pi = PrefixFunction(s);
    for(auto x: pi) cout << x << " ";

    
    return 0;
}