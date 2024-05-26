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


void main_(){

    int n, m, p; cin>>n>>m>>p;
    vector<int> A(n), B(m);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;

    sort(all(A));
    sort(all(B));

    vector<lli> prefix_B(m);
    for(int i = 0; i < m; i++){
        if(i)
            prefix_B[i] = prefix_B[i-1];
        prefix_B[i] += B[i];
    }

    int r = m-1;
    lli ans = 0;
    for(int i = 0; i < n; i++){
        auto a = A[i];
        while(r >= 0 && (a + B[r] > p)) {
            r--;
        }
        int left = r+1;
        int right = m - left;
        ans +=  (r >= 0 ? prefix_B[r] : 0) + 1LL * left * a + 1LL * right * p;
    }

    cout << ans << endl;
    


}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

