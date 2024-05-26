#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;



int main () {
	//fastIO();
	
    int n, h; cin>>n>>h;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> original = nums;

    sort(all(nums));


    auto print_with_min_changed = [&]() {
        bool yet = true;
        for(int i = 0; i < n; i++){
            if(original[i] == nums[0] && yet) {
                cout << 2 << " ";
                yet = false;
            } else {
                cout << 1 << " ";
            }
        }
        cout << endl;
    };


    if(n == 2) {
        cout << 0 << endl;
        cout << "1 1" << endl;

    } else {
        lli ans_1 = (nums[n-1] + nums[n-2]) - (nums[0] + nums[1]);

        lli max_part = max( nums[n-1] + nums[n-2], nums[n-1] + nums[0] + h  );
        lli min_part = min(  nums[1] + nums[2], nums[0] + nums[1] + h );
        lli ans_2 = (max_part) - (min_part);

        if(ans_1 < ans_2) {
            cout << ans_1 << endl;
            for(int i = 0; i < n; i++) cout << 1 << " ";
            cout << endl;
        } else {
            cout << ans_2 << endl;
            print_with_min_changed();
        }

    }


	return 0;
}

