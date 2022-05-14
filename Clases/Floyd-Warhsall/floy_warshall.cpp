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


int main () {
	//fastIO();

    int n; cin>>n;

    const lli INF = 1e18;

    vector< vector<lli> > matAdj(n, vector<lli>(n));
    vector< vector<lli> > f(n, vector<lli>(n, INF));


    for(int i = 0; i < n; i++) {
        for(int j = 0; j< n ; j++) {
            cin>>matAdj[i][j];
            f[i][j] = matAdj[i][j];
        }
    }

    vector<int> orden(n);
    for(auto &x: orden){ 
        cin>>x;
        x--;
    }

    reverse(all(orden));


    vector<lli> ans;
    vector<bool> processed(n);

    // cualquier orden
    for(auto k: orden) {

        processed[k] = true;

        // Solo encuentra caminos cortos de nodos ya creados
        for(int u = 0; u < n; u++) {
            for(int v = 0; v < n; v++) {
                f[u][v] = min(f[u][v],  f[u][k] + f[k][v]);
            }
        }



        // Ignora los que no has puesto
        lli sum = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++){
                if(processed[i] && processed[j]) {
                    sum += f[ i  ][ j ];
                }
            }
        }
        ans.push_back(sum);
    

    }

    

    reverse(all(ans));
    for(auto x: ans) cout << x << " ";


	return 0;
}

