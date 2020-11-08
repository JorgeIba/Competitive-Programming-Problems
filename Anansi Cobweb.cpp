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

#define Edge pair<int,int>

struct UnionFind{
    int n;
    vector<int> parent, size;

    UnionFind(int N): n(N), parent(N+1), size(N+1, 1){
        while(N--) parent[N] = N;
    }

    int find(int u)
    {
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(size[a] < size[b]) swap(a, b);
        n--; parent[b] = a;
        size[a] += size[b];
    }
};


int main () {
	fastIO();
    int n, m; cin>>n>>m;
    vector<Edge> edges(m);
    for(int i = 0; i<m; i++)
    {
        cin>>edges[i].first>>edges[i].second;
    }
    int q; cin>>q;
	vector<int> idxEdges(q);
    vector<bool> idxDo(m, true);

    for(auto &i: idxEdges)
    {
        cin>>i; i--;
        idxDo[i] = false;
    } 

    UnionFind U(n);

    for(int i = 0; i<m; i++)
    {
        if(idxDo[i]) U.join(edges[i].first, edges[i].second);
    }
    
    reverse(all(idxEdges));

    vector<int> ans(q);
    for(int i = 0; i<q; i++)
    {
        ans[i] = U.n;
        U.join(edges[idxEdges[i]].first,  edges[idxEdges[i]].second);
    }
    reverse(all(ans));

    for(auto x: ans) cout << x << " ";
    cout << endl;
    

    
	return 0;
}