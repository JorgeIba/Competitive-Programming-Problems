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

int main () {
    // fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    int parity = 0;
    map<int,int> fr;
    fr[0] = 1;
    lli ans = 0;
    for(auto x: nums) {
        parity ^= x;
        ans += fr[parity ^ 1];
        fr[parity]++;
    }

    cout << ans << endl;

	return 0;
}

