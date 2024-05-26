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

const int MOD = 998'244'353;


lli powerMod(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

const int inv_2 = (MOD+1) / 2;


struct DSU{
    int n;
    int comps;
    vector<int> parent, sz;

    DSU(int n): n(n), comps(n), parent(n), sz(n, 1) {
        iota(all(parent), 0);
    }

    int root(int u) {
        return parent[u] = (parent[u] == u ? u : root(parent[u]));
    }

    void join(int u, int v) {
        int Ru = root(u), Rv = root(v);
        if(Ru == Rv) return;

        if(sz[Ru] < sz[Rv]) swap(Ru, Rv);

        comps--;
        parent[Rv] = Ru;
        sz[Ru] += sz[Rv];

    }
};



int main () {
	fastIO();

    int n; cin>>n;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    map<int,int> mapping;
    for(auto &x: nums) {
        if(!mapping.count(x)) {
            mapping[x] = SZ(mapping);
        }
        x = mapping[x];
    }

    int m = SZ(mapping);

    const int BLUE = 0, RED = 1;

    bool ok = true;
    DSU D(m);
    auto countEqual = [&](const auto &countEqual, int start) -> void {
        if(start == n) return;

        map<int,int> last_color;
        vector<int> blue, red;

        int i = start, j = 0;
        for(i = start; i < n; i++) {
            if(!last_color.count(nums[i])) {
                last_color[nums[i]] = BLUE;
            }

            int color = last_color[nums[i]];
   
            if(color == BLUE) {
                blue.push_back(nums[i]);
            } else {
                assert(color == RED);
                if(j < SZ(blue) && blue[j] == nums[i]) {
                    red.push_back(nums[i]);
                    j++;
                } else {
                    ok = false;
                    return;
                }
            }

            last_color[nums[i]] = !color;
            if(SZ(blue) == SZ(red)) {
                i++;
                break;
            }
        }

        if(blue != red) {
            ok = false;
            return;
        }

        for(auto x: blue) {
            D.join(x, blue[0]);
        }

        countEqual(countEqual, i);
    };
    


    lli all_comb = powerMod(2, m);
    countEqual(countEqual, 0);

    lli equal = (ok ? powerMod(2, D.comps) : 0);

    // debugg(equal);
    cout << (all_comb - equal + MOD) % MOD * inv_2 % MOD << endl;


	return 0;
}

