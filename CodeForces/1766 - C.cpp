// Problem: C. Hamiltonian Wall
// Contest: Codeforces - Educational Codeforces Round 139 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1766/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector< string > mat(2);
int m; 

const int maxM = 2e5+100;
bool visited[2][maxM];

int dfs(int i, int j) {
	if(mat[i][j] == 'W') {
		return -1e9;
	}
	
	visited[i][j] = 1;
	int ret = 1;
	if(i == 0) {
		if(mat[i+1][j] == 'B' && !visited[i+1][j]) {	
			ret += dfs(i+1, j);
		} else if(mat[i][j+1] == 'B') {
			ret += dfs(i, j+1);
		}
		
	} else{
		if(mat[i-1][j] == 'B' && !visited[i-1][j]) {	
			ret += dfs(i-1, j);
		} else if(mat[i][j+1] == 'B') {
			ret += dfs(i, j+1);
		}
	}
	
	return ret;
}



void main_(){
	cin>>m;
	cin>>mat[0]>>mat[1];
		
	int total = 0;
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < m; j++) {
			total += (mat[i][j] == 'B');
		}
	}		
				
	int ans_1 = 0, ans_2 = 0;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < m; j++){
			visited[i][j] = 0;
		}
	}
	ans_1 = dfs(0, 0);

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < m; j++){
			visited[i][j] = 0;
		}
	}
	ans_2 = dfs(1, 0);
	
		
		
	int ans = max(ans_1, ans_2);
//	debugg(ans);
		
	cout << (ans == total ? "YES" : "NO") << endl;
		
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

