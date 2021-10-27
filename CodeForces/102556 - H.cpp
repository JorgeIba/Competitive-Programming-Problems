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


map<lli,lli> get_facts(lli n)
{
    map<lli,lli> facts;
    for(lli i = 2; i*i <= n; i++)
    {
        while( n % i == 0)
        {
            facts[i]++;
            n /= i;
        }
    }
    if(n>1) facts[n]++;
    
    return facts;
}


vector<lli> get_divs(lli n)
{
    vector<lli> divs;
    for(lli i = 1; i*i <= n; i++)
    {
        if( n % i == 0)
        {
            divs.push_back(i);
            if(i*i != n) divs.push_back(n/i);
        }
    }
    return divs;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b>>=1;
        a = a * a;
    }
    return res;
}


int main () {
	fastIO();
    lli m; cin>>m;
    
    auto facts = get_facts(m);

    lli gcd = 0;
    for(auto pe: facts)
        gcd = __gcd(gcd, 2*pe.second);

    auto divs = get_divs(gcd);

    lli ans = m == 1? 1: -1;
    for(auto d: divs)
    {
        lli n = 1, fn = 1;
        for(auto pe: facts)
        {
            lli e = 2*pe.second / d;
            n *= binPow(pe.first, e);
            fn *= (e+1);
        }

        if( fn == d )
            ans = n;
    }

    cout << ans << endl;


	return 0;
}