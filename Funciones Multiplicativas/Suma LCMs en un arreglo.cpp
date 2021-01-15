#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for (int i = a; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli MOD = 1e9+7;

/*
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            ans += lcm(a[i], a[j])%MOD;
        }
    }
*/


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a%MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}

lli g(lli p, lli a)
{
    lli aux = binPow(p, a);
    return ((1-p)*binPow(aux, MOD-2) % MOD + MOD) % MOD;
}

//35
vector<int> sieveMulFunction(lli n)
{
    vector<int> primes, lp(n+1), cnt(n+1), pot(n+1), f(n+1);
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
                f[d] = 1LL*f[ i/pot[i] ] * g(p,cnt[i]+1) % MOD;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = 1LL*f[i]*f[p] % MOD;
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}

const int maxN = 1e5+1;

auto t = sieveMulFunction(maxN);

int solve(){
    int n; cin>>n;
    map<int,int> freq;
    vector<int> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
        freq[x]++;
    } 
    vector<int> P(maxN);
    for(lli d = 1; d<maxN; d++)
    {
        lli sum = 0;
        for(lli i = 1; i*d<maxN; i++)
        {
            if(freq.count(i*d)) sum = (sum + ((((i*d)%MOD) * freq[i*d])%MOD))%MOD;
        }
        P[d] = sum;
    }
    lli ans = 0;
    for(int d = 1; d<maxN; d++)
    {
        ans += (1LL*t[d]*P[d]%MOD)*P[d]%MOD;
        if(ans >= MOD) ans-=MOD;
    }
    return ans;
}

int main()
{
    fastIO();
    freopen("lcm.in", "r", stdin);
    int t; cin>>t;
    while(t--)
    {
        cout << solve() << endl;
    }
    return 0;
}