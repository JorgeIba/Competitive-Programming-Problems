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
const lli maxN = 1e6;
const lli MOD = 1000000007;
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


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b>0)
    {
        if(b&1) res = (res*a)%MOD;
        b>>=1;
        a = (a*a)%MOD;
    }
    return res;
}


int main () {
	//fastIO();
    prec();
    lli n, k; cin>>n>>k;
    vector<lli> lightsOn(k);
    for(auto &x: lightsOn) cin>>x;
    sort(all(lightsOn));
    
    vector<lli> dist;
    lli currDist = 0;
    for(int i = 0; i<k; i++)
    {
        dist.push_back(lightsOn[i]-currDist-1);
        currDist = lightsOn[i];
    }
    dist.push_back(n-currDist);

    lli ans = fact[n-k];
    for(int i = 0; i<SZ(dist); i++)
    {
        ans = (ans*invFact[dist[i]])%MOD;
        if(i && i != SZ(dist)-1)
        {
            ans = (ans*(binPow(2, dist[i]-1)))%MOD;
        }
    }
    
    cout << ans << endl;


    
	return 0;
}