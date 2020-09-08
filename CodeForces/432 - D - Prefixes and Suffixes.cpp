#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

vector< lli > PrefixFunction(string &s){
    lli n = s.length();
    vector< lli > pi(n);
    pi[0] = 0;
    for(int i = 1; i<n; i++)
    {
        lli j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}


int main () {
	fastIO();
    string s; cin>>s;
    lli n = s.length();
    vector< lli > pi = PrefixFunction(s);
    vector< lli > howMuch(n+1);
    for(int i = 0; i<n; i++)
    {
        howMuch[pi[i]]++;
    }
    vector< pair< lli, lli > > ans;
    for(int i = n; i>0; i--)
    {
        howMuch[pi[i-1]] += howMuch[i];
    }

    /*
    for(int i = 1; i<=n; i++) cout << howMuch[i] << " ";
    */

    lli j = pi[n-1];
    while(j>0)
    {
        if(howMuch[j])
        {
            ans.push_back({j, howMuch[j]});
        }
        j = pi[j-1];
    }

    sort(all(ans));
    cout << (SZ(ans)+1) << endl;
    for(auto x: ans)
    {
        cout << x.first << " " << x.second+1 << endl;
    }
    cout << n << " 1\n";


	return 0;
}