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

// Maximum Bipartite Matching O(nm)
struct KuhnAlgo {
    int n, m;
    vector<int> left_to_right, right_to_left;
    vector<bool> visited;
    vector<vector<int>> adjListLeft;

    // Left: 0, 1, ..., n-1
    // Right: 0, 1, ..., m-1
    KuhnAlgo(int n, int m, const vector<vector<int>> &adjListLeft): n(n), m(m), adjListLeft(adjListLeft) {
        left_to_right.assign(n, -1);
        right_to_left.assign(m, -1);
        visited.assign(n, false);
    }
    
    bool try_Kuhn(int u) {
        if(visited[u]) return false;
        visited[u] = true;

        for(auto v: adjListLeft[u]) {
            if(right_to_left[v] == -1 || try_Kuhn(right_to_left[v])) {
                left_to_right[u] = v;
                right_to_left[v] = u;
                return true;
            }
        }
        return false;
    }
    
    vector<pair<int,int>> getMaxMatching() {
        int sizeMatching = 0;
        for(int u = 0; u < n; u++) {
            fill(all(visited), false);
            if( try_Kuhn(u) )
                sizeMatching++;                
        }
        vector< pair<int,int> > ans;
        for(int u = 0; u < n; u++)
            if(left_to_right[u] != -1)
                ans.push_back({u, left_to_right[u]});
        return ans;
    }
};



int main () {
	//fastIO();
    int n, m; cin>>n>>m;

    vector<string> mat(n);
    for(auto &s: mat) cin>>s;

    vector< vector<int> > adjList_match(m);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++) {
            if(i == j) continue;
            bool valid = true;
            bool is_same = true;
            
            for(int d = 0; d < n; d++) {
                valid = (valid && (mat[d][i] >= mat[d][j]));
                is_same = (is_same && mat[d][i] == mat[d][j]);
            }

            if(valid) {
                // cout << "EXCUSE ME?" << endl;
                if(is_same) {
                    if(i < j) {
                        adjList_match[i].push_back(j);
                    }
                } else {
                    adjList_match[i].push_back(j);
                }
            }
        }
    }


    KuhnAlgo *KA = new KuhnAlgo(m, m, adjList_match);

    auto matches = KA->getMaxMatching();


    vector< vector<int> > adjList(m);
    vector<int> income_degree(m);

    for(auto [u, v]: matches) {
        adjList[u].push_back(v);
        income_degree[v]++;
    }

    auto dfs = [&](const auto &dfs, int u, vector<int> &path) -> void {
        path.push_back(u);

        for(auto v: adjList[u]) {
            assert(SZ(adjList[u]) == 1);

            dfs(dfs, v, path);
        }
    };

    
    vector< vector<int> > paths;
    for(int i = 0; i < m; i++){
        if(income_degree[i]) continue;

        vector<int> path;
        dfs(dfs, i, path);

        paths.push_back(path);
    }

    int k = SZ(paths);
    cout << k << endl;

    vector< pair<int,int> > v_group(m);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < SZ(paths[i]); j++) {
            auto v = paths[i][j];
            v_group[v] = {i, j + 5};
        }
    }

    for(int i = 0; i < m; i++) {
        cout << v_group[i].first + 1 << " ";
    }   
    cout << endl;

    for(int i = 0; i < m; i++){
        cout << v_group[i].second << " ";
    }
    cout << endl;


    for(int d = 0; d < n; d++){
        vector< int > max_value_group(k, 1);
        for(int i = 0; i < m; i++) {
            if(mat[d][i] == '0') continue;

            auto [group, val] = v_group[i];

            max_value_group[group] = max(max_value_group[group], val);
        }

        for(int i = 0; i < k; i++){
            cout << max_value_group[i] << " ";
        }
        cout << endl;
    }

	return 0;
}

