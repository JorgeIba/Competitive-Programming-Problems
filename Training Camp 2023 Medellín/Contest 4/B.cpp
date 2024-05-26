#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 

#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)


using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define point pair<lli,lli>
#define x first
#define y second

int main () {
	//fastIO();
	
    int n, m, l; cin>>n>>m>>l;

    vector<point> fishes(n);
    for(auto &[x, y]: fishes) cin>>x>>y;

    vector< point > man(m);
    for(auto &[x, y]: man){
        cin>>x;
        y = l;
    }

    auto transform = [](point p) -> point {
        return {p.x - p.y, p.x + p.y};
    };


    vector< pair< point, int > > events;
    
    for(auto p: fishes){
        events.push_back({p, -1});
    }

    forn(i, m){
        events.push_back({man[i], i});
    }


    for(auto &[p, t]: events){
        p = transform(p);
    }

    stable_sort(all(events), [](auto pp_1, auto pp_2){
        auto p_1 = pp_1.first;
        auto p_2 = pp_2.first;

        if(p_1.x != p_2.x) return p_1.x > p_2.x;
        if(p_1.y != p_2.y) return p_1.y < p_2.y;

        return pp_1.second < pp_2.second;
    });


    ordered_set<pair<lli,int>> s;
    vector<int> ans(m);
    int timee = 0;
    for(auto [p, idx]: events){
        if(idx == -1){
            s.insert({p.y, timee++});
        } else {
            ans[idx] = s.order_of_key({p.y+1, -1e9}); 
        }
    }

    for(auto x: ans) cout << x << endl;


	return 0;
}

