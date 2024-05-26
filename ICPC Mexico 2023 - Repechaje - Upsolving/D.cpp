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

const lli INF = 1e15;

const int MAXN = 300 + 50;

vector< int > adjList[MAXN];
lli mat[MAXN][MAXN];
int idx_mat[MAXN][MAXN];

const int FIRST = 0;
const int SECOND = 1;
const int NONE = 2;

typedef pair<lli,lli> pairi;
pair< vector< pairi >, vector< pairi > > dijkstra(int start, int n){
    vector< pairi > dist_1(n, {INF, -1});
    vector< pairi > dist_2(n, {INF, -1});

    auto update = [&](int who, lli cand, int v) -> int {
        auto &[best_1, who_best_1] = dist_1[v];
        auto &[best_2, who_best_2] = dist_2[v];

        if(who == who_best_1){
            if(cand < best_1){
                best_1 = cand;
                return FIRST;
            }

            return NONE;
        }
        
        if(who == who_best_2){

            if(cand < best_2){
                best_2 = cand;

                if(best_2 < best_1){
                    swap(best_1, best_2);
                    swap(who_best_1, who_best_2);
                    return FIRST;
                }
                return SECOND;
            }

            return NONE;
        }

        if(cand <= best_1) {

            best_2 = best_1;
            who_best_2 = who_best_1;

            best_1 = cand;
            who_best_1 = who;

            return FIRST;
        } else if(cand < best_2){

            best_2 = cand;
            who_best_2 = who;
            return SECOND;
        }

        assert(best_1 <= best_2);

        return NONE;
    };


    typedef tuple<lli,lli,lli> tll;
    priority_queue< tll, vector<tll>, greater<tll> > pq;

    for(auto u: adjList[start]){
        dist_1[u] = {mat[start][u], u};

        pq.push({dist_1[u].first, u, u});
    }

    while(!pq.empty()){
        auto [dist_u, who_u, u] = pq.top(); pq.pop();
        
        bool is_1 = (dist_u == dist_1[u].first && who_u == dist_1[u].second);
        bool is_2 = (dist_u == dist_2[u].first && who_u == dist_2[u].second);

        if(!is_1 && !is_2) continue;

        for(auto v: adjList[u]){
            lli w = mat[u][v];
            if(v == start) continue;

            int status = update(who_u, dist_u + w, v);
            if(status == NONE) continue;
            else if(status == FIRST) 
                pq.push({dist_1[v].first, dist_1[v].second, v});
            else
                pq.push({dist_2[v].first, dist_2[v].second, v});    
        }

    }
    return {dist_1, dist_2};
}

int main () {
	//fastIO();
	
    int n, m; cin>>n>>m;

    forn(i, n){
        forn(j, n){
            mat[i][j] = INF;
        }
        mat[i][i] = 0;
    }

    vector< pair<int,int> > edges(m);
    forn(i, m){
        int u, v, l; cin>>u>>v>>l; u--, v--;

        edges[i] = {u, v};
        mat[u][v] = l;
        mat[v][u] = l;

        idx_mat[u][v] = i;
        idx_mat[v][u] = i;
    }

    for(auto [u, v]: edges){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    vector<lli> ans(m);
    vector< vector<int> > queries_in_u(n);
    for(auto [u, v]: edges){
        if(u > v) swap(u, v);
        queries_in_u[u].push_back(v);
    }


    forn(u, n){
        if(queries_in_u[u].empty()) continue;

        auto [dist_1, dist_2] = dijkstra(u, n);
        for(auto v: queries_in_u[u]){
            auto [best_1, who_best_1] = dist_1[v];
            auto [best_2, who_best_2] = dist_2[v];

            if(who_best_1 != v) ans[ idx_mat[u][v] ] = best_1;
            else ans[ idx_mat[u][v] ] = best_2;
        }
    }

    for(auto x: ans) cout << (x != INF ? x : -1) << endl;


	return 0;
}

