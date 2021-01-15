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

/*
    O(n ln( ln(n) ) + t*n^(1/2))
    for(int i = 1; i<=a; i++)
    {
        for(int j = 1; j<=b; j++)
        {
            ans += isPrime[__gcd(i,j)];
        }
    }}
*/


lli g(lli p, lli a)
{
	return (-1)*(a == 1);
}
VLL lp, primes;
vector<lli> sieveMulFunction(lli n)
{
	lp.resize(n+1);
    vector<lli> f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}

const int maxN = 1e7+10;

auto miu = sieveMulFunction(maxN);

VLL getSumMiu(lli N)
{
	VLL sumMiu(N);
	for(auto p: primes)
	{
		for(lli i = 1; i*p<N; i++)
		{
			sumMiu[i*p] += miu[i];
		}
	}
	return sumMiu;
}

int main () {
	fastIO();
	//time_t begin = clock();
	auto sumMiu = getSumMiu(maxN);
	//cout << (double)(clock() - begin) / (CLOCKS_PER_SEC) << endl;

	VLL prefix(maxN);
	for(int i = 1; i<maxN; i++)
	{
		prefix[i] = prefix[i-1] + sumMiu[i];
	}

	lli t; cin>>t;
	while(t--)
	{
		lli a, b; cin>>a>>b;
		lli ans = 0;

		for(int n = 2, r; n<=min(a,b); n = r + 1)
		{
			lli la = a/n, ra = a/la;
			lli lb = b/n, rb = b/lb;
			r = min(ra, rb);

			ans += (a/n)*(b/n)*(prefix[r] - prefix[n-1]);
		}
		cout << ans << endl;
	}

	return 0;
}	