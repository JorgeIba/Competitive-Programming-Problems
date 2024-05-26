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

const int LOG_D = 55;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) {
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++){
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

int main () {
	//fastIO();
	
    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    lli total = 0;
    for(auto x: nums)
        total ^= x;

    for(auto x: nums) insert_vector(x & (~total), true);

    auto get_best = [&](lli mask){
        lli ans = 0;
        forn(i, LOG_D){
                ans ^= basis[i];
        }
        return ans;
    };

    lli y = get_best(total);

    cout << y + (total^y) << endl;

	return 0;
}

