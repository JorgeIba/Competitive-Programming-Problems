#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


template<typename T>
struct FenwickTree{
	int n;
    vector< vector<T> > bit;

    FenwickTree(int n): n(n) {
        bit.assign(2, vector<T>(n+1));
    }
    T get(int x, int i) {
        T ret = 0;
        for (; i; i -= i&-i) ret += bit[x][i];
        return ret;
    }
    void add(int x, int i, T val) {
        for (; i <= n; i += i&-i) bit[x][i] += val;
    }
    T get2(int p) {
        return get(0, p) * p + get(1, p);
    }
    T query(int l, int r) {
        return get2(r+1) - get2(l);
    }
    void update(int l, int r, T x) {
        add(0, l+1, x), add(0, r+2, -x);
        add(1, l+1, -x*l), add(1, r+2, x*(r+1));
    }
};


const int MAXN = 1e5 + 100;
const int LOG = 18;

vector<int> adjList[MAXN];
array<int,2> Ranges[MAXN];
int Time = 0;

FenwickTree<lli> *FW1, *FW2;
lli updates_children[MAXN][LOG];

int parent[MAXN];
int depth[MAXN];
vector<int> order_per_depth[MAXN];

void dfs_euler(int u){

    order_per_depth[depth[u]].push_back(Time);
    Ranges[u][0] = Time++;
    
    for(auto v: adjList[u]){
        depth[v] = depth[u] + 1;
        dfs_euler(v);
    }

    Ranges[u][1] = Time-1;
}

vector<int> get_children_by_level(int u){
    vector<int> child_per_level;
    for(int level = depth[u]; level < depth[u] + LOG; level++){
        auto itr_l = lower_bound(all( order_per_depth[level] ), Ranges[u][0]);
        auto itr_r = upper_bound(all( order_per_depth[level] ), Ranges[u][1]);
        child_per_level.push_back(itr_r - itr_l);
    }
    return child_per_level;
}

void updateOne(int x, int y){
    FW1->update(Ranges[x][0], Ranges[x][1], y);
}

void updateMore(int x, int y, int k){
    auto child_per_level = get_children_by_level(x);

    lli curr_val = y;
    lli sum = 0;
    for(int off = 0; off < LOG; off++){
        updates_children[x][off] += curr_val;
        sum += curr_val * child_per_level[off];
        curr_val /= k;
    }

    FW2->update(Ranges[x][0], Ranges[x][0], sum);
}


lli get_ans(int x){

    lli ans = 0;

    { // Query of all updates with k = 1
        ans += FW1->query(Ranges[x][0], Ranges[x][1]);
    }

    { // Query of all updates with k > 1
        ans += FW2->query(Ranges[x][0], Ranges[x][1]);

        auto child_per_level = get_children_by_level(x);
        for(int curr_u = parent[x], d = 1; curr_u != -1 && d < LOG; d++, curr_u = parent[curr_u]) {
            for(int off = d; off < LOG; off++){
                ans += updates_children[curr_u][off] * child_per_level[off - d];
            }
        }
    }

    return ans;
}


int main () {
	//fastIO();
	
    int n, q; cin>>n>>q;

    forr(i, 1, n-1){
        int p; cin>>p; p--;
        adjList[p].push_back(i);
        parent[i] = p;
    }

    parent[0] = -1;
    dfs_euler(0);


    FW1 = new FenwickTree<lli>(n+1);
    FW2 = new FenwickTree<lli>(n+1);
    while(q--){
        int t; cin>>t;
        if(t == 1){
            int x, y, k; cin>>x>>y>>k; x--;
            if(k == 1){
                updateOne(x, y);
            } else {
                updateMore(x, y, k);
            }
        } else{ 
            int x; cin>>x; x--;

            cout << get_ans(x) << endl;
        }
    }

	return 0;
}

