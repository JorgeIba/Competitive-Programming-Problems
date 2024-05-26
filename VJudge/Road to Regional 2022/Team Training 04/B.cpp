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
const int MAXN = 3e5 + 1000;

vector<int> adjList[MAXN];
int depth[MAXN];


pair<int,int> bfs(int start, int n) {
    vector<int> dist(n, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);

    while(!q.empty()){
        int u = q.front(); q.pop();

        for(auto v: adjList[u]) {
            if(dist[v] != -1) continue;
            dist[v] = dist[u] + 1;

            q.push(v);
        }
    }

    int max_dist = *max_element(all(dist));
    for(int i = 1; i < n; i++) {
        if(max_dist == dist[i]) {
            return {i, dist[i]};
        }
    }
    return {-1, -1};
}

//* n has to be exactly the size of the tree
// return at most 2 centroids of a tree
vector<int> getCentroids(int n) {
    vector<int> centroids;
    vector<int> sz(n+1); //! 1-indexed
    auto dfs = [&](const auto& self, auto u, auto p) -> void {
        sz[u] = 1;
        bool is_centroid = true;
        for (auto v: adjList[u]){
            if (v == p) continue;

            self(self, v, u);
            sz[u] += sz[v];
            if (sz[v] > n / 2) is_centroid = false;
        }
        if (n - sz[u] > n / 2) is_centroid = false;
        if (is_centroid) centroids.push_back(u);
    };
    dfs(dfs, 1, -1); //! 1-indexed
    return centroids;
}

void dfs(int u, int p, vector<int> &vertex) {
    vertex.push_back(u);

    for(auto v: adjList[u]) {
        if(v == p) continue;
        dfs(v, u, vertex);
    }
};

int main() {
    // fastIO();

    int n; cin>>n;

    forn(i, n-1) {
        int u, v; cin>>u>>v;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    auto centroid = getCentroids(n)[0];

    

    vector< vector<int> > subtrees;
    for(auto v: adjList[centroid]) {
        vector<int> vertex;
        dfs(v, centroid, vertex);
        subtrees.push_back(vertex);
    }

    int m = SZ(subtrees);

    int greatest = 0;
    for(int i = 0; i < m; i++) {
        if(SZ(subtrees[i]) > SZ(subtrees[greatest])){
            greatest = i;
        }
    }

    queue< pair<int,int> > pq;
    for(int i = 0; i < m; i++) {
        pq.push({SZ(subtrees[i]), i});
    }

    vector<int> ans;
    ans.push_back(centroid);
    while(!pq.empty()) {
        auto [sz, idx] = pq.front(); pq.pop();

        ans.push_back(subtrees[idx].back());
        subtrees[idx].pop_back();

        if(SZ(subtrees[idx]))
            pq.push( { SZ(subtrees[idx]), idx }  );
    }

    auto [start, dist] = bfs(1, n+1);
    auto [farthest, diameter] = bfs(start, n+1);

    // debugg(centroid);
    // debugg(start);
    // debugg(farthest);
    // debugg(diameter);

    if(diameter <= 2) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(auto v: ans) cout << v << " ";
        cout << endl;
    }


    return 0;
}