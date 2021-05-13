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


VI sieveMulFunction(lli n)
{
    VI primes, lp(n+1), cnt(n+1), pot(n+1), miu(n+1);
    miu[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            miu[i] = -1;
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                miu[d] = -miu[i];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return miu;
}


int main () {
	//fastIO();
    lli n = (1LL<<50);

    lli ans = 0, m = sqrt(n);
    auto miu = sieveMulFunction(m);

    for(lli i = 1; i<=m; i++)
    {
        ans += miu[i]*(n / (i*i));
    }

    cout << ans << endl;
	return 0;
}