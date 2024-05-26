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

    vector<lli> ans;
    for(lli mask = n; mask; mask = (mask-1)&n) {
        ans.push_back(mask);
    }

    ans.push_back(0);
    reverse(all(ans));
    
    for(auto x: ans) cout << x << endl;

	return 0;
}

