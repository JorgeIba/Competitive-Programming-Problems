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

    int n = 1'500'000;
    // cin>>n;

    vector< vector<int> > divs(n+1);

    for(int d = 1; d <= n; d++) {
        for(int j = d; j <= n; j += d) {
            divs[j].push_back(d);
        }
    }


    int ans = 0;
    for(int L = 12; L <= n; L += 2) {
        set<tuple<lli,lli>> solutions;

        for(auto r: divs[L/2]) {
            for(auto d: divs[r]) {
                int k = r / d;
                int m = L / (2 * k * d) - d;
                assert(2*k*d*(d+m) == L);
                lli a = 1LL * d * d - 1LL * m * m;
                lli b = 2LL * d * m;
                lli c = 1LL * d * d + 1LL * m * m;
                a *= k;
                b *= k;
                c *= k;

                if(a > b) swap(a, b);

                if(a > 0 && b > 0){
                    solutions.insert({a, b});
                }
            }
        }
        ans += (SZ(solutions) == 1);
    }

    cout << ans << endl;



	return 0;
}

