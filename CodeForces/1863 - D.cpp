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


    // DD
    // UU

    vector<string> ans(n, string(m, '.'));

    for(int i = 0; i < n-1; i++){
        bool white = true;
        // if true
        // white
        // black

        for(int j = 0; j < m; j++){
            if((mat[i][j] == 'U' && mat[i+1][j] == 'D')){
                if(white){
                    ans[i][j] = 'W';
                    ans[i+1][j] = 'B';
                } else {
                    ans[i][j] = 'B';
                    ans[i+1][j] = 'W';
                }
                white = !white;
            }
        }
    }

    // L R
    // L R
    for(int j = 0; j < m-1; j++){
        bool white = true;
        // if true
        // white black

        for(int i = 0; i < n; i++){
            if((mat[i][j] == 'L' && mat[i][j+1] == 'R')){
                if(white){
                    ans[i][j] = 'W';
                    ans[i][j+1] = 'B';
                } else {
                    ans[i][j] = 'B';
                    ans[i][j+1] = 'W';
                }
                white = !white;
            }
        }
    }

    
    bool ok = true;
    for(int i = 0; i < n; i++){
        int cnt_w = 0;
        int cnt_b = 0;
        for(int j = 0; j < m; j++){
            cnt_w += (ans[i][j] == 'W');
            cnt_b += (ans[i][j] == 'B');
        }
        if(cnt_w != cnt_b) ok = false;
    }

    for(int j = 0; j < m; j++){
        int cnt_w = 0;
        int cnt_b = 0;
        for(int i = 0; i < n; i++){
            cnt_w += (ans[i][j] == 'W');
            cnt_b += (ans[i][j] == 'B');
        }
        if(cnt_w != cnt_b) ok = false;
    }


    if(!ok){
        cout << -1 << endl;
        return;
    }

    for(auto v: ans){
        cout << v << endl;
    }

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

