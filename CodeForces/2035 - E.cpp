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


lli INF = 2e18;
void main_() {
    lli x, y, z, k; cin>>x>>y>>z>>k;

    auto division = [&](lli d) -> lli {
        lli r = d / k;
        lli num = z - k * r * (r+1) / 2;
        if(num < 0) return -1;

        return (num + d - 1) / d;
    };

    auto cost = [&](lli d) -> lli {
        lli r = division(d);

        lli ans = d * x + y * (d/k + r);
        return ans;
    };

    int cnt = 0;
    lli d = 1;
    lli ans = INF;
    while(d <= z) {
        lli cost_d = cost(d);
        ans = min(ans, cost_d);

        int l = d, r = z+10, ans = r;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(division(mid) != division(d)) {
                ans = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }

        cnt++;
        d = ans;
        if(division(d) < 0) break;
    }

    cout << (lli) ans << endl;
}

int main () {
	// fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}



	return 0;
}