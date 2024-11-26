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
    int n; cin>>n;

    if(n == 2) {
        cout << 66 << endl;
        return;
    }

    if(n % 2 == 0) {
        forn(i, n-2) {
            cout << 3;
        }
        forn(i, 2) {
            cout << 6;
        }
        cout << endl;
        return;
    } 

    if(n == 1 || n == 3) {
        cout << -1 << endl;
        return;
    }

    forn(i, n-5) {
        cout << 3;
    }
    cout << 36366 << endl;
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

