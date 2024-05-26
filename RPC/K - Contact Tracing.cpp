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


const int MAXN = 1e3+100;
const int MAXK = 10 + 2;
vector<int> adjList[MAXK][MAXN];
vector< pair<int,int> > edges[MAXK];
set<int> persons_in_day[MAXK];
int dp[MAXN][MAXN][MAXK][2]; 



int mat[MAXN][MAXK];


int main () {
	// fastIO();
    memset(dp, -1, sizeof(dp)); 

    int n, k, c; cin>>n>>k>>c;

    
    vector< tuple<int,int,int> > edges;
    forn(i, c){
        int u, v, d; cin>>u>>v>>d; u--, v--;
        edges.push_back({u, v, d});

        mat[u][d] = 1;
        mat[v][d] = 1;


        // adjList[d][u].push_back(v);
        // adjList[d][v].push_back(u);

        persons_in_day[d].insert(u);
        persons_in_day[d].insert(v);
    }

    for(auto [u, v, d]: edges){
        bool ok = true;
        for(int i = d+2; i <= k; i++){
            if(mat[u][i] || mat[v][i])
                ok = false;
        }

        if(ok){
            adjList[d][u].push_back(v);
            adjList[d][v].push_back(u);
        }
    }

    // for(int d = 1; d <= k; d++){
    //     cout << "Day: " << d << ":" << endl;
    //     forn(i, n){
    //         cout << i << ":" << endl;
    //         for(auto v: adjList[d][i]){
    //             cout << v << ", ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    if(k == 1){
        vector<int> ans(all(persons_in_day[1]));
        cout << SZ(ans) << endl;
        for(auto x: ans){
            cout << x+1 << endl;
        }
        return 0;
    }


    set<int> possible;
    for(int i = 0; i < n; i++){
        bool ok = true;
        for(int j = 2; j <= k; j++){
            if(persons_in_day[j].count(i)) ok = false;
        }
        if(ok) possible.insert(i);
    }


    vector< int > day_of_infect(n, -1);
    
    // dp[u][d][0] -> puede u llegar al día d no infectado? // creo que esta madre siempre es true ? 
    // dp[u][d][1] -> puede u llegar al día d infectado?    
    auto f = [&](const auto &f, int u, int p, int d, bool infected) -> int {
        if(d == 0) {
            if(possible.count(u)) return 1;

            return 0;
        }

        // debugg(u);
        // debugg(p);
        // debugg(d);
        // cout << endl;


        int &ans = dp[u][p][d][infected];
        if(ans != -1) return ans;

        if(infected){ 
            // Si me quiero infectar este día, entonces algun wey de los que tengo conectado debio de infectarse únicamente el día anterior
            // Y no me debo infectar yo antes
            bool ok = false;
            for(auto v: adjList[d][u]){
                if(v == p) continue;
                
                ok = ok || (f(f, v, u, d-1, infected));
            }

            return (ans = ok);
        } else {
            // ??
        }


        return false;
    };

    // for(auto u: persons_in_day[k]){
    //     bool ok = false;
    //     for(auto v: adjList[k][u]){
    //         assert(day_of_infect[v] == -1);
    //         if(day_of_infect[v] >= k) continue;

    //         day_of_infect[v] = k-1;
    //         if(dfs(dfs, v, k-1)){
    //             ok = true;
    //         }
    //         day_of_infect[v] = -1;

    //     }
        
    //     if(ok){
    //         ans.push_back(u);
    //     }
    // }

    // cout << f(f, 1, -1, 2, true) << endl;

    vector<int> ans;
    forn(i, n){
        auto ans_i = f(f, i, MAXN-1, k, true);
        // cout << i << " -> " << ans_i << endl;
        if(ans_i) {
            ans.push_back(i);
        }
    }    

    sort(all(ans));
    
    cout << SZ(ans) << endl;
    for(auto x: ans){
        cout << x+1 << endl;
    }


	return 0;
}

