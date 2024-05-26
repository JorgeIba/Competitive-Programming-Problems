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


const int MAXN = 1e5+100;


#define edge array<int,3>

vector<edge> adjList[MAXN];
int prefix_xor[MAXN];
int time_disc[MAXN];
int Time = 1;


vector<int> cycle_basis;

void dfs(int u, int id_edge_p) {
    time_disc[u] = Time++;

    for(auto [v, w, id_edge]: adjList[u]) {
        if(id_edge == id_edge_p) continue;


        if(time_disc[v] && time_disc[v] <= time_disc[u]) {
            int xor_path = prefix_xor[u]^prefix_xor[v]^w;
            cycle_basis.push_back(xor_path);
            continue;
        }

        if(time_disc[v]) continue;

        prefix_xor[v] = prefix_xor[u] ^ w;
        dfs(v, id_edge);
    }
}


const int LOG_D = 31;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) //Zeros -> make zeros above basis[i]
{
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++){
				if(j==i) continue;
				if(j < i){
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}



int main () {
	//fastIO();

    int n, m; cin>>n>>m;

    forn(i, m) {
        int u, v, w; cin>>u>>v>>w; u--, v--;
        adjList[u].push_back({v, w, i});
        adjList[v].push_back({u, w, i});
    }


    dfs(0, -1);

    for(auto x: cycle_basis) insert_vector(x, true);


    int xor_path_main = prefix_xor[0] ^ prefix_xor[n-1];


    for(int i = LOG_D-1; i >= 0; i--) {
        if(xor_path_main & (1LL << i)) {
            xor_path_main ^= basis[i];
        }
    }

    cout << xor_path_main << endl;



	return 0;
}

