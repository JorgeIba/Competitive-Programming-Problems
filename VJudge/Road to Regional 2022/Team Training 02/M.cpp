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

char contr(char a) {
    if( a == 'R' ) return 'G';
    return 'R';
}


vector< string > generate(char first, int n, int m){
    vector<string> mat(n, string(m,' '));
    

    mat[0][0] = first;
    for(int i = 1; i < n; i++) 
        mat[i][0] = contr(mat[i-1][0]);

    for(int i = 0; i < n; i++) {
        for(int j = 1; j < m; j++) {
            mat[i][j] = contr(mat[i][j-1]);
        }
    }

    return mat;
}


int cost(char to_change, char must) {
    if(to_change == must) return 0;
    if(to_change == 'R') {
        assert(must == 'G');
        return 5;
    } else {
        assert(must == 'R');
        return 3;
    }
}

lli get_cost(vector<string> &ori, vector<string> &must, int n, int m) {
    lli total_cost = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            total_cost += cost( ori[i][j],  must[i][j] );
        }
    }

    return total_cost;
}



void solve() {
    int n, m; cin>>n>>m;
    vector< string > mat(n);

    for(auto &s: mat) cin>>s;

    auto mat_1 = generate('G', n, m);
    auto mat_2 = generate('R', n, m);


    auto ans_1 = get_cost(mat, mat_1, n, m);
    auto ans_2 = get_cost(mat, mat_2, n, m);

    cout << min(ans_1, ans_2) << endl;
}


int main () {
	//fastIO();
	
    int t; cin>>t;
    while(t--) solve();


	return 0;
}

