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
typedef complex<long double> cd;

const ld PI = acos(-1);
const lli INF = 1e15;

int main () {
	// fastIO();

    int n, k; cin>>n>>k;
    vector<lli> f(n);
    for(auto &x: f) {
        cin>>x;
    }

    vector<cd> C(n), R(n);
    for(int t = 0; t < n; t++) {
        cd sum = 0;
        for(int s = 0; s < n; s++) {
            if(s == k) continue;

            sum += ld(f[s]) * polar(ld(1.0), -2*PI*s*t / n);
        }
        C[t] = sum;
    }

    auto get_score = [&](ld f_k) {
        ld maxi = 0;
        for(int t = 0; t < n; t++) {
            cd F_t = C[t] + f_k * polar(ld(1.0), -2*PI*k*t / n);
            maxi = max(maxi, abs(F_t));
        }
        return maxi;
    };

    lli l = -INF, r = INF;
    while(r-l > 3) {
        lli ll = l + (r-l) / 3;
        lli rr = r - (r-l) / 3;

        if(get_score(ll) < get_score(rr)) {
            r = rr;
        } else {
            l = ll;
        }
    }

    ld ans = INF;
    for(lli x = l; x <= r; x++) {
        ans = min(ans, get_score(x));
    }
    cout << fixed << setprecision(15) << ans << endl;



	return 0;
}

