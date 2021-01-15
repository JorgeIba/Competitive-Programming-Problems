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
typedef pair<lli,lli> PLL;
typedef vector<PLL> VPLL;
typedef vector<int> VI;

VPLL getFactors(lli n)
{
    VPLL factors;
    for(lli i = 2; i*i<=n; i++)
    {
        if(n % i == 0)
        {
            PLL a;
            a.first = i;
            while(n%i == 0)
            {
                a.second++;
                n/=i;
            }
            factors.push_back(a);
        }
    }
    if(n!= 1) factors.push_back({n, 1});
    return factors;
}


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a;
        b>>=1;
        a = a*a;
    }
    return res;
}

int main () {
	//fastIO();
    lli n, m; cin>>n>>m;
    
    auto divs = getFactors(m);
    lli gcd = 1;
    for(auto d: divs)
    {
        lli cabe = d.second / n;
        gcd *= binPow(d.first, cabe);
    }
    cout << gcd << endl;
	return 0;
}