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
    return -1 * (a == 1);
}


vector<lli> lp;
//35
vector<lli> sieveMulFunction(lli n)
{
    vector<lli> primes, f(n+1), cnt(n+1), pot(n+1);
    lp.resize(n+1);
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


vector<lli> getDivs(vector<pair<lli,lli>> &factors)
{
    vector<lli> divs;
    int n = SZ(factors);

    int factors_count = 1;
    for (int i = 0; i < n; ++i)
    {
        factors_count *= 1+factors[i].second;
    }

    divs.resize(factors_count);
    divs[0] = 1;


    int count = 1;
    for (int stack_level = 0; stack_level < n; ++stack_level)
    {
        int count_so_far = count;
        int prime = factors[stack_level].first;
        int exponent = factors[stack_level].second;
        int multiplier = 1;
        for (int j = 0; j < exponent; ++j)
        {
            multiplier *= prime;
            for (int i = 0; i < count_so_far; ++i)
            {
                divs[count++] = divs[i] * multiplier;
            }
        }
    }
    return divs;
}


const lli maxN = 1e8;
vector<lli> miu = sieveMulFunction(maxN);

lli coprimesInRange(lli n, lli L, lli R)
{
    vector< pair<lli,lli> > factors;

    while(n > 1)
    {
        lli lowestPrime = lp[n];
        factors.push_back({lowestPrime, 1});
        while( n % lowestPrime == 0) 
            n/=lowestPrime;
    }

    lli ans = 0;

    auto divs = getDivs(factors);
    for(auto d: divs)
    {
        ans += miu[d] * (R / d - (L-1)/d);
    }
    return ans;
}


const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a*a % MOD;
    }
    return res;
}



int main () {
	//fastIO();

    time_t begin = clock();

    lli ans = 1;
    for(int i = 2; i<=maxN; i++)
    {
        lli howManyCoprimes = coprimesInRange(i, i, maxN);

        ans = ans * binPow(i, howManyCoprimes) % MOD;
    }

    cout << ans << endl;
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

