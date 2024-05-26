#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector<lli> heights;
vector< vector<int> > adjList;

const lli INF = LLONG_MAX;
vector<lli> dijkstra(int s){
    int n = SZ(adjList);
    vector<lli> dist(n, -1);  

    priority_queue< pair<lli,lli>, vector<pair<lli,lli>>, greater<pair<lli,lli>> > pq;
    pq.push({0, s});

    dist[s] = 0;

    while(!pq.empty()){
        auto [dist_u, u] = pq.top(); pq.pop();

        if(dist_u != dist[u]) continue;

        for(auto v: adjList[u]){
            lli w = (heights[u] - heights[v]) * (heights[u] - heights[v]);
            if(dist[v] == -1 || dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

 
struct Line {
	mutable lli k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(lli x) const { return p < x; }
};

// Works for maximum
// If you want minimum, multiply m and b for -1, and 
// multiply for -1 the query
struct LineContainer : multiset<Line, less<>> {
	const lli INF = LLONG_MAX;
	lli div(lli a, lli b) { 
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = INF; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(lli k, lli m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	lli query(lli x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main () {
	fastIO();
    int n, m, s, t; cin>>n>>m>>s>>t; s--, t--;
    heights.resize(n);
    adjList.resize(n);

    for(auto &x: heights) cin>>x;

    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    auto distS = dijkstra(s);
    auto distT = dijkstra(t);
    




    vector< LineContainer* > Hulls(n);
    for(int i = 0; i < n; i++) Hulls[i] = new LineContainer();


    for(int u = 0; u < n; u++){
        for(auto v: adjList[u]){
            Hulls[v]->add( 2*heights[u],  -( 2*distS[u] + heights[u] * heights[u]) );
        }
    }


    lli ans = INF;
    for(auto v: adjList[s]) 
        ans = min(ans, 2*distT[v]);

    for(auto v: adjList[t]) 
        ans = min(ans, 2*distS[v]);

    for(int u = 0; u < n; u++){
        lli aux = -INF;
        for(auto v: adjList[u]){
            aux = max(aux, Hulls[v]->query(heights[u]));
        }
        lli best = 2*distT[u] + heights[u]*heights[u] - aux;
        lli ans_u = min( 2*(distS[u] + distT[u]), best);
        ans = min(ans, ans_u);
    }

        
    cout << fixed << setprecision(15);
    cout << (ld) 0.5 * ans << endl;


	return 0;
}

