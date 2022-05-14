
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


int main () {
	//fastIO();
    string a = "acmicpc$acm$icpc$maratona";
    auto x = PrefixFunction(a);
    for(auto s: x) cout << s << " ";
	


	return 0;
}

