#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool Q = 0;
struct Line {
	mutable lli m, b, x;
 
	bool operator < (const Line L) const {
		return Q ? x < L.x : m < L.m; 
	}
};
const lli INF = numeric_limits<lli>::max();
struct Hull : multiset<Line> {

    lli ceil (lli a, lli b) { if (a < 0 != b < 0) return a / b; return (abs(a) + abs(b) - 1) / abs(b); }
    
    lli intersection (const Line &p, const Line &q) { return ceil(q.b - p.b, p.m - q.m); }
	bool valid (auto it) {
		if (it == begin()) {
			auto sig = it;
			sig++;
			if (sig != end()) sig->x = intersection(*it, *sig);
			return it->x = -INF;
		}
		auto ant = it, sig = it;
		ant--, sig++;
		if (sig == end()) { it->x = intersection(*it, *ant); return 1;}
		lli x = intersection(*it, *ant); 
		lli y = intersection(*it, *sig);
 
		if (x > y) return 0;
		it->x = x, sig->x = y;
		return 1;
	}
 
	void add (lli m, lli b) {
		auto it = lower_bound({m, b, -INF}); 
		
        if (it != end() && it->m == m) { 
			if (it->b > b) return; 
			it->b = b; 
		} else { it = insert({m, b, -INF}); }
 
		if (!valid(it)) { erase(it); return; }
 
		auto ant = it;
		while (ant != begin()) { 
			if (valid(--ant)) break;
			erase(ant);
			if (it == begin()) { it->x = -INF; break; }
			ant = it;
		}
 
		auto sig = it;
		sig++;
		while (sig != end() && !valid(sig))
			erase(sig++);
	}
 
	lli query (lli x) {
		if (empty()) return 0; 
 
		Q = 1;
		auto it = upper_bound({0, 0, x});
		it--;
		Q = 0;
		return x * it->m + it->b;
	}
};

vector< lli > a, b, dp;
vector< Hull > Hulls;
vector< vector< lli > > adjList;

void prep(lli n)
{
    a.resize(n+1);
    b.resize(n+1);
    adjList.resize(n+1);
    dp.resize(n+1);
    Hulls.resize(n+1);
}

bool isLeaf(lli u)
{
    return (adjList[u].size() == 1) && (u != 1);
}

void dfs(lli u, lli p)
{
    for(auto v: adjList[u])
    {
        if( v!= p )
        {
            dfs(v, u);
            if(Hulls[u].size() < Hulls[v].size())
            {
                swap(Hulls[u], Hulls[v]);
            }
            for(auto L: Hulls[v])
            {
                Hulls[u].add(L.m, L.b);
            }
        }
    }
    if(isLeaf(u))
    {
        Hulls[u].add(-b[u], 0);
    }
    else
    {
        dp[u] = Hulls[u].query(a[u]);
        Hulls[u].add(-b[u], dp[u]);
    }
}


int main()
{
    fastIO();
    lli n; cin>>n;
    prep(n);
    for(int i = 1; i<=n; i++) cin>>a[i];
    for(int i = 1; i<=n; i++) cin>>b[i];

    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs(1, -1);

    for(int i = 1; i<=n; i++)
    {
        cout << (-dp[i]) << " ";
        //cout << Hulls[i].size() << " ";
    }
    //cout << Hulls[3].size() << endl;
    //cout << Hulls
    

    return 0;
}