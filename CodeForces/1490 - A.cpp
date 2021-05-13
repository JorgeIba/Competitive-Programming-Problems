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

lli get_diff(lli num1, lli num2)
{
    if(num2 < num1) swap(num1, num2);

    int curr = num1;
    int i = 0;
    for(i = 0; 2*curr < num2; i++)
    {
        curr = 2*curr;
    } 
    return i;
}


void solve()
{
    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    int ans = 0;
    for(int i = 0; i<n-1; i++)
    {
        ans += get_diff(nums[i], nums[i+1]);
    }
    cout << ans << endl;

}



int main () {
	fastIO();
    int t; cin>>t;

    //get_diff(2, 10);

    while(t--) solve();

	return 0;
}