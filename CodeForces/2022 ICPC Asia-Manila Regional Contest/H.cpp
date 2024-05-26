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


typedef priority_queue< pair<lli,lli>, vector< pair<lli,lli> >, greater<pair<lli,lli>> > priority_queue_min;

int main () {
	//fastIO();
    lli n, limit; cin>>n>>limit;

    vector< array<lli,3> > routines(n);


    for(auto &r: routines) cin>>r[0];
    for(auto &r: routines) cin>>r[1];

    for(int i = 0; i < n; i++) 
        routines[i][2] = i;


    sort(all(routines), [&](auto r_1, auto r_2) {
        return r_1[0] < r_2[0];
    });


    priority_queue_min pq_ba;
    priority_queue< pair<lli,lli> > pq_a;
    priority_queue_min pq_b;
    

    vector<int> ans(n);
    int i = 0;
    for(i = 0; i < n; i++) {
        auto [a, b, idx] = routines[i];
        if(a <= limit) {
            limit -= a;
            ans[idx] = 1;
            pq_ba.push({b-a, idx});
            pq_a.push({a, idx});
        } else break;
    }

    for(; i < n; i++) {
        auto [a, b, idx] = routines[i];
        pq_b.push({b, idx});
    }

    vector<int> available(n, 1);
    while(true) {

        while(!pq_ba.empty() && !available[pq_ba.top().second])
            pq_ba.pop();

        while(!pq_a.empty() && !available[pq_a.top().second])
            pq_a.pop();


        bool is_option_1 = (!pq_ba.empty());
        bool is_option_2 = (!pq_a.empty() && !pq_b.empty());

        if(is_option_1 && is_option_2) {

            lli option_1 = pq_ba.top().first;
            lli option_2 = pq_b.top().first - pq_a.top().first;

            int idx_option_1  = pq_ba.top().second;
            int idx_option_2a = pq_a.top().second;
            int idx_option_2b = pq_b.top().second;

            if(option_1 > limit && option_2 > limit) break;

            if(option_1 < option_2) {
                available[idx_option_1] = 0;
                ans[idx_option_1] = 2;
                pq_ba.pop();
                limit -= option_1;
            } else {
                available[idx_option_2a] = 0;

                ans[idx_option_2a] = 0;
                ans[idx_option_2b] = 2;

                pq_a.pop();
                pq_b.pop();
                limit -= option_2;
            }
        } else if(is_option_1 && !is_option_2) {
            lli option_1 = pq_ba.top().first;
            int idx_option_1 = pq_ba.top().second;
            if(option_1 > limit) break;

            available[idx_option_1] = 0;
            ans[idx_option_1] = 2;

            pq_ba.pop();
            limit -= option_1;                
            
        } else if(!is_option_1 && is_option_2) {

            lli option_2 = pq_b.top().first - pq_a.top().first;
            int idx_option_2a = pq_a.top().second;
            int idx_option_2b = pq_b.top().second;
            
            if(option_2 > limit) break;

            available[idx_option_2a] = 0;

            ans[idx_option_2a] = 0;
            ans[idx_option_2b] = 2;

            pq_a.pop();
            pq_b.pop();
            limit -= option_2;

        } else {
            break;
        }
    }

    // cout << limit << endl;
    for(auto x: ans) cout << x;
    cout << endl;


	return 0;
}

