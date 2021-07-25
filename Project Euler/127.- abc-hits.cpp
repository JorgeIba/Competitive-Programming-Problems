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
    return p;
}


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



int main () {
	//fastIO();

    //lli n; cin>>n;
    lli n = 1e5+2e4;
    //lli n = 1e3;
    auto f = sieveMulFunction(n+10);

    lli sum = 0;
    for(int a = 1 ; a <= n; a++)
    {
        for(int b = a+1; a+b <= n; b++)
        {
            if(__gcd(a,b) == 1)
            {
                int c = a+b;
                sum += (c)*(f[a]*f[b]*f[c] < c);
            }
        }
    }
    
    cout << sum << endl;


	return 0;
}

