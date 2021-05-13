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

vector<lli> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

set<lli> square_frees;


map<lli,lli> factorize_factorial(lli n)
{
    map<lli,lli> facts;
    for(auto p: primes)
    {
        if(p>n) break;
        lli curr = p;
        while(curr <= n)
        {
            facts[p] += (n / curr);
            curr *= p;
        }
    }
    return facts;
}

void process(lli n, lli k)
{
    auto facts_n = factorize_factorial(n);
    auto facts_k = factorize_factorial(k);
    auto facts_nk = factorize_factorial(n-k);

    for(auto pk: facts_k) facts_n[pk.first] -= pk.second;
    for(auto pk: facts_nk) facts_n[pk.first] -= pk.second;

    lli num = 1;
    bool sqfree = true;
    for(auto p: facts_n)
    {
        if(p.second > 1) sqfree = false;
        assert(p.second >= 0);
        num *= pow(p.first, p.second);
    }

    if(sqfree) square_frees.insert(num);
}

int main () {
	//fastIO();
    int n; cin>>n;

    for(int i = 1; i<n; i++)
        for(int j = 0; j<=i; j++)
            process(i, j);

    lli ans = 0;
    for(auto sqfree: square_frees) ans += sqfree;
    cout << ans << endl;

	return 0;
}