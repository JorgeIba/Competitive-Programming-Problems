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
	int n, h_carlitos; cin>>n>>h_carlitos;

    vector<int> heights(n);
    for(auto &height: heights) {
        cin>>height;
    }

    int ans = 0;
    for(auto height: heights) {
        ans += (h_carlitos >= height);
    }

    cout << ans << endl;

	return 0;
}

