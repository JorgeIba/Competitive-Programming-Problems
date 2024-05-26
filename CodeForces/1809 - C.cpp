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


void main_(int n, int k){
	if(k == 0){
		forn(i, n) {
			cout << -1 << " ";
		}
		cout << endl;
		return;
	}
	
	
	vector< int > ans(n+1);
	int start = 0, end = 0, flag = 0;
	
	int aux_k = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			aux_k++;
			if(aux_k == k) {
				start = i;
				end = j+1;
				flag = 1;
				break;
			}
		
		} 
		if(flag) break;
	}
	
	
	for(int i = 0; i < start; i++) {
		ans[i] = 1000;
	}
	
	
	for(int i = start+1; i < end; i++) {
		ans[i] = -1;
	}


	ans[start] = 31;
	
	for(int i = end; i < n; i++) {
		ans[i] = -32;
	}
		
	
	forn(i, n){
		cout << ans[i] << " ";
	}
	cout << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	while(t--) {
		int n, k; cin>>n>>k;
		main_(n, k);
	}
	
	// for(int n = 2; n < 30; n++) {
		// for(int k = 1; k <= n*(n+1) / 2;  k++){
			// main_(n, k);			
		// }
	// }


	return 0;
}

