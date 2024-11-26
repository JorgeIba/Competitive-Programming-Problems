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

void main_() {
    int n, r; cin>>n>>r;
    vector<int> fam(n);
    for(auto &x: fam)
        cin>>x;

    int pairs = 0, res = 0;
    for(auto x: fam) {
        pairs += (x / 2);
        res += (x % 2);
    }

    int ans = 2 * pairs;
    r -= pairs;

    int happy = min(res, r);
    res -= happy;

    ans += happy - res;

    cout << ans << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

