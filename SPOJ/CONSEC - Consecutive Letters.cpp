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

#define Query pair<int, int> 

struct UnionFind{
  int n;
  vector<int> dad, size;

  UnionFind(int N) : n(N), dad(N), size(N, 1) {
    while (N--) dad[N] = N;
  }

  int root(int u) {
    if (dad[u] == u) return u;
    return dad[u] = root(dad[u]);
  }
  void join(int u, int v) {
    int Ru = root(u), Rv = root(v);
    if (Ru == Rv) return;
    if (size[Ru] > size[Rv]) swap(Ru, Rv);
    --n, dad[Ru] = Rv;
    size[Rv] += size[Ru];
  }
  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }
};

string s;
int n;

bool checkLeft(int i)
{
    if(i>0 && s[i] == s[i-1]) return true;
    return false;
}

bool checkRight(int i)
{
    if(i<n && s[i] == s[i+1]) return true;
    return false;
}

void solve()
{
    cin>>s;
    n = s.length();
    int q; cin>>q;
    vector<Query> queries;
    vector<int> notUse(n,1);

    for(int i = 0; i<q; i++)
    {
        int t, idx; cin>>t>>idx;
        if(t == 2) notUse[idx] = 0;
        queries.push_back({t, idx});
    }

    UnionFind U(n);
    for(int i = 0; i<n; i++)
    {
        if(checkLeft(i) && notUse[i] && notUse[i-1])  U.join(i-1, i);
        if(checkRight(i) && notUse[i] && notUse[i+1])  U.join(i+1, i);
    }

    reverse(all(queries));
    vector<int> ans;
    for(int i = 0; i<q; i++)
    {
        int idx = queries[i].second;

        if(queries[i].first == 1) ans.push_back(U.getSize(idx));
        else
        {
            notUse[idx] = 1;
            if(checkLeft(idx) && notUse[idx] && notUse[idx-1])  U.join(idx, idx-1);
            if(checkRight(idx) && notUse[idx] && notUse[idx+1]) U.join(idx, idx+1);
        }
    }
    reverse(all(ans));
    for(auto x: ans) cout << x << endl;

}



int main () {
	fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        cout<< "Case " << i << ":\n";
        solve();
    }

    
	return 0;
}