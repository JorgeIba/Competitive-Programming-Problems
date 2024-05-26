#include<bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl '\n'
#define forn(i, n) for(int i = 0; i < (n); i++) 
#define forr(i, a, b) for(int i = (a); i <= (b); i++) 
#define SZ(a) (int) a.size()
#define pb push_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;

ld eps = 1e-18;

int main() {
    // fastIO();
    lli n, k, d, s;
    cin >> n >> k >> d >> s;
    lli sum = (n*(d - s) - (k - n) * s);
    //cout << sum << endl;
    ld ans = sum / (n - k);
    cout << fixed << setprecision(10);
    if(sum < 0 || sum > 100 * (n - k)) cout << "impossible" << endl;
    else cout << (ld)sum / (ld)(n - k) << endl;


    return 0;
}
