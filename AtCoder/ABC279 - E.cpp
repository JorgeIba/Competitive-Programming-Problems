#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;


int main () {
	fastIO();

	int n, m; cin>>n>>m;
	vector<int> A(m);
	for(auto &x: A) cin>>x;

	vector<int> B(n+1);
	iota(all(B), 0);

	for(int i = 0; i < m; i++){
		swap( B[ A[i] ], B[ A[i] + 1] );
	}

	vector<int> last_position(n+1);
	for(int i = 1; i <= n; i++)
		last_position[ B[i]  ] = i;


	iota(all(B), 0);

	vector<int> ans(m);
	int last_pos_1 = 1;
	for(int i = 0; i < m; i++){

		if(B[A[i]] == 1) {
			ans[i] = last_position[ B[A[i] + 1] ];
			last_pos_1 = A[i]+1;
		} else if( B[ A[i] + 1 ] == 1) {
			ans[i] = last_position[ B[A[i]] ];
			last_pos_1 = A[i];
		} else {
			ans[i] = last_position[ B[last_pos_1] ];
		}

		swap( B[ A[i] ], B[ A[i] + 1 ]  );
	}

	for(auto x: ans) cout << x << endl;


	return 0;
}

