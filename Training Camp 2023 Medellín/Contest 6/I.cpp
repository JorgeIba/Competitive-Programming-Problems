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

int n; 

vector<int> get_gr_left(const vector<int> &nums){
    vector<int> ans(n+1);
    stack< pair<int,int> > s;

    for(int i = 1; i <= n; i++){
        auto x = nums[i];
        while(!s.empty() && x >= s.top().second) 
            s.pop();

        ans[i] = (s.empty() ? 0 : s.top().first);
        s.push({i, x});
    }

    return ans;
}
vector<int> get_gr_right(const vector<int> &nums){
    vector<int> ans(n+1);
    stack< pair<int,int> > s;

    for(int i = n; i >= 1; i--){
        auto x = nums[i];
        while(!s.empty() && x > s.top().second) 
            s.pop();

        ans[i] = (s.empty() ? n+1 : s.top().first);
        s.push({i, x});
    }

    return ans;
}


vector<int> get_lo_left(const vector<int> &nums){
    vector<int> ans(n+1);
    stack< pair<int,int> > s;

    for(int i = 1; i <= n; i++){
        auto x = nums[i];
        while(!s.empty() && x <= s.top().second) 
            s.pop();

        ans[i] = (s.empty() ? 0 : s.top().first);
        s.push({i, x});
    }

    return ans;
}
vector<int> get_lo_right(const vector<int> &nums){
        vector<int> ans(n+1);
    stack< pair<int,int> > s;

    for(int i = n; i >= 1; i--){
        auto x = nums[i];
        while(!s.empty() && x < s.top().second) 
            s.pop();

        ans[i] = (s.empty() ? n+1 : s.top().first);
        s.push({i, x});
    }

    return ans;
}



int main () {
	//fastIO();
    cin>>n;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];

    auto gr_left  = get_gr_left(nums);
    auto gr_right = get_gr_right(nums);

    auto lo_left = get_lo_left(nums);
    auto lo_right = get_lo_right(nums);


    lli ans = 0;

    forr(i, 1, n){
        int l_lower = lo_left[i];
        int r_lower = lo_right[i];

        int l_greater = gr_left[i];
        int r_greater = gr_right[i];

        // cout << i << " -> " << l_greater << " " << r_greater << endl;

        ans += 1LL*(i - l_greater) * (r_greater - i) * nums[i];
        ans -= 1LL*(i - l_lower)   * (r_lower - i) * nums[i];
    }

    cout << ans << endl;


	return 0;
}

