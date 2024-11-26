#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int INF = 1e9 + 10;
int main () {
	// fastIO();

    int n, m, d; cin>>n>>m>>d;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    map<int,int> index;
    forn(i, n)
        index[nums[i]] = i;

    vector<int> ans(n);
    set<int> mins(all(nums));

    int day = 1;
    int last_minute = -INF;
    while(!mins.empty()) {
        auto itr = mins.lower_bound(last_minute);
        if(itr == mins.end()) {
            day++;
            last_minute = -INF;
            continue;
        }

        auto x = *itr; mins.erase(itr);
        ans[index[x]] = day;
        last_minute = (x+1) + d;
    }

    cout << day << endl;
    forn(i, n) cout << ans[i] << " ";
    cout << endl;



	return 0;
}

