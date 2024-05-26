#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int main () {
	//fastIO();
	
    int n, m, s, d; cin>>n>>m>>s>>d;
    int total_m = m;

    vector<int> slots(s);
    for(auto &x: slots) cin>>x;



    auto cmp_custom = [&](pair<int,int> a, pair<int,int> b) {
        return a.first > b.first;
    };

    priority_queue< pair<int,int>, vector<pair<int,int>>, decltype(cmp_custom) > pq(cmp_custom);
    for(int i = 0; i < s; i++){
        pq.push({slots[i], i});
    }

    // while(!pq.empty()) {
    //     cout << pq.top().first << " " << pq.top().second << endl;
    //     pq.pop();
    // }

    vector<int> ans(s);
    while(n && !pq.empty()) {
        auto cold = pq.top().first, idx = pq.top().second;
        pq.pop();


        int free = d - cold;
        

        int match = min(n, free);
        ans[idx] = match;

        n -= match;
        free -= match;
    }

    int pos = 0;
    for(int i = 0; i < s; i++) {
        if(!ans[i] && slots[i]) pos += slots[i];
    }

    // cout << "ANSSS" << endl;
    // for(int i = 0; i < s; i++){
    //     cout << ans[i] << " ";
    // }
    // cout << endl;

    // cout << pos << " " << total_m << endl;

    if(pos < total_m) {
        cout << "impossible" << endl;
    } else {
        for(int i = 0; i < s; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }


	return 0;
}

