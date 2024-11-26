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

    lli a, b, x, y; cin>>a>>b>>x>>y;
    lli g = gcd(x, y);
    x /= g;
    y /= g;

    cout << min(a / x, b / y) << endl;

	return 0;
}

