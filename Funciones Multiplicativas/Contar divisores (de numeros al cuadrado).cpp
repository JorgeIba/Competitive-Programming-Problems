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

VI miu, sigma;

void sieveMulFunction(lli n)
{
    miu.resize(n+1);
    sigma.resize(n+1);
    VI primes, lp(n+1), cnt(n+1), pot(n+1);
    miu[1] = 1;
    sigma[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            miu[i] = -1;
            sigma[i] = (2);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                sigma[d] = sigma[ i/pot[i] ] * (cnt[i]+2);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                miu[d] = -miu[i];
                sigma[d] = sigma[i]*sigma[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
}

int limit = 5e7;
vector<lli> p_miu_2(limit), p_sigma(limit);
const lli maxN = 1e12+5;


unordered_map<lli,lli> dp_miu_2, dp_sigma;

lli get_p_miu_2(lli n)
{
    if(n < limit) return p_miu_2[n];
    if(dp_miu_2[n]) return dp_miu_2[n];

    lli ans = 0, m = sqrt(n);
    for(lli i = 1; i<=m; i++)
    {
        ans += miu[i]*(n / (i*i));
    }
    return dp_miu_2[n] = ans;
}


lli get_p_sigma(lli n)
{
    if(n < limit) return p_sigma[n];
    if(dp_sigma[n]) return dp_sigma[n];

    lli ans = 0;
    for(lli i = 1, r; i<=n; i = r+1)
    {
        r = n/(n/i);
        ans += (r - i + 1)*(n/i);
    }
    return dp_sigma[n] = ans;
}


int main () {
	fastIO();

    int t; cin>>t;
    
    if(t > 800) limit = 10000;
    sieveMulFunction(limit);

    for(lli i = 1; i<limit; i++)
    {
        p_sigma[i] = (p_sigma[i-1] + sigma[i]);
        p_miu_2[i] = (p_miu_2[i-1] + miu[i]*miu[i]);
    }

    while(t--)
    {
        lli n; cin>>n;

        lli ans = 0;

        for(lli i = 1, r; i<=n; i = r+1)
        {
            r = n/(n/i);
            ans += (get_p_miu_2(r) - get_p_miu_2(i-1)) * get_p_sigma(n/i);
        }
        
        cout << ans << endl;
    }

    
    
	return 0;
}