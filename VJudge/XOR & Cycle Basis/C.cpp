#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int LOG_D = 21;

struct XORBasis{
    vector<lli> basis;
    int sz_basis=0;

    XORBasis(): basis(LOG_D){}

    void insert_vector(lli mask, bool zeros = false){
        for(int i = LOG_D-1; i>=0; i--){
            if(!(mask & (1LL<<i))) continue;

            if(!basis[i]){
                basis[i] = mask;
                sz_basis++;
                if(!zeros) return;

                for(int j = 0; j<LOG_D; j++)
                {
                    if(j==i) continue;
                    if(j < i){
                        if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
                    }
                    else{
                        if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
                    }
                }
                return;
            }
            mask ^= basis[i];
        }
    }

};

const int MOD = 1e9+7;

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}



int main () {
	fastIO();

    int n, q; cin>>n>>q;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector< XORBasis > basiss(n);
    for(int i = 0; i < n; i++){
        if(i){
            basiss[i].basis = basiss[i-1].basis;
            basiss[i].sz_basis = basiss[i-1].sz_basis;
        }
        int x = nums[i];
        basiss[i].insert_vector(x, true);
    }


    while(q--){
        int l, x; cin>>l>>x; l--;

        int poss = 0;
        for(int i = 0; i < LOG_D; i++){
            if(x & (1 << i)){
                poss ^= basiss[l].basis[i];
            }
        }

        if(poss != x) {
            cout << 0 << endl;
            continue;
        }

        cout << powerMod(2, l+1 - basiss[l].sz_basis) << endl;
    }
    

	return 0;
}

