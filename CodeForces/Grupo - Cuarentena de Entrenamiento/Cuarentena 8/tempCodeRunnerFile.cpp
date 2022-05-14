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

lli g(lli p, lli a)
{
    return -(a==1);
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

struct Prefix_F{

	typedef lli (*func) (lli);

	func p_f;
	lli limit, inv;
	unordered_map <lli, lli> dp;

	Prefix_F(func p_f, lli limit) : p_f (p_f), limit(limit) {}

	lli go(lli n) {
		if (n <= limit) return p_f (n);
		if (dp.count(n)) return dp[n];
		lli ans = 0;
		for (lli i = 2, r; i <= n; i = r + 1) {
			r = n / (n / i);
			ans += (r - i + 1)* go(n / i);
		}
        //assert(ans >= 0 && ans < MOD);
		ans = 1 - ans; ans = ans / inv;

		return dp[n] = ans;
	}

	lli get(lli n) {
		if (n <= 0) return 0;
		inv = 1;
		return go(n); 
	}
};


const lli maxN = 1e10+10;
const lli limit = pow(maxN, 2.0/3.0);
auto miu = sieveMulFunction(limit);
VLL p_miu_2(limit), p_miu(limit);

lli get_p_miu(lli n)
{
    return p_miu[n];
}

Prefix_F F(get_p_miu, limit);

lli get_p_miu_2(lli n)
{
    if(n < limit) return p_miu_2[n];
    lli m = sqrt(n);
    lli ans = 0;
    for(lli i = 1; i<=m; i++)
    {
        ans += miu[i] * (n/(i*i));
    }
    return ans;
}


lli counting(lli n)
{
    lli V = get_p_miu_2(n);
    lli U = F.get(n);
    return (V + U) / 2 - 1;
}

int main () {
	//fastIO();
    for(int i = 1; i<limit; i++)
    {
        p_miu_2[i] = p_miu_2[i-1] + miu[i]*miu[i];
        p_miu[i] = p_miu[i-1] + miu[i];
    } 

    lli k; cin>>k;

    lli l = 0, r = 1e11, ans = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( counting(mid) >= k)
        {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    } 
    
    cout << ans << endl;

    
	return 0;
}