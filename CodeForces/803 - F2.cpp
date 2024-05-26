#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}



const int MOD = 1e9+7, maxA = 1e5+10;
int main () {
	//fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> freq(maxA);
    for(auto x: nums) freq[x]++;

    vector<int> subsets(maxA);
    for(lli g = maxA-1; g >= 1; g--) {
        lli multiples = 0, sub = 0;
        for(lli j = 1; j * g < maxA; j++){
            multiples += freq[j*g];

            sub += subsets[j*g];
            if(sub >= MOD) sub -= MOD;
        }
        
        subsets[g] = ((powerMod(2, multiples, MOD)-1) - sub + 2*MOD) % MOD;   
    }

    cout << subsets[1] << endl;



    


	return 0;
}

