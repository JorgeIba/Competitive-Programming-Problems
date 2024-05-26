#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n, m; cin>>n>>m;
    vector< vector<int> > mat(n, vector<int>(m));

    int mn = 1e9;
    for(auto &v: mat) {
        for(auto &x: v) {
            cin>>x;
            mn = min(mn, x);
        }
    }

    lli ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            ans += (mat[i][j] - mn);
        }
    }

    cout << ans << endl;


}


int main () {
	fastIO();
	
	int t = 1; 
	// cin>>t;
	while(t--) 
		main_();


	return 0;
}

