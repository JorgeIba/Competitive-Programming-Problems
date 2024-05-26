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

    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    lli max_abs = 0;
    for(auto x: nums) max_abs = max(max_abs, abs(x));

    if(max_abs == 0){
        cout << 0 << endl;
        return;
    } 

    int many_pos = 0, many_neg = 0;
    int idx_neg = 0, idx_pos = 0;
    forn(i, n){
        auto x = nums[i];
        if(x > 0) {
            many_pos++;
            if(x > nums[idx_pos])
                idx_pos = i;
        }
        else if(x < 0){
            many_neg++;
            if(x < nums[idx_neg])
                idx_neg = i;
        }
    }


    auto fix = [&](bool all_pos = true){
        vector< pair<int,int> > ans;
        if(all_pos){
            forr(i, 2, n){
                ans.push_back({i, i-1});
                nums[i-1] += nums[i-2];
            }
        } else {
            for(int i = n-1; i >= 1; i--){
                ans.push_back({i, i+1});
                nums[i-1] += nums[i];
            }
        }
        return ans;
    };


    if(many_neg == 0){
        auto ans = fix(true);
        cout << SZ(ans) << endl;
        for(auto [i, j]: ans) {
            cout << i << " " << j << endl;
        }
        return;
    } else if(many_pos == 0){
        auto ans = fix(false);
        cout << SZ(ans) << endl;
        for(auto [i, j]: ans) {
            cout << i << " " << j << endl;
        }

        return;
    }


    vector< pair<int,int> > ans;
    if(min(many_neg, many_pos) <= 7){
        if(many_neg  > many_pos){
            forn(i, 5) {
                ans.push_back({idx_neg+1, idx_neg+1});    
                nums[idx_neg] += nums[idx_neg];
            }

            forn(i, n){
                if(nums[i] > 0){
                    ans.push_back({i+1, idx_neg+1});
                    nums[i] += nums[idx_neg];
                }
            }

            auto ext = fix(false);
            for(auto move: ext) ans.push_back(move);
        } else {
            forn(i, 5) {
                ans.push_back({idx_pos+1, idx_pos+1});    
                nums[idx_pos] += nums[idx_pos];
            }

            forn(i, n){
                if(nums[i] < 0){
                    ans.push_back({i+1, idx_pos+1});
                    nums[i] += nums[idx_pos];
                }
            }

            auto ext = fix(true);
            for(auto move: ext) ans.push_back(move);
        }
    } else {
        if(-nums[idx_neg] > nums[idx_pos]){
            forn(i, n){
                if(nums[i] > 0){
                    ans.push_back({i+1, idx_neg+1});
                    nums[i] += nums[idx_neg];
                }
            }

            auto ext = fix(false);
            for(auto move: ext) ans.push_back(move);
        } else {
            forn(i, n){
                if(nums[i] < 0){
                    ans.push_back({i+1, idx_pos+1});
                    nums[i] += nums[idx_pos];
                }
            }

            auto ext = fix(true);
            for(auto move: ext) ans.push_back(move);
        }
    }

    cout << SZ(ans) << endl;
    for(auto [i, j]: ans) cout << i << " " << j << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

