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

vector< vector<int> > adjList;
vector< int > child, nxt;
int n, K; 

void prec(int u, int p = -1){
    bool f = true;
    int before = 0;
    for(auto v: adjList[u]) {
        if(v == p) continue;
        if(f) {
            child[u] = v;
            f = !f;
        } else {
            nxt[before] = v;
        }

        prec(v, u);

        before = v;
    }
}

const lli INF = 1e9;

const int maxN = 410;
lli dp_g[maxN][maxN][2];

lli g(int u, int k, bool has_started){
    if(u == -1) return k == 0 ? 0 : INF;

    lli &ans = dp_g[u][k][has_started];
    if(ans != -1) return ans;

    ans = INF;

    
    if(has_started){
        // mi jefe ya empezó

        // Me tomo
        for(int to_child = 0; to_child <= k-1; to_child++) {
            ans = min(ans, g(child[u], to_child, true) + g(nxt[u], (k-1) - to_child, true));
        }

        // no tomo
        ans = min(ans, 1 + g(nxt[u], k, true));
    } else{

        // No empiezo
        ans = min({ans, g(child[u], K, false), g(nxt[u], K, false)});

        // Empiezo
        ans = min(ans, g(child[u], K-1, true) + (u != 1));
    }

    return ans;
}


map< pair<int,int>, int > edge_to_idx;

void rec_g(int u, int k, bool has_started, int parent, vector<int> &ans_rec){
    if(u == -1) return;

    lli ans = dp_g[u][k][has_started];
    
    if(has_started){
        for(int to_child = 0; to_child <= k-1; to_child++) {
            lli ret = g(child[u], to_child, true) + g(nxt[u], (k-1) - to_child, true);
            if(ret == ans){
                rec_g(child[u], to_child, true, u, ans_rec);
                rec_g(nxt[u], (k-1) - to_child, true, parent, ans_rec);
                return;
            }
        }

        // no tomo
        ans_rec.push_back(edge_to_idx[{u, parent}]);
        rec_g(nxt[u], k, true, parent, ans_rec);
        // ans = min(ans, 1 + g(nxt[u], k, true));
    } else{

        // No empiezo
        lli start_child = g(child[u], K, false);
        lli start_nxt = g(nxt[u], K, false);

        lli start_me = g(child[u], K-1, true) + (u != 1);

        if(ans == start_child) {
            rec_g(child[u], K, false, u, ans_rec);
        } else if(ans == start_nxt){
            rec_g(nxt[u], K, false, parent, ans_rec);
        } else {
            assert(ans == start_me);
            if(u != 1) ans_rec.push_back(edge_to_idx[{u, parent}]);
            rec_g(child[u], K-1, true, u, ans_rec);
        }
    }

    return;
}



int main () {
	//fastIO();
	
    cin>>n>>K;
    adjList.resize(n+1);
    child.resize(n+1, -1);
    nxt.resize(n+1, -1);


    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        
        edge_to_idx[{u, v}] = i+1;
        edge_to_idx[{v, u}] = i+1;
    }

    prec(1);

    memset(dp_g, -1, sizeof(dp_g));


    lli start = g(child[1], K, false);
    lli not_start = g(child[1], K-1, true);
    lli ans = min( start , not_start );


    cout << ans << endl;



    vector<int> ans_idx;
    if(start == ans){
        rec_g(child[1], K, false, 1, ans_idx);
    } else {
        rec_g(child[1], K-1, true, 1, ans_idx);
    }
    for(auto x: ans_idx) cout << x << " ";
    cout << endl;


	return 0;
}

