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
    lli x, n; cin>>x>>n;

    vector<lli> divs;
    for(int i = 1; 1LL * i * i <= x; i++) {
        if(x % i == 0) {
            divs.push_back(i);
            if(i*i != x) 
                divs.push_back(x / i);
        }
    }

    lli ans = 1;
    for(auto d: divs) {
        lli others = 1LL * (n-1) * d;
        lli left = x - others;
        if(left <= 0) continue;
        if((x - others) % d == 0){
            ans = max(ans, d);
        }
    }

    cout << ans << endl;
}

int main () {
	// fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

