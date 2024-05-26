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


int main () {
	//fastIO();
    int n; cin>>n;

    vector< vector<int> > mat(n, vector<int>(n));

    lli total = 0;
    for(auto &v: mat) {
        for(auto &x: v){
            cin>>x;
            total += x;
        }
    }

    lli mini = 1e9;
    for(int i = 0, j = n-1; i < n; i++, j--) {
        mini = min(mini, (lli)mat[i][j]);
    }

    cout << total - mini << endl;


	return 0;
}

