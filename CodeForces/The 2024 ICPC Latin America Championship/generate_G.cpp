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


const int MAXN = 1e5;
int main () {
	// fastIO();


    lli ans = 0;
    for(int x = 1; x <= MAXN; x++) {        
        for(int y = x; y <= MAXN; y += x) {
            ans += (MAXN / y);
        }
    }
    cout << ans << endl;


	return 0;
}
