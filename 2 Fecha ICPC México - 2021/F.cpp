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


const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
    lli res = 1; 
    while(b)
    {
        if(b & 1)
        {
            res = res * a % MOD;
        }
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}


lli g(lli p, lli a)
{
    return binPow(a, p);
}

//35
vector<lli> sieveMulFunction(lli n)
{
    vector<lli> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
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
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1) % MOD;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p] % MOD;
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}


int main () {
	//fastIO();
    const lli maxN = 5e7+10;

    vector<lli> ans(maxN+1), f = sieveMulFunction(maxN);
    for(int i = 1; i < maxN; i++)
    {
        ans[i] = (ans[i-1] + f[i]) % MOD;
    }

    lli n; cin>>n;

    cout << ans[n] << endl;


    

	


	return 0;
}

