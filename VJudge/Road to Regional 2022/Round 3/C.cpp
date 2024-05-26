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


int main () {
	//fastIO();
    
    lli n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    stack<lli> greater;

    vector<lli> ans(n);
    for(int i = n-1; i >= 0; i--) {
        auto num = nums[i];
        while(SZ(greater) > 0 && greater.top() <= num)
            greater.pop();

        if(greater.empty()) {
            ans[i] = -1;
        } else {
            ans[i] = greater.top();
        }

        greater.push(num);
    }


    for(auto x: ans) cout << x << " ";



	return 0;
}

