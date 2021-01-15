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

const lli maxN = 1e6;
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

lli nCr(lli n, lli r)
{
    if(r < 0) return 0;
    return (((1LL*fact[n]*invFact[n-r])%MOD)*invFact[r])%MOD;
}


int main () {
	//fastIO();
	prec();
    lli n, X, A, B; cin>>n>>X>>A>>B;
    vector<lli> a(n);
    for(auto &x: a) cin>>x;
    
    for(int i = 0; i<n; i++)
    {
        X -= max(0LL, A-a[i]);
        a[i] += max(0LL, A-a[i]);
    }
    if(X < 0)
    {
        cout << 0 << endl; return 0;
    } 
    
    lli total = nCr(X + n - 1, X);
    
    for(int i = 0; i<n; i++)
    {
        X -= max(0LL, B-a[i]);
    }
    lli complemento = nCr(X + n - 1, X);

    total -= complemento;
    if(total < 0) total += MOD;
    cout << total << endl;
    
	return 0;
}