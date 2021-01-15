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
            for(int k = j+1; k<n; k++)
            {
                for(int d = 1; d<=MAX; d++)
                {
                    ans += (__gcd(a[i],a[j],a[k]) == 1);
                }
            }
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

const int maxN = 1e5+5;
const int maxA = 1e6+5;

vector<lli> fr(maxA);
vector<lli> howManyDiv(maxA);

void prec()
{
    for(int d = 1; d < maxA; d++)
    {
        for(int i = d; i < maxA; i+=d)
        {
            howManyDiv[d] += fr[i];
        }
    }
}


lli nC3(lli n)
{
    return (n*(n-1)*(n-2))/6;
}

int main () {
	//fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x; 
        fr[x]++;
    }
    auto miu = sieveMulFunction(maxA);
    prec();
    lli ans = 0;
    for(int d = 1; d<maxA; d++)
    {
        ans += miu[d]*nC3(howManyDiv[d]);
    }
    cout << ans << endl;

    
	return 0;
}