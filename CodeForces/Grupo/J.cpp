#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
using namespace std;

struct UnionFind {
    vector<int> sz;
    vector<int> padre;

    UnionFind(int n): padre(n, 0), sz(n, 0) { // O(n)
        for(int i=0;i<n;i++) {
            padre[i] = i;
            sz[i] = 1;
        }
    }

    int Find(int u) { // ~O(log n)
        if(u == padre[u]) return u;
        return padre[u] = Find(padre[u]);
    }

    bool same(int u, int v) { // O(1)
        return Find(u) == Find(v);
    }

    void Union(int u, int v) { // ~O(log n)
        if(same(u, v)) return;
        int Ru = Find(u), Rv = Find(v);
        padre[Ru] = Rv;
        sz[Rv] += sz[Ru];
    }

    int getSize(int u) {
        return sz[Find(u)];
    }
};

int main()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli minimo = 1000000000000000LL;
    for(int i = 0; i<n; i++)
    {
        lli act = nums[i];
        minimo = min(minimo, act);

    }


    return 0;
}