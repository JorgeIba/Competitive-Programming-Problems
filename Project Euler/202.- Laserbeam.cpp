#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


int main () {
	//fastIO();

    lli N; cin >> N;

    time_t begin_t = clock();

    // x + y = (N+3)/2
    // gcd(x, y) == 1
    // x = A + R
    // y = A - 2*R
    // x-y = A + R - (A - 2*R) =  3*R


    // K = (N+3) / 2
    // y = K - x
    // gcd(x, y) = gcd(x, K-x) = gcd(x, K) = 1
    // x-y = 0 mod 3  ->   x - (K - x) = 0 MOD



    lli K = (N+3) / 2;

    lli ans = 0;

    // cout << K << " " << K / 3 << endl;

    
    assert(K % 3 != 0);
    
    lli init = 2*K % 3;

    for(lli x = init; x < K/2;  x += 3) {
        if(__gcd(x, K) == 1) {
            // cout << x << " ";
            ans++;
        }
    }
    

    cout << 2*ans << endl;
    cout << (double) (clock() - begin_t) / CLOCKS_PER_SEC << endl;

	return 0;
}

