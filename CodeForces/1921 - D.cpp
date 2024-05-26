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
    int n, m; cin>>n>>m;
    
    vector<lli> A(n), B(m);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;


    sort(all(A));
    sort(all(B));



    int lA = 0, rA = n-1;
    int lB = 0, rB = m-1;
    lli ans = 0;
    while(lA <= rA) {
        lli opt_1 = abs(A[lA] - B[lB]);
        lli opt_2 = abs(A[lA] - B[rB]);
        lli opt_3 = abs(A[rA] - B[lB]);
        lli opt_4 = abs(A[rA] - B[rB]);

        lli best = max({opt_1, opt_2, opt_3, opt_4});

        // debugg(lA);
        // debugg(rA);
        // debugg(lB);
        // debugg(rB);
        // debugg(best);

        ans += best;
        if(opt_1 == best) {
            lA++; lB++;
        }else if(opt_2 == best) {
            lA++; rB--;
        }else if(opt_3 == best) { 
            rA--; lB++;
        } else {
            rA--; rB--;
        }
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

