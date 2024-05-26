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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b & 1) res = a * res % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

const int PRIMES = 4;
vector<lli> mods = {
    100'000'000 + 7, 1'000'000'000LL + 7, 2'36'887'529, 9'82'448'893
};

const lli LOWER_X = 1e7;
const lli UPPER_X = 1e9;

vector<lli> Xs(4);
vector<lli> Xs_inv(4);


const int MAXN = 2e5+100;
vector<int> adjList[MAXN];

typedef array<lli,PRIMES> hash_type;

hash_type hash_original = {0, 0, 0, 0};

hash_type get_hash(lli d) {
    hash_type hashed = {0, 0, 0, 0};
    for(int i = 0; i < PRIMES; i++) {
        hashed[i] = powerMod(Xs[i], d, mods[i]);
    }
    return hashed;
}


hash_type sum_hash(hash_type hash_1, hash_type hash_2) {
    hash_type hash = {0, 0, 0, 0};
    for(int i = 0; i < PRIMES; i++) {
        hash[i] = (hash_1[i] + hash_2[i]) % mods[i];
    }
    return hash;
}

hash_type sub_hash(hash_type hash_1, hash_type hash_2) {
    hash_type hash = {0, 0, 0, 0};
    for(int i = 0; i < PRIMES; i++) {
        hash[i] = (hash_1[i] - hash_2[i] + mods[i]) % mods[i];
        assert(hash[i] >= 0);
    }
    return hash;
}

hash_type shift_hash(hash_type hash_1, int d) {
    hash_type hash = {0, 0, 0, 0};
    for(int i = 0; i < PRIMES; i++) {
        if(d >= 0) {
            hash[i] = hash_1[i] * powerMod(Xs[i], d, mods[i]) % mods[i];
        } else{
            hash[i] = hash_1[i] * powerMod(Xs_inv[i], -d, mods[i]) % mods[i];
        }
    }
    return hash;
}


set< hash_type > possible_hashes;
hash_type hashes_subtree[MAXN];

void dfs_init(int u, int d = 0, int p = -1) {
    hash_type hash = get_hash(d);
    
    for(auto v: adjList[u]) {
        if(v == p) continue;
        dfs_init(v, d + 1, u);

        hash = sum_hash(hash, hashes_subtree[v]);
    }

    hashes_subtree[u] = hash;
}

bool ans[MAXN];
void dfs_ans(int u, hash_type p_hash, int d = 0, int p = -1) {
    auto parent_hash = shift_hash(p_hash, 1);

    auto curr_hash = hashes_subtree[u];
    auto hash_if_root = shift_hash(curr_hash, -d);
    hash_if_root = sum_hash(hash_if_root, parent_hash);

    if(possible_hashes.count(hash_if_root))
        ans[u] = true;

    for(auto v: adjList[u]) {
        if(v == p) continue;

        auto hash_all_without_v = sub_hash(hashes_subtree[u], hashes_subtree[v]);
        hash_all_without_v = shift_hash(hash_all_without_v, -d);

        auto next_parent_hash = sum_hash(hash_all_without_v, parent_hash);
        dfs_ans(v, next_parent_hash, d+1, u);
    }
}


int main () {
	//fastIO();

    for(int i = 0; i < PRIMES; i++){
        lli x = aleatorio(LOWER_X, mods[i] - 1);
        lli inv_x = powerMod(x, mods[i] - 2, mods[i]);
        Xs[i] = x;
        Xs_inv[i] = inv_x;
    }

    int n; cin>>n;
    vector<int> values(n-1);  
    for(auto &x: values) cin>>x;

    forn(i, n-1) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    for(auto x: values) {
        auto hash_x = get_hash(x);
        hash_original = sum_hash(hash_original, hash_x);
    }

    for(int i = 0; i <= n; i++) {
        auto hash_i = get_hash(i);
        hash_type possible_hash = sum_hash(hash_original, hash_i);
        possible_hashes.insert(possible_hash);
    }


    int root = 1;
    dfs_init(root);
        
    dfs_ans(root, {0,0,0,0});
    
    vector<int> good_v;
    forr(i, 1, n) {
        if(ans[i]) 
            good_v.push_back(i);
    }
    
    cout << SZ(good_v) << endl;
    for(auto v: good_v) cout << v << " ";
    cout << endl;

	return 0;
}

