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


const int MAXN = 2e5 + 1000;
int sz[MAXN];
int parent[MAXN];


int root(int u){
    return (u == parent[u] ? u : parent[u] = root(parent[u]));
}

void join(int u, int v){
    int Ru = root(u), Rv = root(v);
    if(Ru == Rv) return;
    if(sz[Ru] < sz[Rv]) swap(Ru, Rv);
    parent[Rv] = Ru;
    sz[Ru] += sz[Rv];
}

int main () {
	//fastIO();

    int n, l, r; cin>>n>>l>>r;

    iota(parent, parent + n, 0);
    fill(sz, sz + n, 1);

    forn(i, n){
        int x, y; cin>>x>>y; x--, y--;
        join(x, y);
    }

    int ans = 0;
    forn(i, n){
        if(root(i) != i) continue;
        int x = sz[i];
        int grundy = 0;
        // debugg(sz[i]);
        if(x <= r+l-1 ) {
            grundy = x / l;
        }

        // debugg(grundy);
        ans ^= grundy;
    }

    cout << (ans == 0 ? "Bob" : "Alice") << endl;




	return 0;
}

