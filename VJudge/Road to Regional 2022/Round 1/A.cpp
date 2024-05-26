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

    lli x, y, n; cin>>x>>y>>n;


    lli ans = 1e18;
    for(int i_x = 0; i_x <= n; i_x++){
        for(int j_y = 0; j_y <= n/3 + 1; j_y++) {
            if(i_x + 3*j_y == n) {
                ans = min(ans, x*i_x + y*j_y);
            }
        }
    }

    cout << ans << endl;

	return 0;
}

