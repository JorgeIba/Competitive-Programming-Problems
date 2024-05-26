#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int n; 
vector<lli> flow;
vector< vector<int> > adjList;
vector< lli > lower;
vector< bool> wildcard;

void prec_lower(int u, int p = -1){
    for(auto v: adjList[u]){
        if( v == p ) continue;
        prec_lower(v, u);
        lower[u] += lower[v];
    }

    if(flow[u]) {
        lower[u] = flow[u];
    }
    lower[u] = max(1LL, lower[u]);
}

void push_top(int u, int p = -1){
    for(auto v: adjList[u]){
        if( v == p ) continue;
        push_top(v, u);
    }

    lli sum = 0, cnt = 0;
    for(auto v: adjList[u]) {
        if(flow[v] == 0) cnt++;
        else sum += flow[v];
    }

    if(!flow[u] && !cnt) {
        flow[u] = sum;
    }
}

bool impossible = false;

void dfs_ans(int u, lli f, int p = -1){

    flow[u] = f;
    if(!SZ(adjList[u])) return;

    lli rest_flow = f;
    vector< int > wilds;
    for(auto v: adjList[u]) {
        if(v == p) continue;

        if(wildcard[v]) {
            wilds.push_back(v);
            continue;
        }

        dfs_ans(v, lower[v], u);
        rest_flow -= lower[v];
    }

    if(SZ(wilds)) {
        int sum = 0;
        for(auto v: wilds) sum += lower[v];

        if(rest_flow < sum) impossible = true;
        else if(rest_flow == sum){
            for(auto v: wilds)
                dfs_ans(v, lower[v], u);
        } else {
            if(SZ(wilds) > 1) impossible = true; 
            else dfs_ans(wilds[0], rest_flow, u);
        }
    } else if(rest_flow != 0) {
        impossible = true;
    }
}


int main () {
    //fastIO();

    cin>>n;

    adjList.resize(n);
    flow.resize(n);
    lower.resize(n);
    wildcard.resize(n);

    for(int i = 1; i <= n-1; i++){
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    for(auto &x: flow) cin>>x;

    prec_lower(0);
    push_top(0);

    for(int i = 0; i < n; i++){
        wildcard[i] = (flow[i] == 0);
    }

    flow.clear();
    flow.resize(n);
    dfs_ans(0, lower[0]);

    impossible |= (wildcard[0]);

    if(impossible){
        cout << "impossible" << endl;
    } else {
        for(auto x: flow) cout << x << endl;
    }

    return 0;
}

