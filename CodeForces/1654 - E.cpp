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
#define fst first
#define snd second

using namespace std;

const int LIMIT = 1e5;
const int SQRT = 330;


int get_ans(const vector<int> &nums) {
    int n = SZ(nums);

    int ans_big = 0;
    for(int i = 0; i < n; i++) {
        vector<int> slopes;

        for(int j = i+1; j <= i+SQRT; j++) {
            if(j >= n) break;
        
            int delta_y = nums[j] - nums[i];
            int delta_x = j - i;

            if(delta_y % delta_x) continue;

            int slope = delta_y / delta_x;

            if(slope < SQRT) continue;

        
            slopes.push_back(slope);
        }

        sort(all(slopes));

        int cnt_before = 0, ans_i = 0;
        for(int j = 0; j < SZ(slopes); j++){
            if(j) {
                if(slopes[j-1] == slopes[j]) cnt_before++;
                else cnt_before = 1;
            } else {
                cnt_before = 1;
            }

            ans_i = max(ans_i, cnt_before);
        }
        ans_big = max(ans_big, ans_i + 1);
    }

    
    int ans_small = 0;
    for(int slope = 0; slope <= SQRT; slope++) {
        vector<int> consts;
        for(int i = 0; i < n; i++) {
            int c = nums[i] - i * slope;

            consts.push_back(c);
        }

        sort(all(consts));

        int cnt_before = 0, ans_i = 0;
        for(int j = 0; j < SZ(consts); j++){
            if(j) {
                if(consts[j-1] == consts[j]) cnt_before++;
                else cnt_before = 1;
            } else {
                cnt_before = 1;
            }

            ans_i = max(ans_i, cnt_before);
        }
        ans_small = max(ans_small, ans_i);
    }

    int ans = max({1, ans_small, ans_big});

    return ans;
}


int main () {
	fastIO();
    int n; cin>>n;
    
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    auto ans_1 = get_ans(nums);

    reverse(all(nums));

    auto ans_2 = get_ans(nums);

    auto ans = max(ans_1, ans_2);

    cout << n - ans << endl;

	return 0;
}