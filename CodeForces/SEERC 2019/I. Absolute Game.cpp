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
	fastIO();
    lli n; cin>>n; 
    vector<lli> a(n), b(n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;

    lli ans = -1;
    for(int i = 0; i<n; i++)
    {
        lli minCurr = 1e18;
        for(int j = 0; j<n; j++)
        {
            minCurr = min( minCurr, abs(a[i] - b[j])  );
        }
        ans = max(ans, minCurr);
    }
    

    cout << ans << endl;

	return 0;
}