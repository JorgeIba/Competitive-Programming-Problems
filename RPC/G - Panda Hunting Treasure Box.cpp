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


const int MAXN = 500 + 10;

lli mat[MAXN][MAXN];

vector< tuple<int,int,int> > dirs = {
    {-1, -1, 1}, {-1, 0, 2}, {-1, 1, 3},
    { 0, -1, 8},             { 0, 1, 4},
    { 1, -1, 7}, { 1, 0, 6}, { 1, 1, 5}
};


lli dist[MAXN][MAXN];

const lli INF = 1e17;

int main () {
	fastIO();
	
    int n, m, nr, mr, energy;  
    cin>>n>>m>>nr>>mr>>energy;

    nr--, mr--;

    forn(i, n){
        forn(j, m){
            cin>>mat[i][j];
        }
    }

    auto is_inside = [&](int i, int j) {
        if(i < 0 || i >= n || j < 0 || j >= m) return false;
        return true;
    };


    #define edge tuple<lli,int,int>

    priority_queue< edge, vector<edge>, greater<edge> > pq;

    forn(i, n){
        forn(j, m){
            dist[i][j] = INF;
        }
    }

    pq.push({0,nr, mr}); 
    dist[nr][mr] = 0;

    while(!pq.empty()){
        auto [dist_u, i, j] = pq.top(); pq.pop();

        if(mat[i][j] != 0) continue;
        if(dist_u > dist[i][j]) continue;

        for(auto [dx, dy, cost]: dirs){
            if(!is_inside(i+dx, j+dy)) continue;


            if(dist[i][j] + cost < dist[i+dx][j+dy]) {
                dist[i+dx][j+dy] = dist[i][j] + cost;
                pq.push({cost, i+dx, j+dy});
            }
        }
    }

    lli ans = 0;
    forn(i, n){
        forn(j, m){
            // cout << i << ", " << j  << " cost: " << dist[i][j] << ", ";
            if(dist[i][j] <= energy) {
                ans = max(ans, mat[i][j]);
            }
        }
        
    }

    cout << ans << endl;



	return 0;
}

