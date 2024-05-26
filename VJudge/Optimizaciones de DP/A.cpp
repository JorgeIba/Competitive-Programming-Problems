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

const int MAXN = 50 + 5;

int mat[MAXN][MAXN];

int main () {
	//fastIO();

    int n, m; cin>>n>>m;

    forn(i, n){
        forn(j, m){
            cin>>mat[i][j];
        }
    }

    bool ok = true;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < m-1; j++){
            if( mat[i][j] + mat[i+1][j+1] > mat[i][j+1] + mat[i+1][j] )
                ok = false;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;


	return 0;
}

