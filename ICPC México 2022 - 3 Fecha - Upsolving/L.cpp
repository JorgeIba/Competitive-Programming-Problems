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


const lli maxN = 1e5+10;
vector<lli> frAll(maxN);
vector<lli> colors(maxN);
vector< vector<lli> > adjList(maxN);
vector< map<lli,lli> > frU(maxN);
map< pair<lli,lli>, lli > ansForEdge;

lli dfs(lli u, lli parent) {
	lli greatestChild = -1, szGreatest = -1;
	lli ans = 0;
	lli sub = 0;
	lli color_u = colors[u];
	for(auto v: adjList[u]) {
		if(v == parent) continue;
		ans += dfs(v, u);
		
		if(SZ(frU[v]) > szGreatest) {
			greatestChild = v;
            szGreatest = SZ(frU[v]);
		}

		sub += frU[v][color_u];
	}
	
	if(greatestChild != -1) swap(frU[u], frU[greatestChild]);
	
	
	for(auto v: adjList[u]) {
		if(v == greatestChild) continue;
		for(auto [color, freq]: frU[v]) {
			sub += frU[u][color]*freq*2;
			frU[u][color] += freq;
		}
	}
	
	frU[u][color_u]++;
	ans += (frAll[color_u] - frU[u][color_u]);
	
	if(parent != -1) {
		ansForEdge[{u,parent}] = ans-sub;
		ansForEdge[{parent,u}] = ans-sub;
	}
    

	return ans - sub;
}

int main () {
	fastIO();

    lli n; cin>>n;

    for(int i = 1; i <= n; i++){
        cin>>colors[i];
	frAll[colors[i]]++;
    }
    
    vector<pair<lli,lli>> edges(n-1);

    for(auto &e: edges){
        cin>>e.first>>e.second;
        adjList[e.first].push_back(e.second);
        adjList[e.second].push_back(e.first);
    }

    dfs(1, -1);

    for(auto e: edges) {
	    cout << ansForEdge[{e.first, e.second}] << " ";
    }
    cout << endl;

	return 0;
}
