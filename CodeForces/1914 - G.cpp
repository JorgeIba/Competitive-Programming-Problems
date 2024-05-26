#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int MOD = 998244353;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void main_(){
    int n; cin>>n;
    
    vector<lli> nums(2*n);
    vector<int> last_pos(n);

    forn(i, 2*n) {
        cin>>nums[i];
        nums[i]--;
        last_pos[nums[i]] = i;
    }

    vector<lli> value_hash(n);
    forn(i, n) value_hash[i] = rng();


    for(auto &x: nums){
        x = value_hash[x];
    }

    vector< int > prefix(2*n+1);

    map<lli,lli> hash_map;
    lli hash = 0;
    int last = 0;
    hash_map[0] = 0;
    vector< pair<int,int> > ranges;
    for(int i = 0; i < 2*n; i++) {
        hash ^= nums[i];
        
        if(hash_map.count(hash)) { // a range
            int idx_bef = hash_map[hash];
            if(last == idx_bef) {
                assert(hash == 0);
                // valid range
                ranges.push_back({last, i});
                last = i+1;
            } else {
                prefix[idx_bef]++;
                prefix[i+1]--;
            }
        }

        hash_map[hash] = i+1;
    }

    partial_sum(all(prefix), prefix.begin());

    auto cnt_segment = [&](int l, int r) {
        int alright = 0;
        for(int i = l; i <= r; i++) {
            if(prefix[i] == 0) {
                alright++;
            }
        }
        // cout << l << " -- " << r << " -> " << alright << endl;
        assert(alright % 2 == 0);
        return alright / 2;
    };


    pair<lli,lli> ans = {SZ(ranges), 1};
    for(auto [l, r]: ranges) {
        ans.second = ans.second * 2 * cnt_segment(l,r) % MOD;
    }

    cout << ans.first << " " << ans.second << endl;

}

int main () {
	// fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

