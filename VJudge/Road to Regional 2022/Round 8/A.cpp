#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n, w; cin>>n>>w;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    vector<int> fr(3e6+10);

    for(int i = 0; i < n; i++){
        auto num_a = nums[i];
        for(int j = i+1; j < n; j++) {
            auto num_b = nums[j];
            for(int k = j+1; k < n; k++) {
                auto num_c = nums[k];
                fr[num_a + num_b + num_c]++;
            }
            fr[num_a + num_b]++;
        }
        fr[num_a]++;
    }

    lli ans = 0;
    for(int i = 1; i <= w; i++){
        ans += (fr[i] > 0);
    }

    cout << ans << endl;
    

}


int main () {
	fastIO();
	
	int t = 1; 
	// cin>>t;
	while(t--) 
		main_();


	return 0;
}

