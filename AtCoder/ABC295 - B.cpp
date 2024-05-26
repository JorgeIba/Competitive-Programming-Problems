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
	int n, m; cin>>n>>m;
    vector< string > mat(n);
    for(auto &s: mat) cin>>s;


    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            if(mat[i][j] != '.' && mat[i][j] != '#') {
                int range = mat[i][j] - '0';


                for(int x = 0; x < n; x++){
                    for(int y = 0; y < m; y++) {
                        if(mat[x][y] == '#' && abs(i-x) + abs(j-y) <= range) {
                            mat[x][y] = '.';
                        }
                    }
                }

                mat[i][j] = '.';
            }
        }
    }

    for(auto v: mat){
        for(auto x: v){
            cout << x;
        }
        cout << endl;
    }



}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

