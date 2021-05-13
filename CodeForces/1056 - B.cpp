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
    lli n, m; cin>>n>>m;

    lli ans = 0;

    for(lli i = 1; i <= min(n,m); i++)
    {
        for(lli j = 1; j <= min(n,m); j++)
        {
            if(((i % m)*(i % m) + (j%m)*(j%m))%m == 0)
            {
                lli rest_i = (n - i)/m + 1, rest_j = (n - j)/m + 1;
                ans += rest_i * rest_j;
            }
        }
    }
    cout << ans << endl;

	return 0;
}