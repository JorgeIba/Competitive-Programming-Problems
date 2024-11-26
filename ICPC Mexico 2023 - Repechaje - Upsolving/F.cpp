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
    int d, c, r; cin>>d>>c>>r;

    lli D = d;
    vector<int> C(c);
    forn(i, c) {
        cin>>C[i];
    }

    int ans = r;
    forn(i, r) {
        int x; cin>>x;
        D += x;
    }

    for(auto x: C) {
        if(D >= x) {
            D -= x;
            ans++;
        } else {
            break;
        }
    }
    cout << ans << endl;


	return 0;
}

