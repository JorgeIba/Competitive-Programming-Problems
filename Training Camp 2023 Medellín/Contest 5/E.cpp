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



const int MOD = 1e9+7;


int main () {
	//fastIO();
	
    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    vector<int> next(n);
    stack< pair<int,int> > s; // {idx, num}
    for(int i = n-1; i >= 0; i--){
        auto num = nums[i];
        while(!s.empty() && num > s.top().second) {
            s.pop();
        }

        next[i] = (s.empty() ? -1 : s.top().first);
        s.push({i, num});
    }


    lli ans = 1;

    for(int i = 0; i < n; ){
        if(next[i] == -1) break;
        int range = next[i] - i + 1;
        ans = ans * range % MOD;
        i = next[i];
    }

    cout << ans << endl;



	return 0;
}

