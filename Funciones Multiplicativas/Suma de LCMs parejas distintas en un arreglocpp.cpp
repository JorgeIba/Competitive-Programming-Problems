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
lli ans = 0;
for(int i = 0; i<n; i++)
{
    for(int j = i+1; j<n; j++)
    {
        ans += lcm(nums[i], nums[j]);
    }
}
cout << ans << endl;
*/

const lli MOD = 998244353;

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
    return (1-p+MOD)%MOD*binPow(aux, MOD-2)%MOD;
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
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1)%MOD;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p]%MOD;
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}


lli lcm(lli a, lli b)
{
    return (a*b) / (__gcd(a,b));
}

const int maxA = 1e6+5;

vector<lli> fr(maxA);
vector<lli> divs(maxA);
vector<lli> squares(maxA);

void prec(){
    for(lli d = 1; d<maxA; d++)
    {
        for(lli i = d; i<maxA; i+=d)
        {
            divs[d] = (divs[d] + (i*fr[i]%MOD))%MOD;
            squares[d] = (squares[d]+(i*i%MOD*fr[i]%MOD))%MOD;
        }
    }
}

lli inv2 = binPow(2, MOD-2);

int main () {
	//fastIO();
    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
        fr[x]++;
    } 
    prec();
    auto t = sieveMulFunction(maxA);
    
    lli ans = 0;
    for(lli d = 1; d<maxA; d++)
    {
        lli aux1 = divs[d]*divs[d]%MOD;
        aux1 -= squares[d];
        if(aux1 < 0) aux1+=MOD;
        ans += t[d]*aux1%MOD;
        if(ans >= MOD) ans -=MOD;
    }
    cout << ans*inv2%MOD << endl;
    
	return 0;
}