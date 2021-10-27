#include <bits/stdc++.h>

#define lli long long int
#define ld long double

using namespace std;


lli g(lli p, lli a)
{
    return a + 1;
}

lli maxN = 1e12;
const lli N = pow(maxN, 2.0/3.0);
vector<lli> miu(N+1,0), sigma(N+1,0);
vector<lli> prefix_sigma_v(N+1), prefix_miu_v(N+1);
//35
void sieveMulFunction(lli n)
{

    vector<lli> primes, lp(n+1), cnt(n+1), pot(n+1);
    sigma[1] = 1;
    miu[1] = 1;
    for(lli i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            sigma[i] = g(i,1);
            miu[i] = -1;
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                sigma[d] = sigma[ i/pot[i] ] * g(p,cnt[i]+1);
                miu[d] = 0;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                sigma[d] = sigma[i]*sigma[p];
                miu[d] = miu[i] * miu[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
}


lli prefix_sigma(lli n)
{
    if( n < N) return prefix_sigma_v[n];
    lli ans = 0;
    
    for(lli i = 1, r; i <= n; i = r+1)
    {
        r = n / (n/i);
        ans += (n/i) * (r - i + 1);
    }

    return ans;
}


lli prefix_miu(lli n)
{
    if(n < N) return prefix_miu_v[n];
    lli ans = 0;
    for(lli i = 1; i*i<=n; i++)
    {
        ans += miu[i] * (n / (i*i));
    }
    return ans;
}


int main () {
	//fastIO();
    time_t start = clock();

    sieveMulFunction(N+1);
    for(lli i = 1; i<=N; i++)
    {   
        prefix_sigma_v[i] = prefix_sigma_v[i-1] + sigma[i];
        prefix_miu_v[i] = prefix_miu_v[i-1] + abs(miu[i]);
    } 

    
    lli n; cin>>n;
    lli ans = 0;

    for(lli i = 1, r; i <= n; i = r+1)
    {
        r = n / (n/i);
        ans += prefix_miu(n/i) * ( prefix_sigma(r) - prefix_sigma(i-1) );
    }

    cout << (ans + n) / 2 << endl;
    

    time_t finish = clock();
    cout << (double) (finish - start)/CLOCKS_PER_SEC << endl;
	return 0;
}