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


const int maxN = 70 + 5;
const int maxCount = 1e5 + 5;
const int MOD = 1e9+7;
const int cntPrimes = 19;
lli bucket[maxN+2];
lli masks[maxN + 2];
lli pows2[maxCount + 2];



void init()
{
    vector<bool> isPrime(maxN, true);
    int noPrime = 0;
    for(int i = 2; i <= maxN; i++)
    {
        if(isPrime[i])
        {  
            masks[i] ^= (1<<noPrime);
            for(int j = 2*i; j <= maxN; j += i)
            {
                isPrime[j] = false;
                int aux = j;
                while(aux % i == 0)
                {
                    masks[j] ^= (1<<noPrime);
                    aux /= i;
                }
            }
            noPrime++;
        }
    }

    pows2[0] = 1;
    for(int i = 1; i<maxCount; i++)
    {
        pows2[i] = pows2[i-1]*2 % MOD;
    }
    return;
}


int dp[maxN][(1<<cntPrimes) + 5];


int main () {
	fastIO();
    init();
    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums)
    {
        cin>>x; bucket[x]++;
    }

    dp[0][0] = 1;
    for(lli i = 0; i<=70; i++)
    {
        for(lli mask = 0; mask<(1<<cntPrimes); mask++)
        {
            if(bucket[i] >= 1)
            {
                dp[i+1][mask] = (dp[i+1][mask] +  (dp[i][mask] * pows2[bucket[i] - 1] % MOD))%MOD;
                dp[i+1][mask ^ masks[i]] =  (dp[i+1][mask ^ masks[i]] +  (dp[i][mask] * pows2[bucket[i] - 1] % MOD))%MOD;
            }
            else
            {
                dp[i+1][mask] = (dp[i+1][mask] +  dp[i][mask])%MOD;
            }
        }
        //cout << i << " " << endl;
    }
    cout << (dp[71][0] - 1 + MOD)%MOD << endl;

	return 0;
}