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

void solve() {
    lli n; cin>>n;

    auto lcm = [](lli a, lli b) {
        return a * (b / __gcd(a, b));
    };



    if( n % 2 == 0 ){
        cout << n/2 << " " << n/2 << endl;
    } else {

        auto get_ans = [&](lli a, lli b) {
            // one option
            lli ans = n;
            if(b - 1 > 0) {
                lli k = b - 1;
                ans = min(ans, lcm(a, k*a));
            }

            if(a - 1 > 0) {
                lli k = a - 1;
                ans = min(ans, lcm(b, b*k));
            }
            return ans;
        };

        lli ans = n;
        for(lli i = 1; i * i <= n; i++) {
            if(n % i == 0){
                lli a = n / i;
                lli b = i;

                ans = min(ans, get_ans(a, b));
            }
        }

        for(lli i = 1; i * i <= n; i++) {
            if(n % i == 0){
                lli a = n / i;
                lli b = i;

                if(ans == get_ans(a, b)) {
                    if(b - 1 > 0) {
                        lli k = b - 1;
                        if(ans == k*a) {
                            cout << a << " " << k*a << endl;
                            return;
                        }
                    }

                    if(a - 1 > 0) {
                        lli k = a - 1;
                        if(ans == k*b) {
                            cout << b << " " << k*b << endl;
                            return;
                        }
                    }
                }
            }
        }

        

        cout << ans << endl;

    }


}


int main () {
	//fastIO();
	
    int t; cin>>t;
    while(t--) solve();


	return 0;
}

