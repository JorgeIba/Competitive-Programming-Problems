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
	
    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    int min_temp = 1e9, idx_ans = 0;
    for(int i = 0; i < n-2; i++){
        int max_temp_i = max(nums[i], nums[i+2]);
        if(max_temp_i < min_temp){
            min_temp = max_temp_i;
            idx_ans = i+1;
        }
    }

    cout << idx_ans << " " << min_temp << endl;

	return 0;
}

