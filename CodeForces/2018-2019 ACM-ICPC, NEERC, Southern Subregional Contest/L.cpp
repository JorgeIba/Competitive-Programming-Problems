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


const int LOG = 30;
int main () {
	fastIO();

    int n, y1; cin>>n>>y1;
    vector<int> A(n);
    for(auto &x: A) cin>>x;

    int m, y2; cin>>m>>y2;
    vector<int> B(m);
    for(auto &x: B) cin>>x;


    auto check_for_d = [&](int D) {
        int ans_d = 0;
        int half = D/2;
        map<int,int> fr_A, fr_B;
        for(auto x: A) {
            int y = x % D;
            fr_A[y]++;
        }
        for(auto x: B){
            int y = x % D;
            fr_B[y]++;
        }
        
        for(auto [x, frA]: fr_A) {
            ans_d = max(ans_d, frA + fr_B[(x+half)%D]);
        }

        for(auto [x, frB]: fr_B) {
            ans_d = max(ans_d, frB + fr_A[(x+half)%D]);
        }

        return ans_d;
    };

    int ans = 2;
    for(int i = 1; i < LOG; i++) {
        ans = max(ans, check_for_d(1 << i));
    }
    cout << ans << endl;

	return 0;
}