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


//13
const lli maxN = 1e6+5;
const lli MOD = 998244353;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

int main () {
	//fastIO();
    prec();
    lli n; cin>>n;
    vector<lli>nums(n);
    for(int i = 1; i<=n; i++) nums[i-1] = i;


    lli ans = 0;
    for(int i = 0; i<=n; i++)
    {
        lli sz_perm = n - i;

        lli parejas = (fact[n]+MOD) % MOD;
        
        ans += (parejas - (parejas*invFact[sz_perm]))%MOD;
        if(ans >= MOD) ans -= MOD;
        else if(ans < 0) ans += MOD;
        //cout << parejas << " " << many_perm << " " << bloques << endl;
    }
    cout << (ans + 1)%MOD<< endl;
    
	return 0;
}