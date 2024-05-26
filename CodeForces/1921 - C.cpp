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

void main_(){
    int n; cin>>n;
    lli f, a, b; cin>>f>>a>>b;

    vector<lli> times(n);
    for(auto &x: times) cin>>x;

    lli last_time = 0;
    for(auto x: times) {
        lli opt_1 = (x - last_time) * a;
        lli opt_2 = b;

        lli best_opt = min(opt_1, opt_2);
        f -= best_opt;

        if(f <= 0) {
            cout << "NO" << endl;
            return;
        }

        last_time = x;
    }

    cout << "YES" << endl;
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

