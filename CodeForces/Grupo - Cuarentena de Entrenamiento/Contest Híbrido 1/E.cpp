#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

/*
vector<lli> costs;
lli f(lli idx) {
    if(idx > SZ(costs)) return 0;

    

    return min({f(idx+1), f(idx+2), f(idx+3)}) + costs[idx];
}
*/

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;


// Complejidad: O((m + k) * log(n))
// Probado solo cuando u < v para todas las aristas (u->v)

struct Node {
	ii val;
	Node *izq, *der;
	
	Node () : val(ii(0, 0)), izq(0), der(0) {}
	Node (const ii &val) : val(val), izq(0), der(0) {}
	Node (Node *t) { *this = *t; }
};

const lli MX = 250005;
lli n, k;
ll a[MX], dis[MX], p[MX], vis[MX];
vi q;
vii adj[MX];
Node *pq[MX];

Node * merge (Node *a, Node *b) {
	if (!a) return b;
	if (!b) return a;
	
	if (a->val > b->val) swap(a, b);
	
	Node *nt = new Node(a);
	if (rand() % 2) nt->der = merge(nt->der, b);
	else nt->izq = merge(nt->izq, b);
	
	return nt;
}

Node * pop (Node * a) {
	return merge(a->izq, a->der);
}

void dij (lli s) {
	memset(dis, -1, sizeof(dis));
	dis[s] = 0;
	priority_queue<ii, vii, greater<ii>> pq;
	pq.emplace(0, s);
	
	while (pq.size()) {
		lli u = pq.top().se;
		ll d = pq.top().fi;
		pq.pop();
		
		if (dis[u] < d) continue;
		
		for (ii &v : adj[u]) {
			ll w = d + v.se;
			if (dis[v.fi] == -1 || dis[v.fi] > w) {
				dis[v.fi] = w;
				p[v.fi] = u;
				pq.emplace(w, v.fi);
			}
		}
	}
}

void dfs (lli u) {
	vis[u] = 1;
	for (ii &v : adj[u])
		if (!vis[v.fi])
			dfs(v.fi);
	q.pb(u);
}

// Nodos indexados en cero
typedef pair<ll, Node*> tin;
vi klp (lli s, lli t, lli k) {
	dij(s);
	
	dfs(s);
	reverse(all(q));
	
	for (lli u : q) {
		for (ii &v : adj[u])
			if (p[v.fi] == u)
				pq[v.fi] = merge(pq[v.fi], pq[u]);
			else {
				Node *nt = new Node(ii(dis[u] + v.se - dis[v.fi], u));
				pq[v.fi] = merge(pq[v.fi], nt);
			}
	}
	
	vi res = {dis[t]};
	k--;
	priority_queue<tin, vector<tin>, greater<tin>> hp;
	if (pq[t]) hp.emplace(dis[t] + pq[t]->val.fi, pq[t]);
	
	while (k && hp.size()) {
		ll d = hp.top().fi;
		Node *t = hp.top().se;
		hp.pop();
		
		res.pb(d);
		k--;
		
		lli v = t->val.se;
		if (pq[v]) hp.emplace(d + pq[v]->val.fi, pq[v]);
		
		d -= t->val.fi;
		t = pop(t);
		if (t) hp.emplace(d + t->val.fi, t);
	}
	
	while (k--)
		res.pb(-1);
	
	return res;
}



int main () {
	//fastIO();

    lli n, k; cin>>n>>k;

    vector<lli> costs(n+1);
    for(int i = 1; i <= n; i++)
        cin>>costs[i];


    // cout << min(f(0), f(1)) << endl;

    vector< vector<pair<lli,lli>> > adjList(n+5);

    for(int i = 1; i <= n; i++) {
        if(i-1 > 0) adj[i-1].push_back({i, (i <= n ? costs[i] : 0)});
        if(i-2 > 0) adj[i-2].push_back({i, (i <= n ? costs[i] : 0)});
        if(i-3 > 0) adj[i-3].push_back({i, (i <= n ? costs[i] : 0)});
    }

    if(1 <= n) adj[0].push_back({1, costs[1]});
    if(2 <= n) adj[0].push_back({2, costs[2]});

    if(n > 0) adj[n].push_back({n+1, 0});
    if(n-1 > 0) adj[n-1].push_back({n+1, 0});


    lli s = 0, t = n+1;

    /*
    for(int i = s; i <= t; i++) {
        cout << i << ":\n";
        for(auto x: adj[i]) cout << x.first << " - " << x.second << "   ";
        cout << endl;
    }
    */

    
    auto ans = klp(s, t, k);

    for(auto x: ans) cout << x << endl;


	return 0;
}

