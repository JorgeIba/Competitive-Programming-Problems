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


void main_(bool print_end){

    int n; cin>>n;
    vector< vector<int> > mat(n, vector<int>(n));

    for(auto &v: mat){
        for(auto &x: v){
            cin>>x;
        }
    }

    vector<int> ans;
    forn(i, n){
        vector<int> row = mat[i];
        if(i & 1) {
            reverse(all(row));
        }
        for(auto x: row) ans.push_back(x);
    }

    int cnt_up = 0;
    int cnt_down = 0;
    forr(i, 1, SZ(ans)-1) {
        cnt_up += (ans[i-1] < ans[i]);
        cnt_down += (ans[i-1] > ans[i]);
    }

    if(cnt_up > cnt_down){
        reverse(all(ans));
    } 

    forn(i, SZ(ans)){
        cout << ans[i];
        if(i != SZ(ans)-1)
            cout << " ";
    }
    if(print_end)
        cout << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_(t);


	return 0;
}

