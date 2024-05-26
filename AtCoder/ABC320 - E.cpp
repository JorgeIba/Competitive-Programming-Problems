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

typedef array<lli,4> pairi;
void main_(){
    int n, m; cin>>n>>m;

    vector< tuple<lli,lli,lli> > events(m);
    for(auto &[t, w, s]: events)
        cin>>t>>w>>s;

    
    priority_queue< pairi, vector<pairi>, greater<pairi> > pq;
    
    set<int> pool;
    forn(i, n){
        pool.insert(i);
    }

    vector<lli> ans(n);
    forn(i, m){
        auto [t, w, s] = events[i];
        pq.push({t, 1, w, s});
    }

    while(!pq.empty()){
        auto [timee, typee, a, b] = pq.top(); pq.pop();
        if(typee == 1){
            if(pool.empty()) continue;

            auto idx = *pool.begin(); pool.erase(idx);
            ans[idx] += a;

            pq.push({timee + b, 0, idx, idx});
        } else {
            pool.insert(a);
        }
    }


    for(auto x: ans) cout << x << endl;


}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

