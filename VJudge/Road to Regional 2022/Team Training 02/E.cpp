#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


int main () {
	//fastIO();
	
    int t; cin>>t;

    auto gauss = [](lli n) {
        return n * (n+1) / 2;
    };

    while(t--) {
        lli n; cin>>n;
        n--;

        lli ans = 3 * gauss(n / 3) + 5 * gauss(n / 5) - 15 * gauss(n / 15);
        cout << ans << endl;
    }


	return 0;
}

