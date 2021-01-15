#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.sz())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;
const int mxn = (int)1e5+10;
vector<lli> adj[mxn];
vector<char> letter;

int n,pos,_id;
int level[mxn];
int sz[mxn];
int parent[mxn];
int nodePos[mxn];
int chHead[mxn];
int DP[mxn][21];
int euler[mxn];
lli potP[mxn]; 

lli P = 31, MOD = 1e9+7; //Pa la mamada del hashing

struct Node{
  lli hash = 0, inv_hash = 0, sz = 0;
  Node(): hash(0), inv_hash(0), sz(0) {}
  Node(lli hash, lli inv_hash, lli sz): hash(hash), inv_hash(inv_hash), sz(sz) { }
};


Node Merge(Node A, Node B)
{
  lli size1 = A.sz, size2 = B.sz;
  lli hash1 = A.hash, hash2 = B.hash;
  lli inv_hash1 = A.inv_hash, inv_hash2 = B.inv_hash;
  
  lli new_size = size1 + size2;
  lli new_hash = (hash1 + (potP[size1]*hash2%MOD))%MOD;
  lli new_inv_hash = ((potP[size2]*inv_hash1%MOD) + inv_hash2)%MOD;
  return Node(new_hash, new_inv_hash, new_size);
}

vector<Node> ST;

void updateST(lli id, lli l, lli r, lli start, lli end,  char value)
{
  if(start > r || end < l)
  {
      return;
  }
  if(l == r)
  {
    ST[id] = Node(value, value, 1);
    return;
  }
  else  
  {
        lli mid = l + (r-l)/2;
        updateST(2*id, l, mid, start, end, value);
        updateST(2*id+1, mid+1, r, start, end, value);
        ST[id] = Merge(ST[2*id], ST[2*id+1]);
    }
}


Node queryST(lli id, lli l, lli r, lli start, lli end)
{
    if(end  < l || r < start) return Node(0,0,0);
    if(start <= l && r<= end)
    {
        return ST[id];
    }
    else
    {
        lli mid = l + (r-l)/2;
        return Merge(queryST(2*id, l, mid, start, end), queryST(2*id+1, mid+1, r, start, end));
    }
}


int LCA(int p, int q){
  if(level[p] < level[q]) swap(p,q);
  int lg;
  for(lg = 1; (1<<lg) <= level[p]; ++lg);
  lg--;
  for(int i = lg; i>= 0; --i){
    if(level[p]-(1<<i) >= level[q]){
      p = DP[p][i];
    }
  }
  if(p == q) return p;
  for(int i = lg; i>= 0; --i){
    if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
      p = DP[p][i];
      q = DP[q][i];
    }
  }
  return parent[p];
}

int get_parent(int p, int k){
  int h = level[p]-k;
  if(h < 0) return -1;
  int lg;
  for(lg = 1; (1<<lg) <= level[p]; ++lg);
  lg--;
  for(int i = lg; i >= 0; --i){
    if(level[p] - (1<<i) >= h){
      p = DP[p][i];
    }
  }
  return p;
}
int dfs(int u, int p, int lvl){
  euler[u] = _id++;
	parent[u] = p;
	sz[u] = 1;
	level[u] = lvl;
	for(auto v:adj[u]){
		if(v == p) continue;
		sz[u] += dfs(v,u,lvl+1);
	}
	return sz[u];
}
void precal(){
  potP[0] = 1;
  for(int i = 1; i < mxn; i++) potP[i] = (potP[i-1]*P)%MOD;
  for(int u = 0; u < n; u++)
    DP[u][0] = parent[u];
  for(int i = 1; (1<<i) <= n; ++i){
    for(int u = 0; u < n; u++)
      DP[u][i] = DP[DP[u][i-1]][i-1];
  }
}
void HLD(int u, int ch){
	chHead[u] = ch;
	nodePos[u] = pos++;
	int mx,hNode;
	mx = 0; hNode = -1;
	for(auto v:adj[u]){
		if(v == parent[u]) continue;
		if(sz[v] > mx){
			mx = sz[v];
			hNode = v;
		}
	}
	if(mx)
		HLD(hNode,ch);
	for(auto v:adj[u]){
		if(v == parent[u] || v == hNode) continue;
		HLD(v,v);
	}
}

void buildHLD(int root){
  ST.resize(4*n+10);
	dfs(root,-1,0);
	HLD(root,root);
  precal();
  //aqui se construye el st con los hash
	for(int i = 0; i < n; i++)
    updateST(1,1,n,nodePos[i]+1, nodePos[i]+1, letter[i]);
}

Node queryHLD(int u, int v){
  Node ans(0,0,0);
	while(chHead[u] != chHead[v]){
		if(level[chHead[u]] < level[chHead[v]])
			swap(u,v);
      
        Node aux = queryST(1, 1, n, nodePos[chHead[u]]+1,nodePos[u]+1);
        swap(aux.hash,aux.inv_hash);
        ans = Merge(ans, aux);

		u = parent[chHead[u]];
	}
	if(level[u] > level[v])
		swap(u,v);

    Node aux = queryST(1, 1, n, nodePos[u]+1,nodePos[v]+1);
    swap(aux.hash,aux.inv_hash);
    ans = Merge(ans, aux);
	return ans;
}



bool query(int u, int v){
  lli lca = LCA(u,v);
  if(lca == v || lca == u){
    if(lca ==  u) swap(u,v);
    auto ANS = queryHLD( u,  v);
    //cout << ANS.hash << " " << ANS.inv_hash << " " << ANS.sz << " " << ANS.s << endl;  
    return ANS.hash == ANS.inv_hash;
  }
  auto L = queryHLD(u, lca); // 0 por la izquierda

  lli diff = level[v] - level[lca];

  lli uno_antes = get_parent(v, diff-1);
  assert(uno_antes != -1);
  auto R = queryHLD(v, uno_antes); // 1 por la derecha
  
  swap(R.hash,R.inv_hash);

  auto ANS = Merge(L, R);
  //cout << ANS.hash << " " << ANS.inv_hash << " " << ANS.sz << " " << ANS.s << endl;
  return ANS.hash == ANS.inv_hash;
}


int main () {
    fastIO();
  lli q; cin>>n>>q;
  string s; cin>>s;
  letter.resize(n);
  for(int i = 0; i<n; i++) letter[i] = s[i];

  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  buildHLD(0);
  for(int i = 0; i<q; i++)
  {
    int t; cin>>t;
    if(t == 1)
    {
      int u, v; cin>>u>>v; u--, v--;
      if(euler[v] < euler[u])
        swap(u,v);
      if(query(u, v))
        cout << "Yes\n";
      else
        cout << "No\n";
    }
    else
    {
      int idx; char c; cin>>idx>>c;
      idx--;
      updateST(1,1,n,nodePos[idx]+1, nodePos[idx]+1, c);
    }
  }

  return 0;
}

/*
5 1
ufpsp
1 2
1 3
1 4
4 5
1 5 2*/

/*
9 7
abacabapk
1 4
2 1
2 5
1 6
7 6
3 6
5 8
4 9 
1 9 8
1 8 9
1 8 8
1 8 3 
1 8 6
1 6 8
1 7 2
*/