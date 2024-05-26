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
	fastIO();
	
    int n; cin>>n;
    int ori = n;
    vector< pair<lli,lli> > primes;
    for(lli i = 2; i * i <= n; i++){
        if(n % i == 0) {
            int pot = 0;
            while(n % i == 0) {
                n /= i;
                pot++;
            }

            primes.push_back({i, pot});
        }
    }

    if(n > 1) {
        primes.push_back({n, 1});
    }


    lli ans = ori;
    for(auto [p, a]: primes){
        if(a&1) ans *= p;
    }

    cout << ans << endl;

	return 0;
}

