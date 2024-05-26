#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


void solve(){
    
    int n, p; cin>>n>>p;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;
    reverse(all(nums));
    
    set<lli> marks(all(nums));
    
    if(SZ(marks) == p) {
        cout << 0 << endl;
        return;
    }

    lli gr = p-1, lo = 0;

    while(marks.count(gr)) gr--;
    while(marks.count(lo)) lo++;


    if(lo >= nums[0]) {
        cout << gr-nums[0] << endl;
        return;
    }

    lli ans = p - nums[0];
    lli before = nums[0];
    nums[0] = 0;
    lli carry = 1;
    for(int i = 1; i < n; i++) {
        nums[i] = (nums[i] + carry);
        carry = nums[i] / p;
        nums[i] %= p;
    }


    for(auto x: nums) marks.insert(x);
    if(carry) marks.insert(carry);

    if(SZ(marks) == p) {
        cout << ans << endl;
        return;
    }



    gr = before, lo = 0;

    while(marks.count(gr)) gr--;
    while(marks.count(lo)) lo++;

    assert(lo >= nums[0]);

    gr = max(0LL, gr);

    cout << gr + ans << endl;
}


int main () {
	fastIO();

    int t; cin>>t;
    while(t--) solve();

	return 0;
}
