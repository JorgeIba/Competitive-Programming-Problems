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

    bool pos = false;
    int idx = 0;
    for(int i = 0; i < n; i++){
        auto x = nums[i];
        if(x == max_abs){
            pos = true;
            idx = i;
        }
        if(pos == false && x == -max_abs){
            idx = i;
        }
    }

    vector< pair<int,int> > ans;
    if(!pos){
        forn(i, 3){
            ans.push_back({n, idx+1});
            nums[n-1] += nums[idx];
        }

        for(int i = n-1; i >= 1; i--){
            ans.push_back({i, i+1});
            ans.push_back({i, i+1});

            nums[i-1] += nums[i];
            nums[i-1] += nums[i];
        }

    } else {
        forn(i, 3){
            ans.push_back({1, idx+1});
            nums[0] += nums[idx];
        }

        for(int i = 2; i <= n; i++){
            ans.push_back({i, i-1});
            ans.push_back({i, i-1});

            nums[i-1] += nums[i-2];
            nums[i-1] += nums[i-2];
        }
    }


    cout << SZ(ans) << endl;
    for(auto [i, j]: ans){
        cout << i << " " << j << endl;
    }
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

