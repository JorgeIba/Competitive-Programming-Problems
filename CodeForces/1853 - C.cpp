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
    int n, k; cin>>n>>k;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    set<lli> nums_set(all(nums));

    auto get_idx = [&](lli idx){
        lli l = 1, r = 1e12, ans = r;

        while(l <= r){
            lli mid = (l+r)/2;

            lli new_idx = mid - (upper_bound(all(nums), mid) - nums.begin());

            if(new_idx == idx){
                if(nums_set.count(mid)){
                    r = mid-1;
                } else {
                    return mid;
                }
            } else if(new_idx < idx){
                l = mid+1;
            } else { // new_idx > idx
                r = mid-1;
            }
        }

        return ans;
    };

    lli ans = 1;
    for(int i = 0; i < k; i++){
        ans = get_idx(ans);
    }

    cout << ans << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

