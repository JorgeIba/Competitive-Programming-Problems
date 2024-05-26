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

    VLL x(2), y(2); cin>>x[0]>>x[1]>>y[0]>>y[1];

    lli ans = -1e18;
    for(auto xi: x) {
        for(auto yi: y) {
            ans = max(ans, xi*yi);
        }
    }

    cout << ans << endl;



	return 0;
}

