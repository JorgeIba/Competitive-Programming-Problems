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


const int MAXN = 100 + 50;

vector<int> adjList[MAXN];
int depth[MAXN];
int n; 
const int ROOT = 0;


void dfs(int u, int depth_u = 0){
    depth[u] = depth_u;
    for(auto v: adjList[u]){
        dfs(v, depth_u + 1);
    }
}

vector<int> query(int color) {
    int t; cin>>t;
    if(t == 1){
        exit(0);
    } else if(t == -1){
        assert(false);
        exit(0);
    } 
    vector<int> colors(color+1);
    for(int i = 1; i <= color; i++){
        cin>>colors[i];
    }
    return colors;
}


void solution_3(){

    cout << 3 << endl;
    for(int i = 1; i < n; i++){
        cout << (depth[i]-1 + 3)%3 + 1 << " ";
    }
    cout << endl; cout.flush();

    while(true){
        auto colors = query(3);

        if(colors[1] && colors[2]){
            cout << 1 << endl;
            cout.flush();
        } else if(colors[2] && colors[3]){
            cout << 2 << endl;
            cout.flush();
        } else if(colors[3] && colors[1]) {
            cout << 3 << endl;
            cout.flush();
        } else {
            for(int i = 1; i <= 3; i++){
                if(colors[i]){
                    cout << i << endl;
                    cout.flush();
                    break;
                }
            }
        }
    }
}


void dfs_single(int u, int &even, int &odd){
    if(SZ(adjList[u]) == 1) {
        even += (depth[u] % 2 == 0);
        odd += (depth[u] % 2 == 1);
    }
    for(auto v: adjList[u]){
        dfs_single(v, even, odd);
    }
}


int ans2[MAXN];
void dfs_mark(int u, int color) {
    ans2[u] = color;
    color = !color;
    for(auto v: adjList[u]){
        dfs_mark(v, color);
    }
}

bool check_two(){
    bool ok = true;
    for(auto v: adjList[ROOT]) {
        int even = 0, odd = 0;
        dfs_single(v, even, odd);
        if(even && odd) ok = false;
        else if(even) {
            dfs_mark(v, 0);
        } else {
            dfs_mark(v, 1);
        }
    }
    return ok;
}

void solution_2() {
    cout << 2 << endl;
    for(int i = 1; i < n; i++){
        cout << ans2[i]+1 << " ";
    }
    cout << endl; cout.flush();

    while(true){
        auto ans = query(2);
        if(ans[1] == 1 && ans[2] == 1) {
            cout << 2 << endl;
            cout.flush();
        } else if(ans[1] == 1){
            cout << 1 << endl;
            cout.flush();
        } else {
            assert(ans[2] == 1);
            cout << 2 << endl;
            cout.flush();
        }
    }
}


int main () {
	//fastIO();
	
    cin>>n;

    for(int i = 1; i < n; i++){
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    dfs(0);

    bool one = true;
    for(int i = 1; i < n; i++)
        one = one && (SZ(adjList[i]) == 0);

    if(one){
        cout << 1 << endl;
        for(int i = 1; i < n; i++){
            cout << 1 << " ";
        }
        cout << endl; cout.flush();
        auto c = query(1); assert(c[1]);
        cout << 1 << endl;
        query(1);
    }

    bool two = check_two();
    if(two){
        solution_2();
    }

    solution_3();

	return 0;
}

