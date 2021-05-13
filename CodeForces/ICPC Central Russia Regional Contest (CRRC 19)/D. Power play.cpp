#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define LLI __int128
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

vector< pair<lli,lli> > factorize(lli n)
{
    vector< pair<lli,lli> > fact;
    for(lli i = 2; i*i<=n; i++)
    {
        if( n % i == 0)
        {
            lli pot = 0;
            while(n%i == 0)
            {
                pot++;
                n/=i;
            }
            fact.push_back({i, pot});
        }
        
    }
    if(n>1) fact.push_back({n,1});

    return fact;
}

VLL getDivisors(lli n)
{
    VLL divisors;
    for(lli i = 1; i*i<=n; i++)
    {
        if(n%i == 0)
        {
            divisors.push_back(i);
            if(i*i != n) divisors.push_back(n/i);
        }
    }
    return divisors;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b>>=1;
        a = a*a;
    }
    return res;
}

lli maxN = 1e18;
priority_queue< lli, vector<lli>, greater<lli> > ans;

bool is_in_range(lli n)
{
    return n>=1 && n<=maxN;
}

void find_multiples(lli a, lli b)
{
    lli upper = round( log(maxN) / log(a));
    for(LLI num = 1, cnt = 0; cnt <= upper+1; cnt++, num = num*a)
    {
        if(is_in_range(num) && num == b*cnt)
        {
            ans.push(num);
        }
    }
}


int main () {
	fastIO();
    lli a, b; cin>>a>>b;

    auto fact_a = factorize(a);

    lli gcd = 0;
    for(auto x: fact_a) gcd = __gcd(gcd, x.second);

    auto roots = getDivisors(gcd);
    for(auto d: roots)
    {
        lli num = 1;
        for(auto x: fact_a){
            num *= binPow(x.first, x.second / d);
        }
        if(b % d == 0)
            find_multiples(num, b/d);
    }

    if(ans.empty()) cout << 0 << endl;
    else cout << ans.top() << endl;

	return 0;
}