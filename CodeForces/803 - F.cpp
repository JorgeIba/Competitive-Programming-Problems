#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if( b & 1 ) res = res * a % mod;
         b >>= 1;
         a = a * a % mod;
    }
    return res;
}

const int maxN = 1e5+100, MOD = 1e9+7;

vector<int> muSieve(int n){
	vector<int> Mu(n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}


int main () {
	//fastIO();

    int n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    vector<int> freq(maxN);
    for(auto x: nums) freq[x]++;

    lli ans = powerMod(2, n, MOD) - 1;
    
    lli sub = 0;

    auto miu = muSieve(maxN);

    for(lli i = 2; i < maxN; i++){
        lli how_many = 0;
        for(lli j = 1; j*i < maxN; j++){
            how_many += freq[j*i];
        }
        
        sub = ( sub + miu[i] * (powerMod(2, how_many, MOD) - 1)) % MOD;
        if(sub < 0) sub += MOD;
        if(sub >= 0) sub -= MOD;
    }

    cout << (ans + sub + MOD) % MOD << endl;

	return 0;
}

