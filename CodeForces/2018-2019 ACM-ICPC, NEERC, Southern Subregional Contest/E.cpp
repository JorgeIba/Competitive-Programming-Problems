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

const int MAXC = 3e5 + 100;
const int INF = 1e9;

set<int> indexes[MAXC];

int main () {
	// fastIO();



    int n; cin>>n;
    set<tuple<int,int,int>> ranges;
    forn(i, n) {
        int x; cin>>x;
        indexes[x].insert(i);
        ranges.insert({i, i, x});
    }

    auto insertt = [&](int l, int r, int c) {
        auto itr = ranges.lower_bound({l, -INF, -INF});

        while(itr != ranges.end()) {
            auto [l_2, r_2, c_2] = *itr;
            if(l_2 > r) break;

            ranges.erase(itr++);
            indexes[c_2].extract(l_2);
            indexes[c_2].extract(r_2);
        }
        // for(;itr != a.end() && (get<0>(*itr) <= r); a.erase(itr++));
        
        ranges.insert({l, r, c});
        indexes[c].insert(l);
        indexes[c].insert(r);
    };

    int q; cin>>q;
    while(q--) {
        int c; cin>>c;
        if(SZ(indexes[c]) < 2) continue;

        auto l = *indexes[c].begin();
        auto r = *indexes[c].rbegin();

        insertt(l, r, c);
    }

    vector<int> ans(n);
    for(auto itr = ranges.begin(); itr != ranges.end(); itr++) {
        auto [l, r, c] = *itr;
        for(int i = l; i <= r; i++) {
            ans[i] = c;
        }
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;



	return 0;
}

