#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define point pair<int,int>
#define x first
#define y second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli maxN = 11;
int M[2*(maxN+2)][2*(maxN+2)];


vector<pair<lli,lli>> adjList[maxN+10][maxN+10];


bool visited[maxN+5][maxN+5];

bool is_inside(int x, int y) {
	if(x < 0 || x >= maxN+5 || y < 0 || y >= maxN+5) return false;
	return true;
}

vector<pair<int,int>> dir = {{0, 1}, {1,0}, {-1, 0}, {0,-1}};

lli dfs(int i, int j, int color) {
	visited[i][j] = true;

	int x = 2*i, y = 2*j;

	lli sz = 1;
	for(auto [i_next, j_next]: dir) {

		if(!is_inside(i+i_next, j+j_next) || M[x+i_next][y+j_next]) continue;
		if(visited[i+i_next][j+j_next]) continue;
		sz += dfs(i+i_next, j+j_next, color);
	}
	return sz;
}


int main () {
	//fastIO();
	
	int n; cin>>n;

	point start; cin>>start.x>>start.y;


	point p_before = start;
	for(int i = 1; i <= n; i++) {
		point next; cin>>next.x>>next.y;
		point c_next = next;
		
		if(next.x == p_before.x) { // Horizontal
			if(next.y < p_before.y) swap(next, p_before);
			
			for(int y = 2*p_before.y-1; y <= 2*next.y - 1; y++) M[2*next.x - 1][y] = 1;
		} else {
			
			if(next.x < p_before.x) swap(next, p_before);
		
			for(int x = 2*p_before.x-1; x <= 2*next.x - 1; x++) M[x][2*next.y-1] = 1;
			
		}
		
		p_before = c_next;
		
	}	
	

	// for(int y = 2*maxN; y >= 0; y--) {
	// 	for(int x = 0; x <= 2*maxN; x++){
	// 		cout << M[x][y] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	
	lli ans = 0, color = 0;
	for(int i = 0; i < maxN; i++) {
		for(int j = 0; j < maxN; j++) {

			if(visited[i][j]) continue;

			lli aux = dfs(i, j, ++color);
		
			if(color != 1)
				ans = max(ans, aux);			
		}
	}
	

	
	// for(int i = 0; i < maxN; i++) {
	// 	for(int j = 0; j < maxN; j++) {
	// 		cout << "[" << i << ", " << j << "]:    ";
	// 		for(auto [x,y]: adjList[i][j]) {
	// 			cout << "[" << x << ", " << y << "], ";
	// 		}
	// 		cout << endl;
	// 	}
	// }	
	
	cout << ans << endl;


	return 0;
}
