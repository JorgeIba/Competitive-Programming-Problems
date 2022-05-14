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


void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    if(nums[0] != n && nums[n-1] != n)
    {
        cout << -1 << endl;
        return;
    }

    deque<lli> dq;

    dq.push_back(n);

    lli i = 0, j = n-1;

    if(nums[0] == n) i++;
    else j--;

    while(i <= j)
    {
        dq.push_front(nums[i]);
        if(i != j)
            dq.push_back(nums[j]);
        i++, j--;
    }


    for(auto x: dq) cout << x << " ";
    cout << endl;


}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();

	


	return 0;
}

