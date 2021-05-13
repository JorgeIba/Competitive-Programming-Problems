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
    vector<pair<lli,lli>> nums(n);
    int i = 1;
    for(auto &x: nums)
    {
        cin>>x.first; x.second = i++;
    }

    sort(all(nums));
    vector<lli> marquitas(n);

    for(int i = 0; i<n-1; i++)
    {
        marquitas[i+1] = nums[i].first;
    }

    vector<lli> sums(n);
    lli bolita = 0;
    for(int i = 0; i<n; i++)
    {
        bolita += marquitas[i];
        sums[i] = bolita;
    }

    /*
    for(auto x: nums) cout << x.first << " ";
    cout << endl;

    for(auto x: sums) cout << x << " ";
    cout << endl;
    */

    set<lli> winners;

    lli limit_to_win = nums[n-1].first;
    for(int i = n-1; i>=0; i--)
    {
        if(nums[i].first + sums[i] >= limit_to_win)
        {
            winners.insert(nums[i].second);
            limit_to_win = min(nums[i].first, limit_to_win);
        } 
        
    }

    
    cout << SZ(winners) << endl;
    for(auto x: winners) cout << x << " ";
    cout << endl;    

}

int main () {
	fastIO();
    int t; cin>>t;
    while(t--) solve();


	return 0;
}