#pragma GCC optimize("O3")
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

vector<tuple<int,int,int>> adjList[MAXN];
int pref[MAXN];
int disc[MAXN];
int Time = 1;

int sz_cycles = 0;
int cycles[MAXN];

void dfs_base(int u, int idx_p = -1){
    disc[u] = Time++;

    for(auto [v, w, idx_v]: adjList[u]){
        if( idx_v == idx_p ) continue;

        if(!disc[v]){
            pref[v] = pref[u] ^ w;
            dfs_base(v, idx_v);
        } else {
            if(disc[v] <= disc[u]) {
                cycles[sz_cycles++] = pref[u] ^ pref[v] ^ w;
                // cycles.push_back(pref[u] ^ pref[v] ^ w);
            }
        }
    }
}


const int LOG_D = 30;
vector<int> basis(LOG_D); 
int sz_basis = 0;

void insert_vector(int mask, bool zeros = false){
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++){
				if(j==i) continue;
				if(j < i){
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}

struct Node{
    int fr[LOG_D][2];
    int ans = 0;

    Node(){
        memset(fr, 0, sizeof(fr));
    }
    Node(int x){
        memset(fr, 0, sizeof(fr));
        forn(i, LOG_D){
            if(x & (1LL << i))
                fr[i][1]++;
            else 
                fr[i][0]++;
        }
            
    }

    Node operator+(Node &b) {
        Node aux;
        forn(i, LOG_D){
            forn(j, 2){
                aux.fr[i][j] = fr[i][j];
            }
        }

        aux.ans = ans ^ b.ans;

        for(int i = LOG_D-1; i >= 0; i--){
            lli time_appears_0 = aux.fr[i][1] * b.fr[i][1] + aux.fr[i][0] * b.fr[i][0];
            if(time_appears_0 & 1){
                aux.ans ^= basis[i];
            }

            aux.fr[i][0] += b.fr[i][0];
            aux.fr[i][1] += b.fr[i][1];
        }
        return aux;
    }
};


template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;

    T NEUTRO;

	DisjointSparseTable(vector<T> &arr, T neutro): NEUTRO(neutro){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = NEUTRO;
			for(int i = 0; i < N; ++i){
                acum = acum + arr[i];
				left[j][i] = acum;
				if((i & mask) == mask) acum = NEUTRO;
			}
			acum = NEUTRO; 
			for(int i = N-1; i >= 0; --i){
				acum = arr[i] + acum;
				right[j][i] = acum;
				if((i & mask) == 0) acum = NEUTRO; 
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return right[i][l] + left[i][r];
	}
};



int main () {
	fastIO();
	
    int n, m, q; cin>>n>>m>>q;

    forn(i, m) {
        int u, v, w; cin>>u>>v>>w; u--, v--;
        adjList[u].push_back({v, w, i});
        adjList[v].push_back({u, w, i});
    }

    dfs_base(0);
    forn(i, sz_cycles){
        insert_vector(cycles[i], true);
    }
    

    vector< int > pref_of_pref(n);
    vector<Node> nodes(n);
    forn(i, n){
        nodes[i] = Node( pref[i] );
        pref_of_pref[i] = pref[i];
        if(i)
            pref_of_pref[i] = pref_of_pref[i] ^ pref_of_pref[i-1];
    }
    auto get_pref = [&](int l, int r){
        return pref_of_pref[r] ^ (l ? pref_of_pref[l-1] : 0);
    };


    DisjointSparseTable<Node> SPT(nodes, Node());

    while(q--){
        int l, r; cin>>l>>r; l--, r--;

        int ans = SPT.query(l, r).ans;

        if((r-l)&1){
            ans ^= get_pref(l, r);
        }

        cout << ans << endl;
    }

	return 0;
}

