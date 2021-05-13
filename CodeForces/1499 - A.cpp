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
    lli n, k1, k2; cin>>n>>k1>>k2;

    lli w, b; cin>>w>>b;

    lli totalW = k1 + k2, totalB = 2*n - totalW;
    if(totalW % 2 != 0)
    {
        totalW--; totalB--;
    }
    if(2*w <= totalW && 2*b <= totalB) cout << "YES\n";
    else cout << "NO\n";
}


int main () {
	fastIO();
    int t; cin>>t;
    while(t--) solve();

	return 0;
}