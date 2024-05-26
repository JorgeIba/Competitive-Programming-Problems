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

vector< pair<int,int> > dirs = {
        {-1, 0},
    {0,-1}, {0, 1},
        {1, 0}
};

const int MOD = 1e9+7;

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a  % MOD;
    }
    return res;
}


int main () {
	//fastIO();
	
	int n, m; cin>>n>>m;

    vector< string > mat(n);
    for(auto &s: mat) cin>>s;

    auto is_inside = [&](int i, int j){
        if(i < 0 || i >= n || j < 0 || j >= m) return false;
        return true;
    };

    int free_cell = 0;

    forn(i, n){
        forn(j, m){
            bool ok = true;
            for(auto [dx, dy]: dirs) {
                if(is_inside(i+dx, j+dy)){
                    if(mat[i][j] != mat[i+dx][j+dy])
                        ok = false;
                }
            }
            free_cell += ok;
        }
    }

    cout << powerMod(2, free_cell) << endl;




	return 0;
}

