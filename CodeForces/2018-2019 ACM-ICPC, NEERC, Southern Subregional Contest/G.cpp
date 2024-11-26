#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

int main () {
	// fastIO();

    int n; cin>>n;
    vector<pair<int,int>> values(n-1);

    bool ok = true;
    vector<int> used(n+1);
    for(auto &[x, y]: values) {
        cin>>x>>y;
        if(x < y) swap(x, y);
        if(x == y || !(x == n || y == n))
            ok = false;
        used[y]++;
    }

    vector<pair<int,int>> ans;
    for(int i = n-1; i >= 1; i--) {
        if(used[i] == 0) ok = false;
        if(used[i] == -1) continue;
        vector<int> path;

        used[i]--;
        for(int j = i-1; j >= 1; j--) {
            if(used[j] > 0) continue;
            if(used[j] == -1) continue;

            if(used[i]) {
                path.push_back(j);
                used[j]--;
                used[i]--;
            }
        }

        if(used[i] > 0) ok = false;
        path.push_back(n); reverse(all(path)); path.push_back(i);
        forn(i, SZ(path)-1) {
            ans.push_back({path[i], path[i+1]});
        }
    }

    if(!ok) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    for(auto [u, v]: ans) cout << u << " " << v << endl;


    





	return 0;
}

