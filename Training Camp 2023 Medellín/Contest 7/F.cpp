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


const int MAXN = 1e5+100;

vector<int> adjList[MAXN + 100];

int sizes[MAXN];
lli ways[MAXN];
int children[MAXN][2];
int weight[MAXN];
int parent[MAXN];

int n; 
void dfs_1(int u, int p = -1){
    parent[u] = p;
    sizes[u] = 1;
    int t = 0;
    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_1(v, u);

        children[u][t++] = sizes[v];
        sizes[u] += sizes[v];
    }

    lli ways_1 = 1LL * children[u][0] * (n - sizes[u]);
    lli ways_2 = 1LL * children[u][1] * (n - sizes[u]);
    lli ways_3 = 1LL * children[u][0] * children[u][1];
    lli ways_4 = n-1;
    
    ways[u] = 2*(ways_1 + ways_2 + ways_3 + ways_4) + 1;
}


void main_(){
    cin>>n;

    forn(i, n) adjList[i].clear();
    fill(sizes, sizes + n, 0);
    fill(ways, ways + n, 0);
    forn(i, n) children[i][0] = children[i][1] = 0;
    fill(parent, parent+n, -1);


    forn(i, n) cin>>weight[i];
    forn(i, n-1){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs_1(0);


    lli S = 0;
    forn(i, n){
        S += ways[i] * weight[i];
    }

    if(S == 0){
        cout << 0 << endl;
        return;
    }

    forn(i, n){
        if(ways[i] == 0) continue;
        if(S % ways[i] == 0) {
            cout << 1 << " " << i+1 << endl;
            return;
        }
    }

    forn(i, n){
        if(children[i][0] == children[i][1] && children[i][1] == 1){
            cout << 2 << " " << i+1 << " ";
            for(auto v: adjList[i]){
                if(v == parent[i]) continue;
                cout << v+1;

                assert(gcd(ways[i], ways[v]) == 1);
                break;
            }
            cout << endl;
            return;
        }
    }

    assert(false);
    return;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

