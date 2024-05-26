#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector< vector<int> > adjList;
vector<int> longests, ans;


int diameter = 0;
int dfs_prec(int u, int p = -1) {
    if(SZ(adjList[u]) == 1 && p != -1) return 0;

    int longest = 0;
    for(auto v: adjList[u]) {
        if(v == p) continue;

        int longest_v = dfs_prec(v, u) + 1;


        diameter = max(diameter, longest + longest_v);
        longest = max(longest, longest_v);
    }

    return longests[u] = longest;
}


void dfs_ans(int u, int longest_others, int p = -1) {
    if(SZ(adjList[u]) == 1 && p != -1) {
        int diam_new = 1 + longest_others;
        ans[u] = max(diam_new, diameter);

        return;
    }

    multiset<int> longests_in_u;
    longests_in_u.insert(longest_others);


    for(auto v: adjList[u]) {
        if(v == p) continue;

        int longest_v = longests[v] + 1;
        longests_in_u.insert(longest_v);
    }

    ans[u] = max(diameter, longests[u] + 1);
    for(auto v: adjList[u]) {
        if(v == p) continue;

        int longest_v = longests[v] + 1;
        longests_in_u.erase(longests_in_u.find(longest_v));


        int longest_now = *longests_in_u.rbegin();
        dfs_ans(v, longest_now + 1 , u);


        longests_in_u.insert(longest_v);
    }
}



int main () {
	fastIO();
	
    int n; cin>>n;

    adjList.resize(n+1);
    longests.resize(n+1);
    ans.resize(n+1);

    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfs_prec(1);
    dfs_ans(1, 0);

    for(int i = 1; i <= n; i++) cout << ans[i] << endl;

	return 0;
}
