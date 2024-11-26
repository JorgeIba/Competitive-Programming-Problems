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
    lli n, m, r, c; cin>>n>>m>>r>>c;
    r--, c--;
    lli idx = r * m + c;

    lli move_1 = (n*m - 1) - idx;
    lli k = (n * m - idx) / m;

    if((n * m - idx) % m == 0)
        k--;
    // debugg(k);

    cout << move_1 + k * (m-1) << endl;
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

