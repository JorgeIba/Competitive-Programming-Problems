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

    if(m == 1){
        cout << 0 << endl;
        for(int i = 0; i < n; i++) cout << 0 << endl;
        return;
    }


    int ans = min(n+1, m);

    bool needs = false;
    int original_m = m;
    if(m >= n+1){
        needs = true;
        m = n+1;
    } 

    vector< vector<int> > mat(n, vector<int>(m));
    for(int i = 0, start = 1; i < m-1; i++, start++){
        for(int j = 0, k = start; j < m; j++, k = (k+1) % m){
            mat[i][j] = k;
        }
    }

    for(int i = m-1; i < n; i++){
        mat[i] = mat[i-1];
    }

    if(needs) {
        m = original_m;
        for(int i = 0; i < n; i++){
            mat[i].resize(m);
        }

        for(int i = 0; i < n; i++){
            for(int j = n+1, k = n+1; j < m; j++, k++){
                mat[i][j] = k;
            }
        }
    }


    cout << ans << endl;
    for(auto v: mat){
        for(auto x: v) cout << x << " ";
        cout << endl;
    }
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

