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


lli solve_mini(vector<int> row){
	int m = SZ(row);

	int two_window = 0;
	for(int i = 0; i < m; ){ 
		if(row[i] == 1 && row[i+1] == 1) {
			two_window++;
			i += 2;
		} else {
			i++;
		}
	}

	two_window = min(m / 4, two_window);
	int total_light = count(all(row), 1);

	return total_light - two_window;
}


lli solve_maxi(vector<int> row) {
	int m = SZ(row);


	int non = 0;
	for(int i = 0; i < m-1; ){
		if(!(row[i] == 1 && row[i+1] == 1)) {
			non++;
			i += 2;
		} else {
			i++;
		}
	} 

	int total_light = count(all(row), 1);

	non = min(m / 4, non);
	return total_light - (m / 4  - non);
}


int main () {
	fastIO();
	
	int n, m; cin>>n>>m;
	
	vector< string > mat_s(n);
	for(auto &v: mat_s){
		cin>>v;
	}

	vector< vector<int> > mat(n, vector<int>(m));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			mat[i][j] = mat_s[i][j] - '0';
		}
	}
	
	lli ans_maxi = 0;
	for(int i = 0; i < n; i++) {
		ans_maxi += solve_maxi(mat[i]);
	}
	


	lli ans_mini = 0;
	for(int i = 0; i < n; i++) {
		ans_mini += solve_mini(mat[i]);
	}
	cout << ans_mini << " " << ans_maxi << endl;;

	return 0;
}

