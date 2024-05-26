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
	//fastIO();
    int n, q, s; cin>>n>>q>>s;

    vector< int > which_queue(s);
    for(auto &x: which_queue) {
        cin>>x;
        x--;
    }

    vector< int > size_queue(q);
    for(auto &x: size_queue) cin>>x;


    vector< pair<lli, vector<lli>> > wildcards(n+1);
    vector< lli > curr_queue(q);

    bool ok = true;
    forn(i, n){
        int d; cin>>d;
        forn(j, s){
            lli mb; cin>>mb;
            curr_queue[which_queue[j]] += mb;
        }

        wildcards[i] = {d, curr_queue};
        forn(j, q) {
            lli need_send = (curr_queue[j] > size_queue[j] ? curr_queue[j] - size_queue[j] : 0);
            if(need_send == 0) continue;

            for(int k = 0; k < i; k++){
                auto &[d_k, curr_k] = wildcards[k];
                lli taking_off = min({d_k, curr_k[j], need_send});
                d_k -= taking_off;
                need_send -= taking_off;
                // curr_k[j] -= taking_off;

                for(int l = k; l <= i; l++){
                    wildcards[l].second[j] -= taking_off;
                }
            }

            if(need_send > 0) {
                ok = false;
            } else {
                curr_queue[j] = size_queue[j];
            }
        }
    }

    for(auto &x: size_queue) x = 0;
    wildcards[n] = {0, curr_queue};
    forn(j, q){
        lli need_send = (curr_queue[j] > size_queue[j] ? curr_queue[j] - size_queue[j] : 0);
        if(need_send == 0) continue;

        for(int k = 0; k < n; k++){
            auto &[d_k, curr_k] = wildcards[k];
            lli taking_off = min({d_k, curr_k[j], need_send});
            d_k -= taking_off;
            need_send -= taking_off;
            // curr_k[j] -= taking_off;

            for(int l = k; l <= n; l++){
                wildcards[l].second[j] -= taking_off;
            }
        }

        if(need_send > 0) {
            ok = false;
        } else {
            curr_queue[j] = size_queue[j];
        }
    }

    cout << (ok ? "possible" : "impossible") << endl;

	return 0;
}

