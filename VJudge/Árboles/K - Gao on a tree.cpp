#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

//* WAVELET //////////////////////////
struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<lli> freq;

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<lli>::iterator from, vector<lli>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		int m = (lo + hi) / 2;
		if(k <= m) return left->equalTo(lb + 1, rb, k);
		else return right->equalTo(l - lb, r - rb, k);
	}
};

//* FIN WAVELET ///////////////////////////////

struct Edge{
    lli v;
    Edge(lli v): v(v) {}
    Edge(): v(0){}
};

vector< vector< Edge* > > adjList;
vector< lli > colors, chainHead, parent, colorArray, idWavelet, depth, szTree;
lli cnt = 0;


void addEdge(lli u, lli v)
{
    Edge *uv = new Edge(v);
    Edge *vu = new Edge(u);
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

void prep(lli n)
{
    adjList.clear(); adjList.resize(n+1);
    colors.clear(); colors.resize(n+1);
    chainHead.clear(); chainHead.resize(n+1);
    parent.clear(); parent.resize(n+1);
    colorArray.clear(); colorArray.resize(n+1);
    idWavelet.clear(); idWavelet.resize(n+1);
    depth.clear(); depth.resize(n+1);
    szTree.clear(); szTree.resize(n+1);
    cnt = 0;
}

void dfs(lli u, lli p)
{
    szTree[u] = 1;
    parent[u] = p;
    for(Edge* E: adjList[u])
    {
        lli v = E->v;
        if(v != p)
        {
            depth[v] = depth[u] + 1;
            dfs(v,u);
            szTree[u] += szTree[v];
        }
    }
}

void getHLD(lli u, lli chain)
{
    chainHead[u] = chain;
    idWavelet[u] = cnt;
    colorArray[cnt++] = colors[u];

    lli maxSize = -1, index = -1;
    for(Edge* E: adjList[u])
    {
        lli v = E->v;
        if(v != parent[u] && szTree[v] > maxSize)
        {
            maxSize = szTree[v];
            index = v;
        }
    }

    if(maxSize != -1) getHLD(index, chain);

    for(Edge* E: adjList[u])
    {
        lli v = E->v;
        if(v!= parent[u]  &&  v!= index)
        {
            getHLD(v, v);
        }
    }
}

lli queryU(lli u, lli v, lli c, WaveletTree &w)
{
    lli res = 0;
    while( chainHead[u]  !=  chainHead[v] )
    {
        if(depth[ chainHead[u] ]  < depth[ chainHead[v] ]) swap(u,v);
        res += w.equalTo( idWavelet[ chainHead[u] ]+1, idWavelet[u]+1, c);
        u = parent[ chainHead[u]  ];
    }

    if(depth[u] > depth[v]) swap(u,v);

    res += w.equalTo( idWavelet[u]+1, idWavelet[v]+1, c);

    return res;
}



void solve(lli n, lli q)
{
    prep(n);
    for(int i = 1; i<=n; i++)
    {
        cin>>colors[i];
    }
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        addEdge(u,v);
    }
    dfs(1, 1);
    getHLD(1,1);
    vector<lli> aux = colorArray;
    WaveletTree w(all(aux), *min_element(all(aux)), *max_element(all(aux)) );
    
    while(q--)
    {
        lli u, v, c; cin>>u>>v>>c;
        if( queryU(u,v,c,w) > 0 )
        {
            cout<<"Find\n";
        }
        else
        {
            cout<<"NotFind\n";
        }   
    }
    cout<< endl ;

}


int main()
{
    fastIO();
    lli n, m;
    while(cin>>n>>m)
    {
        solve(n,m);
    }
    return 0;
}