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

const int MAXN = 2e5 + 100;
const lli MAXA = 1e9+100;

vector<int> adjList[MAXN];


lli dp[MAXN][15];
vector<int> raws;

lli f(int u, int raw) {
    if(u == raws[raw]) return 1;

    lli &ans = dp[u][raw];

    if(ans != -1) return ans;
    ans = 0;
    
    for(auto v: adjList[u]){
        if(ans <= MAXA)
            ans += f(v, raw);
    }

    return ans;
}



int main () {
	//fastIO();

    int n, m; cin>>n>>m;

    vector<lli> raws_quant;
    

    for(int i = 1; i <= n; i++) {
        int k; cin>>k;
        forr(j, 1, k) {
            int v; cin>>v;
            adjList[i].push_back(v);
        }
    }

    for(int i = n+1; i <= m; i++) {
        int k; cin>>k;
        if(!k) {
            lli quant; cin>>quant;
            raws_quant.push_back(quant);
            raws.push_back(i);
        } else {
            forr(j, 1, k) {
                int v; cin>>v;
                adjList[i].push_back(v);
            }
        }
    }


    memset(dp, -1, sizeof(dp));

    for(int i = 1; i <= n; i++) {
        for(int j = 0;  j < SZ(raws); j++){
            f(i, j);
        }
    }

    int sz_raw = SZ(raws);


    int ans = 0;
    for(int mask = 0; mask < ( 1 << n); mask++) {

        vector<lli> needs(sz_raw);
        for(int j = 0; j < n; j++) {
            if(mask & (1 << j)){
                for(int k = 0; k < sz_raw; k++) {
                    if(needs[k] <= MAXA)
                        needs[k] += f(j+1, k);
                }

            }
        }

        bool valid = true;
        for(int i = 0; i < sz_raw; i++) {
            if(needs[i] > raws_quant[i]) valid = false;
        }

        if(valid) {
            ans = max(ans, __builtin_popcount(mask));
        }
    }

    cout << ans << endl;




	return 0;
}

