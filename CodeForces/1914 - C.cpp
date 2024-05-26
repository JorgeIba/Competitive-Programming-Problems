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
    int n, k; cin>>n>>k;

    vector<lli> A(n), B(n);
    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;

    lli best_b = 0;
    lli ans = 0;
    lli sum = 0;
    for(int i = 0; i < min(n, k); i++) {
        best_b = max(best_b, B[i]);

        sum += A[i];
        // if(i == 3) cout << sum << " " << best_b << " - " << (i+1 - k) << 
        ans = max(ans, sum + best_b * (k - (i+1)));
    }

    cout << ans << endl;

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

