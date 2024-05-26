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


int main () {
	fastIO();
	
    int n; cin>>n;

    vector<int> perm(n+1);
    forr(i, 1, n) cin>>perm[i];

    vector< int > sz_cycles;
    vector<bool> visited(n+1);
    forr(i, 1, n){
        if(visited[i]) continue;
        int j = i, sz = 0;
        do {
            sz++;
            visited[j] = true;
            j = perm[j];
        }while(j != i);

        sz_cycles.push_back(sz);
    }

    int ans = 0;
    for(auto sz: sz_cycles){
        // debugg(sz);
        ans += (sz-1);
    }

    cout << (~ans & 1 ? "Oh No!" : "Smokin Joe!") << endl;


	return 0;
}

