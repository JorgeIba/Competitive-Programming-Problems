#include <bits/stdc++.h>
#define lli long long int
#define SZ(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define FastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const lli maxN = 2*1e5+50;
lli colors[maxN];
vector< vector<lli> > adjList;

vector< set<lli> > ss;
lli ans = 0;
vector<lli> prefixXOR;

void dfsPrefix(int u, int parent) {
    prefixXOR[u] = (parent > 0 ? prefixXOR[parent] : 0) ^ colors[u];
    for(auto v: adjList[u]) {
        if(v != parent)
            dfsPrefix(v, u);
    }
}


void dfs(int u, int parent) {
	int biggest = -1;
	for(auto v: adjList[u])
	{
		if(parent == v) continue;
		dfs(v, u);
		if(biggest == -1 || SZ(ss[v]) > SZ(ss[biggest]))
			biggest = v;
	}

	if(biggest != -1) swap(ss[u], ss[biggest]);

	bool flag = false;
	for(auto v: adjList[u]) {
		if( v == biggest ) continue;
		for(auto prefixColor: ss[v]) {
			lli val = colors[u] ^ prefixColor;
			if( ss[u].count(val) ){
				flag = true;
			}
		}
		ss[u].insert(all(ss[v]));
	}

    flag = flag || ( ss[u].count(colors[u] ^ prefixXOR[u]) );


	if(flag) {
		ans++;
		ss[u].clear();
	} else {
		ss[u].insert(prefixXOR[u]);
	}
	return;
}


int main()
{
    FastIO();
	int n; cin>>n;
	adjList.resize(n+1);
	ss.resize(n+1);
    prefixXOR.resize(n+1);

	for(int i = 1; i <= n; i++) {
		cin>>colors[i];
	}

	for(int i = 0; i < n-1; i++) {
		int u, v; cin>>u>>v;
		adjList[u].push_back(v);
		adjList[v].push_back(u); 
	}

    dfsPrefix(1, -1);

	dfs(1, -1);
	cout << ans << endl;
	

	return 0;
}
