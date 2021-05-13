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

struct UnionFind{
    vector<int> parent, size;
    UnionFind(int N): parent(N, -1), size(N,1) {}

    int find(int u)
    {
        if(parent[u] == -1) return u;
        return parent[u] = find(parent[u]);
    }
    void join(int a, int b)
    {
        a = find(a), b = find(b);
        if(a==b) return;
        if(size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
    int sizeComp(int u)
    {
        return size[find(u)];
    }
};

const int MOD = 1e9+7;

typedef pair<int,int> PII;

template<class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = 0;
    while (!isdigit(c)) {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x = flag ? -x : x;
}

template<class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

pair<int,PII> edges[100001];

int main () {
	fastIO();
	int n; read(n);
    vector< pair<int,PII>  > edges(n-1);
    for(int i = 0; i<n-1; i++) read(edges[i].second.first), read(edges[i].second.second), read(edges[i].first);
    sort(all(edges));
    UnionFind U(n);
    int ans = 0;
    for(const auto &E: edges)
    {
        int aux = (1LL*U.sizeComp(E.second.first-1)*U.sizeComp(E.second.second-1))%MOD;
        aux = (1LL*E.first * aux)%MOD;
        ans = ans + aux;
        if(ans >= MOD) ans-=MOD;
        U.join(E.second.first-1, E.second.second-1);
    }
    write(ans);
	return 0;
}