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


const int MAXN = 1e6 + 100;
const int MAX_ANS = 20;
const int MOD = 982448893;
const int L_BRACKET = 961757387, X = 329457251, R_BRACKET = 961748941;

vector<int> adjList[MAXN];
vector<int> adjAns[MAXN];

int sizes[MAXN];
int hashes[MAXN];
int parent[MAXN];
int invHash[MAXN];

int powerMod(int a, int b){
    int res = 1;
    while(b){
        if(b&1) res = 1LL * res * a % MOD;
        b >>= 1;
        a = 1LL * a * a % MOD;
    }
    return res;
}

void dfs_prec(int u, int p = -1){
    parent[u] = p;
    sizes[u] = 1;
    for(auto v: adjList[u]){
        if(v == p) continue;

        dfs_prec(v, u);
        sizes[u] += sizes[v];
    }
}

void dfs_hash(int u, int p = -1){
    int middle = 1;
    for(auto v: adjList[u]){
        if(v == p) continue;

        dfs_hash(v, u);
        middle = 1LL * middle * (X - hashes[v] + MOD) % MOD;
    }

    int hash = 1LL * L_BRACKET * middle % MOD * R_BRACKET % MOD;
    hashes[u] = hash;
    invHash[u] = powerMod((X - hash + MOD) % MOD, MOD-2);
}


int mark[MAXN];
void dfs_mark(int u){
    mark[u] = 1;
    for(auto v: adjList[u]){
        if(v == parent[u]) continue;
        dfs_mark(v);
    }
}

vector< array<int,3> > options_subtree[MAXN];

const int ON = 0;
const int CHILD = 1;

int main () {
	fastIO();

    int n; cin>>n;
    
    forn(i, n-1){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    if(n == 2){
        cout << 1 << " " << 2 << endl;
        return 0;
    }


    dfs_prec(0, 0);
    dfs_hash(0);

    set<int> all_hashes;
    forn(i, n)
        all_hashes.insert(hashes[i]);

    vector<int> options(n);
    iota(all(options), 0);

    sort(all(options), [&](auto u, auto v){
        return sizes[u] < sizes[v];
    });

    for(auto root: options){
        if(sizes[root] > MAX_ANS) break;

        int option_1 = 1LL * hashes[root] * (X - 1LL * L_BRACKET * R_BRACKET % MOD + MOD) % MOD;
        int option_2 = 1LL * L_BRACKET * (X - hashes[root] + MOD) % MOD * R_BRACKET % MOD;

        vector< array<int, 3> > options_root;
        options_root.push_back({CHILD, root, option_1});
        options_root.push_back({ON, root, option_2});

        for(auto v: adjList[root]){
            if(v == parent[root]) continue;

            for(auto [typee, w, hash_opt]: options_subtree[v]){
                int hash = hashes[root];
                
                hash = 1LL * hash * invHash[v] % MOD;
                hash = 1LL * hash * (X - hash_opt + MOD) % MOD;
            
                options_root.push_back({typee, w, hash});
            }
        }

        options_subtree[root] = options_root;

        for(auto [typee, w, hash_opt]: options_root){
            if(!all_hashes.count(hash_opt)) {
                if(root == 0) continue;

                dfs_mark(root);

                // int ans = sizes[root];
                // debugg(ans);

                int last = -1;
                forn(i,n){
                    if(!mark[i]) last = i;
                }
                assert(last != -1);

                mark[last] = 1;
                parent[root] = -1;
                if(typee == ON){
                    parent[last] = parent[w];
                    parent[w] = last;
                } else {
                    parent[last] = w;
                }

                vector<int> res;
                forn(i, n){
                    if(!mark[i]) res.push_back(i);
                    else if(parent[i] != -1)
                        adjAns[parent[i]].push_back(i);
                }

                int new_root;
                forn(i, n){
                    if(mark[i] && parent[i] == -1) new_root = i;
                }

                forn(i, SZ(res)){
                    auto v = res[i];
                    parent[new_root] = v;
                    adjAns[v].push_back(new_root);
                    new_root = v;
                }

                vector<int> mapp(n);
                iota(all(mapp), 0);
                swap(mapp[new_root], mapp[0]);

                forn(i, n){
                    for(auto v: adjAns[i]){
                        cout << mapp[i]+1 << " " << mapp[v]+1 << endl;
                    }
                }
                return 0;
            }
        }
    }

	
	return 0;
}