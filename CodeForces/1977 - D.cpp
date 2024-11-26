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


const vector<int> MODS = {(int)1e9+7, 982448893, 961757387};

#define hash_t tuple<int,int,int>


lli powerMod(lli a, lli b, const int MOD) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}


void main_() {
    int n, m; cin>>n>>m;
    vector<string> mat(n);

    for(auto &s: mat) cin>>s;

    auto add = [&](hash_t &hashed, int power) {
        auto &[a, b, c] = hashed;
        a += powerMod(2, power, MODS[0]);
        if(a >= MODS[0]) a -= MODS[0];

        b += powerMod(2, power, MODS[1]);
        if(b >= MODS[1]) b -= MODS[1];

        c += powerMod(2, power, MODS[2]);
        if(c >= MODS[2]) c -= MODS[2];
    };

    auto sub = [&](hash_t &hashed, int power) {
        auto &[a, b, c] = hashed;
        a -= powerMod(2, power, MODS[0]);
        if(a < 0) a += MODS[0];

        b -= powerMod(2, power, MODS[1]);
        if(b < 0) b += MODS[1];

        c -= powerMod(2, power, MODS[2]);
        if(c < 0) c += MODS[2];
    };



    map< hash_t, int > fr;
    map< hash_t, pair<int,int> > index_kept;
    for(int j = 0; j < m; j++) {
        hash_t hash_j;
        for(int i = 0; i < n; i++) {
            if(mat[i][j] == '1') {
                add(hash_j, i);
            }
        }

        for(int i = 0; i < n; i++) {
            auto new_hash = hash_j;
            if(mat[i][j] == '1') {
                sub(new_hash, i);
            } else {
                add(new_hash, i);
            }

            fr[new_hash]++;
            index_kept[new_hash] = {j, i};
        }
    }

    hash_t hash_max;
    int ans = 0;
    for(auto [x, f]: fr) {
        if(f > ans) {
            ans = f;
            hash_max = x;
        }
    }

    auto [col, row] = index_kept[hash_max];

    string ans_s(n, '0');
    for(int i = 0; i < n; i++) {
        ans_s[i] = ((row == i) ^ (mat[i][col] == '1')) + '0';
        // if(row == i && mat[i][j] == '0') {
        //     ans[i] = '1';
        // } else if(row == i && mat[i][j] != '0') {
        //     ans[i] = '0';
        // } else if(row != i && mat[i][j] == '0') {
        //     ans[i] = '0';
        // } else {
        //     ans[i] = '1';
        // }
    }

    cout << ans << endl << ans_s << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

