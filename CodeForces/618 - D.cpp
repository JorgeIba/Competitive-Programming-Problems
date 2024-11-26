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

const int MAXN = 2e5 + 100;
vector<int> adjList[MAXN];
int nextt[MAXN], leftt[MAXN];


void dfs(int u, int p = -1) {
    int before = -1;
    bool f = true;
    for(auto v: adjList[u]) {
        if(v == p) continue;

        if(f) {
            leftt[u] = v;
            f = !f;
        } else {
            nextt[before] = v;
        }

        dfs(v, u);
        before = v;
    }
}



const lli INF = 1e15;
lli x, y;

lli f(int, int);
lli g(int, bool);


lli dp[MAXN][3];

lli f(int u, int chains) {
    if(chains < 0) return INF;

    if(u == -1) {
        assert(0 <= chains && chains <= 2);
        return 0;
    }

    lli &ans = dp[u][chains];
    if(ans != -1) return ans;

    lli continue_chain = g(u, true) + f(nextt[u], chains-1) + x;
    lli start_chain = g(u, false) + f(nextt[u], chains) + y;

    return ans = min(continue_chain, start_chain);
}

lli g(int u, bool from_parent) {
    if(from_parent) {
        return f(leftt[u], 1);
    } else{
        return f(leftt[u], 2);
    }
}


int main () {
	// fastIO();
    int n; cin>>n>>x>>y;

    forn(i, n-1) {
        int u, v; cin>>u>>v; 
        u--, v--;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int root_star = -1;
    forn(i, n) {
        if(SZ(adjList[i]) == n-1) {
            root_star = i;
        }
    }

    if(n == 2) {
        cout << x << endl;
        return 0;
    }

    if(root_star != -1) {
        if(y < x) {
            cout << 1LL * (n-2) * y + x << endl;
        } else {
            cout << 2 * x + (n-3) * y << endl;
        }
        return 0;
    }

    fill(nextt, nextt+n, -1);
    fill(leftt, leftt+n, -1);

    dfs(0);

    memset(dp, -1, sizeof(dp));
    cout << g(0, 0) << endl;

	return 0;
}

