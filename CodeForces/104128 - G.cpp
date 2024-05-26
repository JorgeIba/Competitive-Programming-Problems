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
    int n; cin >> n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;

    int sum = 1;
    int pok = 1;
    int ops = 0;
    for(auto x: a){ 
        if(x == 1) {
            sum++;
            pok++;
        }
        if(x == -1) {
            if(pok == 1){
                if(ops){
                    ops--;
                    pok+=2;
                    sum++;
                } else {
                    cout << -1 << endl;
                    return;
                }
            }
            pok--;
        }
        if(x == 0) {
            if(pok >= 2){
                pok--;
                ops++;
            } else {
                sum++;
                pok++;
            }
        } 
    }

    int gcd = __gcd(sum, pok);
    cout << sum / gcd << ' ' << pok / gcd << endl;
}

int main() {
    fastIO();
    int tt;
    cin >> tt;
    while(tt--)
       solve();
}