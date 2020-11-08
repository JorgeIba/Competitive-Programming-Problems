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

#define Edge pair<int, int>

struct SetUnion{
    int n;
    vector<int> parent, size;

    SetUnion(int N): n(N), parent(N+1), size(N+1, 1){
        while(N--) parent[N] = N;
    }

    int find(int u)
    {
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(size[a] < size[b]) swap(a, b);
        n--; parent[b] = a;
        size[a] += size[b];
    }

    bool check(int a, int b)
    {
        if(find(a) != find(b)) return true;
        return false;
    }

};


int main () {
	fastIO();
	int n; cin>>n;
    vector<Edge> edges(n-1);

    for(int i = 0; i<n-1; i++)
    {
        cin>>edges[i].first>>edges[i].second;
    }

    SetUnion S(n);
    int currComp = S.n;
    vector<int> useless;
    for(int i = 0; i<n-1; i++)
    {
        S.join(edges[i].first, edges[i].second);
        if(currComp == S.n) useless.push_back(i);
        currComp = S.n;
    }

    vector< Edge > ans;

    cout << SZ(useless) << endl;

    for(int i = 1; i<=n; i++)
    {
        for(int j = i+1; j<=n; j++)
        {
            if(S.check(i, j))
            {
                ans.push_back({i, j});
                S.join(i, j);
            }
        }
    }
    assert(SZ(ans) == SZ(useless));

    for(int i = 0; i<SZ(ans); i++)
    {
        cout << edges[useless[i]].first << " " << edges[useless[i]].second << " " << ans[i].first << " " << ans[i].second << endl;
    }
    
	return 0;
}