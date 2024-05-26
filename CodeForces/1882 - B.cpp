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


void main_(){
    int n; cin>>n;
    vector< lli > nums(n);


    lli all_union = 0;
    forn(i, n){
        int k; cin>>k;
        lli msk = 0;
        forn(j, k){
            int x; cin>>x;
            msk |= (1LL << x);
        }
        nums[i] = msk;
        all_union |= msk;
    }

    lli ans = 0;
    for(int i = 0; i < 55; i++){
        lli ans_i = 0;
        forn(j, n){
            auto msk_j = nums[j];
            if(msk_j & (1LL << i)) continue;

            ans_i |= msk_j;
        }

        // cout << bitset<10>(ans_i).to_string() << " " << bitset<10>(all_union).to_string() << " " << (lli) __builtin_popcountll(ans_i) << endl;
        if(ans_i != all_union)
            ans = max(ans, (lli) __builtin_popcountll(ans_i));
    }

    // debugg(ans);
    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

