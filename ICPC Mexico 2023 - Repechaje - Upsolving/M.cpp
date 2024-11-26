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


int main () {
    // fastIO();

    int n; cin>>n;
    vector< vector<int> > mat(n, vector<int>(n));
    forn(i, n) {
        forn(j, n) {
            cin>>mat[i][j];
        }
    }

    vector< vector<int> > can_be_eliminated(n, vector<int>(n));
    forn(middle, n) {
        forn(u, n) {
            forn(v, n) {
                if(middle == u || middle == v) continue;

                int cost_at_least_2 = mat[u][middle] + mat[middle][v];
                if(cost_at_least_2 < mat[u][v]) {
                    cout << -1 << endl;
                    return 0;
                } else if(cost_at_least_2 == mat[u][v])
                    can_be_eliminated[u][v] = 1;
            }
        }
    }

    int ans = 0;
    forn(i, n)
        ans += count(all(can_be_eliminated[i]), 1);
    
    cout << ans/2 << endl;

	return 0;
}

