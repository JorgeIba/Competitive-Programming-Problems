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


const int MAXN = 1e5 + 100;
int a[MAXN];
set< pair<int,int> > queries[MAXN];


struct DSU{
    int n;
    vector<int> parent, size;
    vector<lli> sum;


    DSU(int n): n(n), parent(n), size(n, 1), sum(n) {
        iota(all(parent), 0);
        forn(i, n) sum[i] = a[i];
    }

    int root(int u){
        return parent[u] = (parent[u] == u ? u : root(parent[u]));
    }

    void join(int u, int v){
        int Ru = root(u), Rv = root(v);
        if(Ru == Rv) return;

        if(SZ(queries[Ru]) > SZ(queries[Rv])) swap(Ru, Rv);
        parent[Ru] = Rv;

        for(auto [w, idx]: queries[Ru]) queries[Rv].insert({w, idx});

        sum[Rv] += sum[Ru];
        size[Rv] += size[Ru];
    }
};



int main () {
	//fastIO();


    int n, m, q; cin>>n>>m>>q;

    forn(i, n) cin>>a[i];


    vector< tuple<int,int,int> > edges(m);

    for(auto &[u, v, w]: edges) cin>>u>>v>>w;
    for(auto &[u, v, w]: edges) u--, v--;

    DSU dsu(n);
    vector< int > initial_values(q);
    forn(i, q){
        int u, w; cin>>u>>w; u--;
        queries[u].insert({w, i});
        initial_values[i] = w;
    }

    sort(all(edges), [](auto a, auto b){
        auto [u_1, v_1, w_1] = a;
        auto [u_2, v_2, w_2] = b;
        return w_1 < w_2;
    });


    vector<lli> ans(q);
    for(auto [u, v, w]: edges){
        vector<int> out_u, out_v;
        u = dsu.root(u);
        v = dsu.root(v);

        if(dsu.root(u) == dsu.root(v)) continue;

        while(!queries[u].empty() && queries[u].begin()->first + dsu.sum[u] < w){
            auto itr = queries[u].begin();
            out_u.push_back(itr->second);
            queries[u].erase(itr);
        }

        while(!queries[v].empty() && queries[v].begin()->first + dsu.sum[v] < w){
            auto itr = queries[v].begin();
            out_v.push_back(itr->second);
            queries[v].erase(itr);
        }

        for(auto idx: out_u) ans[idx] = dsu.sum[u] + initial_values[idx];
        for(auto idx: out_v) ans[idx] = dsu.sum[v] + initial_values[idx];
    
        dsu.join(u, v);
    }


    vector<int> out_u;
    int u = dsu.root(0);
    while(!queries[u].empty()){
        auto itr = queries[u].begin();
        out_u.push_back(itr->second);
        queries[u].erase(itr);
    }
    for(auto idx: out_u) ans[idx] = dsu.sum[u] + initial_values[idx];


    for(auto x: ans) cout << x << endl;




	return 0;
}

