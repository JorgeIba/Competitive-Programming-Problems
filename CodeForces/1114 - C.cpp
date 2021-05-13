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

map<lli,lli> get_primes(lli n)
{
    map<lli,lli> primes;
    for(lli i = 2; i*i<=n; i++)
    {
        while( n % i == 0)
        {
            n /= i;
            primes[i]++;
        }
    }
    if( n > 1 ) primes[n]++;
    return primes;
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


const lli INF = 1e18;


lli get_cabe(lli n, lli p)
{
    __int128 k = p, aux, ans = 0;
    while (  (aux = n / k) > 0  )
    {
        ans += aux;
        k = k*p;
    }
    
    return ans;
}



int main () {
	//fastIO();

    lli n, b; cin>>n>>b;

    auto primes = get_primes(b);


    lli min_cabe = INF;
    for(auto p_e: primes)
    {
        lli cabe = get_cabe(n, p_e.first);
        min_cabe = min(min_cabe, cabe / p_e.second );
    }

    cout << min_cabe << endl;

	return 0;
}