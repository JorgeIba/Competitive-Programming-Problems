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
    for(int i = l1; i<=r1; i++)
    {
        for(int j = l2; j<=r2; j++)
        {
            ans += (gcd(i,j)==1);
        }
    }
*/

lli g(lli p, lli a)
{
    return (-1)*(a==1);
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


const int maxN = 1e7+1;

int main () {
	fastIO();
    auto miu = sieveMulFunction(maxN);
    lli a, b, c, d; cin>>a>>b>>c>>d;
    lli ans = 0;
    for(lli i = 1; i<=max(b, d); i++)
    {
        lli aux1 = (b/i) - (a-1)/i, aux2 = (d/i) - (c-1)/i;
        ans += miu[i]*aux1*aux2;
    }
    cout << ans << endl;

	return 0;
}