#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void main_(){
    lli n, m; cin>>n>>m;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    lli first_mid = n/2;
    lli second_mid = n - first_mid;

    vector<lli> mask_first;
    for(lli mask = 0; mask < (1<<first_mid); mask++) {
        lli sum = 0;
        for(int j = 0; j < first_mid; j++) {
            if(mask & (1 << j))
                (sum += nums[j]) %= m;
        }
        mask_first.push_back(sum);
    }

    vector<lli> mask_second;
    for(lli mask = 0; mask < (1<<second_mid); mask++) {
        lli sum = 0;
        for(int j = 0; j < second_mid; j++) {
            if(mask & (1 << j))
                (sum += nums[j + first_mid]) %= m;
        }
        mask_second.push_back(sum);
    }

    sort(all(mask_second));


    // for(auto x: mask_first) cout << x << " ";
    // cout << endl;

    // for(auto x: mask_second) cout << x << " ";
    // cout << endl;


    lli best = 0;
    for(auto sum_first: mask_first) {
        lli best_looking = m - sum_first - 1;
        auto it = prev(upper_bound(all(mask_second), best_looking));

        lli sum_total = sum_first + *it;
        // cout << "SUM: " << sum_first << " " << *it << endl;
        assert(sum_total < m);
        best = max(best, sum_total);
        // cout << sum_first << " - " << *it << endl;
    }

    cout << best << endl;


}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

