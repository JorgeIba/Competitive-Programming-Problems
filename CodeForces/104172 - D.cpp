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

bool leq(lli a, lli b){ return a <= b; }

struct point{
    lli x, y;
    point() {}
    point(lli x, lli y): x(x), y(y) {}

    point operator-(const point &p) const {
        return {x - p.x, y - p.y};
    }
    lli cross(const point &p) const { return x * p.y - y * p.x; }

    lli dot(const point &p) const { return x * p.x + y * p.y; }

    bool operator<(const point &p) const {
        return pair<lli,lli>{x, y} < pair<lli,lli>{p.x, p.y};
    }

    bool operator==(const point &p) const {
        return pair<lli,lli>{x, y} == pair<lli,lli>{p.x, p.y};
    }
};

vector<point> convexHull(vector<point> P){
	vector<point> L;
	for(int i = 0; i < SZ(P); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}

	return L;
}

const int MAXN = 5e4 + 100;
const int B = 0, W = 1;

vector< pair<int,int> > adjList[MAXN];

vector<point> dp[MAXN];
const lli INF = 1e15;

int main () {
	fastIO();
    
    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v, c; cin>>u>>v>>c;
        adjList[v].push_back({u, c});
    }

    auto merge_ch = [&](vector<point> left, vector<point> right) -> vector<point> {
        vector<point> both(SZ(left) + SZ(right));

        merge(all(left), all(right), both.begin());
        both.erase(unique(all(both)), both.end());
    
        return convexHull(both);
    };  


    dp[1].push_back({0, 0});
    forr(u, 2, n) {
        vector< point > curr_dp;
        for(auto [v, c]: adjList[u]){
            vector< point > ch_v = dp[v];
            for(auto &p: ch_v){
                if(c == W) p.x++;
                else p.y++;
            }

            curr_dp = merge_ch(curr_dp, ch_v);
        }
        dp[u] = curr_dp;
    }

    int q; cin>>q;
    while(q--){
        int a, b, x; cin>>a>>b>>x;

        point p_q(b, a);
        lli ans = INF;
        for(auto p: dp[x]){
            ans = min(ans, p.dot(p_q));
        }

        cout << ans << endl;
    }

	return 0;
}

