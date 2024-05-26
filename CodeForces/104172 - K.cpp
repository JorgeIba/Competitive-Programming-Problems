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


int main () {
	//fastIO();
    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    nums.erase(unique(all(nums)), nums.end());

    lli mn = *min_element(all(nums));
    bool ok = true;
    for(auto x: nums){
        if(x == mn) continue;
        if(x < 2*mn) ok = false;
    }

    if(ok){
        cout << mn << endl;
        return 0;
    }


    lli min_ans = mn;
    for(auto x: nums){
        min_ans = min(min_ans, x / 2);
    }

    cout << min_ans << endl;




	return 0;
}

