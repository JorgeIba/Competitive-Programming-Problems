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


int main () {
	//fastIO();
    int n; cin>>n;
    string s, t; cin>>s>>t;

    deque<int> ab, ba;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a' && t[i] == 'b') ab.push_back(i);
        if(s[i] == 'b' && t[i] == 'a') ba.push_back(i);
    }

    vector<pair<int,int>> indices;

    
    int ans = 0;
    while(SZ(ab) >= 2) {
        int u = ab.front(); ab.pop_front();
        int v = ab.front(); ab.pop_front();

        indices.push_back({u, v});
    }
    

    while(SZ(ba) >= 2) {
        int u = ba.front(); ba.pop_front();
        int v = ba.front(); ba.pop_front();

        indices.push_back({u, v});
    }



    if(SZ(ab) || SZ(ba)){
        if(SZ(ab) && SZ(ba)){
            ans++;
            indices.push_back({ab.front(), ab.front()});
            indices.push_back({ab.front(), ba.front()});
        } else {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << SZ(indices) << endl;
    for(auto x: indices) {
        cout << x.first+1 << " " << x.second+1 << endl;
    }




	return 0;
}

