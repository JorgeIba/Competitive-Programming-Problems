#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

void solve(){
    lli n, k; cin>>n>>k;
    vector< string > mat(n, string(n, '.'));
    lli max_k = (n+1)/2;
    if(k > max_k){
        cout << -1 << endl;
        return;
    } 
    else {
        lli shots = k;
        for(int i = 0; i < n; i+=2)
        {
            if(shots){
                mat[i][i] = 'R';
                shots--;
            }
            
        }
        for(int i = 0; i<n; i++) cout << mat[i] << endl;
    }

    
}


int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

