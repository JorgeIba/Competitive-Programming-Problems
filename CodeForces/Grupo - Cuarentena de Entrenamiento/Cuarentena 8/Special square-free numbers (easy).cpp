#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MAXN = 3300000;
const lli INF = numeric_limits<int>::max();

vector<int> lowestPrime;
vector<int> primes;
vector<int> res(MAXN);

void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
    for(int i = 2; i<=n; i++)
    {
        if(lowestPrime[i] == i) primes.push_back(i);
    }
}


bool fact(lli n)
{
    lli ans = 0;
    lli prev = -1;
    lli x = n;
    while(x!=1)
    {
        lli lowest = lowestPrime[x];
        if(prev == lowest) 
        {
            return false;    
        }
        ans++;
        prev = lowest;
        x/=lowest;
    }
    if( ans % 2 == 0)
    {
        return true;
    } 
    return false;
}

void prec()
{
    for(int i = 2; i<MAXN-1; i++)
    {
        res[i] = fact(i);
    }
}

int main()
{
    fastIO();
    lowestPrimeSieve(MAXN);
    prec();
    lli n; cin>>n;
    lli counti = 0;
    for(int i = 0; i<MAXN-1; i++)
    {
        if(res[i]) counti++;
        if(counti == n) 
        {
            cout<<i<<endl;
            return 0;
        }
    }

    return 0;
}