#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const int maxN = 14;
const lli INF = 1e9;

vector<lli> nums(maxN+1);

lli dp[maxN+1][35][maxN+1];

lli f(int idx, int taken, int col, const int total_cols) {
    if(idx == 0){
        return 0;
        // return total_cols - col + 1;
    }

    if(col == total_cols+1) return 0;
    if(col > total_cols+1) return -INF;
    

    lli &ans = dp[idx][taken][col];
    if(ans != -1) return ans;

    int group_available = nums[idx] - taken;
    assert(group_available >= 0);
    
    if(group_available > 0) {

        int take = 0, not_take = 0;

        if(col + idx == total_cols+1) {
            take = 1 + f(idx, taken+1, col + idx, total_cols);
        } else {
            take = 1 + f(idx, taken+1, col + (idx + 1), total_cols);
        }

        not_take = f(idx-1, 0, col, total_cols);

        return ans = max(take, not_take);
    } else {
        return ans = f(idx-1, 0, col, total_cols);
    }
}



void rec_f(int idx, int taken, int col, const int total_cols, vector<int> &ans_rec) {
    if(idx == 0){
        return;
    }

    if(col == total_cols+1) return;
    if(col > total_cols+1) return;
    
    lli ans = f(idx, taken, col, total_cols);

    int group_available = nums[idx] - taken;
    assert(group_available >= 0);
    
    if(group_available > 0) {

        int take = 0, not_take = 0;

        if(col + idx == total_cols+1) {
            take = 1 + f(idx, taken+1, col + idx, total_cols);
        } else {
            take = 1 + f(idx, taken+1, col + (idx + 1), total_cols);
        }

        not_take = f(idx-1, 0, col, total_cols);

        if(take == ans) {

            ans_rec.push_back(idx);

            if(col + idx == total_cols+1) {
                rec_f(idx, taken+1, col + idx, total_cols, ans_rec);
            } else {
                rec_f(idx, taken+1, col + idx + 1, total_cols, ans_rec);
            }
        } else {
            assert(ans == not_take);
            rec_f(idx-1, 0, col, total_cols, ans_rec);
        }

        return;
    } else {
        rec_f(idx-1, 0, col, total_cols, ans_rec);
        return;
    }
}



int main () {
	//fastIO();

    int n; cin>>n;

    for(int i = 1; i <= n; i++) cin>>nums[i];

    auto check_empty = [&]() {
        for(int i = 1; i <= maxN; i++) {
            if(nums[i]) return false;
        }
        return true;
    };

    int row = 1;
    for(; row <= maxN; row++){

        memset(dp, -1, sizeof(dp));
        f(12, 0, 1, row);


        vector<int> ans;
        rec_f(12, 0, 1, row, ans);

        for(auto x: ans) nums[x]--;

        if(check_empty()) {
            if(row <= 12) {
                cout << row << endl;
            } else {
                cout << "impossible" << endl;
            }
            return 0;
        }
    }


	return 0;
}

