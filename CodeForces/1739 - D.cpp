#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

vector<vector<lli>> adjList;

const lli INF = 1e15;

lli dfs(lli u, lli p, lli &cost, lli limit_height) {
    lli max_height = 0;

    for(auto v: adjList[u]) {
        max_height = max(max_height, dfs(v, u, cost, limit_height) + 1);
    }

    if(max_height == limit_height - 1) {
        if(u != 1 && p != 1) cost++;

        return -1;
    }

    return max_height;
}


lli check(lli height) {
    lli cost = 0;
    dfs(1, 1, cost, height);
    return cost;
}


void solve() {
	int n, k; cin>>n>>k;
	adjList.clear();
	adjList.resize(n+1);

	for(int i = 2; i <= n; i++){
        lli p; cin>>p;
        adjList[p].push_back(i);
    }


    
    lli l = 1, r = n-1, ans = -1;
    while(l <= r) {
        lli mid = (l+r)/2;

        if(check(mid) <= k) {
            ans = mid, r = mid-1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    
}



int main () {
	fastIO();

    lli t; cin>>t;
    while(t--) solve();

	return 0;
}

