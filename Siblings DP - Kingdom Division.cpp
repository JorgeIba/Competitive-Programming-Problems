#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const lli MOD = 1e9+7;

vector< vector<int> > adjList;

vector< int > child, nxt;

void prec(int u, int p = -1){

    bool f = true;
    int before = 0;
    for(auto v: adjList[u]) {
        if(v == p) continue;
        if(f) {
            child[u] = v;
            f = false;
        } else {
            nxt[before] = v;
        }

        prec(v, u);
        before = v;
    }
}

lli f(int, int, bool);



const int BLUE = 0, RED = 1;
const int maxN = 1e5+100;

lli dp_g[maxN][2][2];


lli g(int u, int color_parent, bool need_to_care){
    if(u == -1) return !need_to_care;

    lli &ans = dp_g[u][color_parent][need_to_care];
    if( ans != -1 ) return ans;

    ans = 0;

    if(color_parent == BLUE) {
        lli ans_same = f(u, BLUE, false)*g(nxt[u], BLUE, false) % MOD;
        lli ans_not_same = f(u, RED, true)*g(nxt[u], BLUE, need_to_care) % MOD;

        return ans = (ans_same + ans_not_same) % MOD;
    } else {
        lli ans_same = f(u, RED, false)*g(nxt[u], RED, false) % MOD;
        lli ans_not_same = f(u, BLUE, true)*g(nxt[u], RED, need_to_care) % MOD;

        return ans = (ans_same + ans_not_same) % MOD;
    }
}


lli dp_f[maxN][2][2];
lli f(int u, int color, bool need_to_care) {
    lli &ans = dp_f[u][color][need_to_care];
    if(ans != -1) return ans;
    ans = 0;

    return ans = g(child[u], color, need_to_care);
}

int main () {
	//fastIO();

    int n; cin>>n;
    adjList.resize(n+1);
    child.resize(n+1, -1);
    nxt.resize(n+1, -1);

    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    prec(1);

    memset(dp_f, -1, sizeof(dp_f));
    memset(dp_g, -1, sizeof(dp_g));
	
    lli ans = f(1, BLUE, true) + f(1, RED, true);

    cout << ans << endl;

	return 0;
}

