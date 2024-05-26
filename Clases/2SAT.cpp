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


struct TWO_SAT{
    int n;
    vector< vector<int> > adjList;
    vector< vector<int> > adjList_T;
    vector<int> visited;
    vector<int> component;
    vector<int> order;

    TWO_SAT(int n): n(n), adjList(2*n), adjList_T(2*n), visited(2*n), component(2*n) {}

    // (a v b) = (~a -> b) and (~b -> a)
    void disjunction(int a, int b, bool neg_a, bool neg_b){ 
        int x = 2*a ^ neg_a;
        int y = 2*b ^ neg_b;

        adjList[ x ^ 1 ].push_back(y);
        adjList[ y ^ 1 ].push_back(x);

        adjList_T[ y ].push_back(x ^ 1);
        adjList_T[ x ].push_back(y ^ 1);
    }


    void dfs_1(int u){
        visited[u] = true;
        for(auto v: adjList[u]){
            if(visited[v]) continue;
            dfs_1(v);
        }

        order.push_back(u);
    }

    void dfs_2(int u, int no_comp){
        visited[u] = true;
        component[u] = no_comp;
        for(auto v: adjList_T[u]){
            if(visited[v]) continue;
            dfs_2(v, no_comp);
        }
    }

    vector<bool> solve(){

        // Correr Kosaraju
        for(int i = 0; i < 2*n; i++){
            if(visited[i] == false)
                dfs_1(i);
        }

        reverse(all(order));
        fill(all(visited), false);
        int comp = 0;
        for(auto u: order){ 
            // Voy y marco las componentes conexas por su orden topológico
            if(visited[u] == false){
                dfs_2(u, comp);
                comp++;
            }
        }

        vector<bool> ans(n);
        for(int i = 0; i < n; i++){
            if(component[2*i] == component[2*i + 1]){
                return {};
            }
            else if(component[2*i] < component[2*i+1]) {
                ans[i] = 0;
            } else { // component[2*i] > component[2*i+1]
                ans[i] = 1;
            }
        }
        return ans;
    }

};


int main () {

    cout << "cuantas variables? " << endl;
    int n; cin>>n;

    cout << "cuantas clausulas?" << endl;
    int m; cin>>m;

    TWO_SAT SAT(n);
    for(int i = 0; i < m; i++){
        cout << "Ingrese clausula" << endl;
        int u, v; cin>>u>>v;
        bool neg_u, neg_v; cin>>neg_u>>neg_v;
        SAT.disjunction(u, v, neg_u, neg_v);
    }

    auto ans = SAT.solve();

    if(ans.empty()){
        cout << "Hay una contradiccion" << endl;
        return 0;
    }

    for(int i = 0; i < n; i++){
        cout << "La variable " << i << " debe tener un valor de " << ans[i] << endl;
    }

	return 0;
}

