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


vector<int> fix(vector<int> ans, int k){
    // Si no tienes d00000dddd te conviene quitar los de hasta el final
    assert(SZ(ans) > 1);
    if(ans[1] != 0 || ans.back() == 0) {
        while(k) {
            ans.pop_back();
            k--;
        }
        return ans;
    }

    int n = SZ(ans);

    int how_many_zeros = 0;
    int idx = 1;
    while(idx < n && ans[idx] == 0) {
        idx++;
        how_many_zeros++;
    }

    assert(idx < n && ans[idx] != 0);

    // te toca quitar d0000
    bool quite = false;
    if(ans[0] > ans[idx] && k >= how_many_zeros + 1) {
        k -= how_many_zeros+1;
        quite = true;
    }

    while(k) {
        ans.pop_back();
        k--;
    }

    vector<int> total_ans;
    if(quite) {
        for(int i = how_many_zeros+1; i < SZ(ans); i++) {
            total_ans.push_back(ans[i]);
        }
    } else {
        total_ans = ans;
    }


    assert(k == 0);
    assert(!total_ans.empty());
    return total_ans;
}


void solve() {
    string s; cin>>s;
    int k; cin>>k;

    int n = SZ(s);

    vector<int> nums(n);
    for(int i = 0; i < n; i++) 
        nums[i] = s[i] - '0';

    vector<int> ans_num;
    queue<int> res_num;
    for(auto x: nums) res_num.push(x);

    auto is_valid_take_off = [&](int next_num) {
        if(SZ(ans_num) == 1 && next_num == 0) return false;
        return true;
    };

    while(!res_num.empty()) {
        auto next_num = res_num.front(); res_num.pop();

        while(!ans_num.empty() && ans_num.back() > next_num && k && is_valid_take_off(next_num)) {
            k--;
            ans_num.pop_back();
        }

        if(next_num != 0 && !ans_num.empty() && ans_num.back() == 0 && ans_num[0] > next_num && k >= SZ(ans_num)) {
            while(!ans_num.empty()) {
                ans_num.pop_back();
                k--;
            }
        }


        ans_num.push_back(next_num);
    }

    vector<int> ans = ans_num;

    if(k) { // Hay un digit + '0000' + sorted suffix
        ans = fix(ans, k);
    }

    for(auto x: ans) cout << x;
    cout << endl;
}


int main () {
	fastIO();
    int t; cin>>t;

    while(t--) solve();


	return 0;
}
