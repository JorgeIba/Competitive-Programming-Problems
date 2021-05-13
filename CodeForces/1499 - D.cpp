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

VLL getDivisors(lli n)
{
    VLL divisors;
    for(lli i = 1; i*i <=n; i++)
    {
        if(n % i == 0)
        {
            divisors.push_back(i);
            if( i * i != n) divisors.push_back(n/i);
        }
    }
    return divisors;
}


//12
vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}


const int maxN = 2e7+10;

lli diff_primes(lli n)
{
    lli ans = 0;
    while(n > 1)
    {
        lli lp = lowestPrime[n];
        ans++;
        while(n % lp == 0)
        {
            n /= lp;
        }
    }
    return ans;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b>>=1;
        a*=a;
    }
    return res;
}


void solve()
{
    lli c, d, x; cin>>c>>d>>x;
    auto divs = getDivisors(x);
    lli ans = 0;
    for(auto div: divs)
    {
        lli xd = x / div;
        if((xd + d) % c != 0) continue;
        lli aux = (xd+d) / c;
        ans += binPow(2, diff_primes(aux));
    }
    cout << ans << endl;
}


int main () {
	//fastIO();
    lowestPrimeSieve(maxN);

    lli n; cin>>n;
    while(n--) solve();

	return 0;
}