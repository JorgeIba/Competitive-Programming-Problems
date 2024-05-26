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
	fastIO();

    const int maxLOG = 31;

    vector<lli> powers(maxLOG);
    powers[0] = 1;
    for(int i = 1; i < maxLOG; i++) powers[i] = (powers[i-1] * 2);

    int n; cin>>n; 
    vector<pair<int,int>> nums(n);

    for(auto &x: nums) cin>>x.first>>x.second;

    vector<lli> ans_bit(maxLOG);


    for(int i = 0; i < maxLOG; i++){
        lli power = powers[i];

        vector< pair<int, int> > events;


        auto add_event = [&](pair<int,int> range) {
            auto [l, r] = range;
            events.push_back({l, 0});
            events.push_back({r, 1});
        };


        for(int j = 0; j < n; j++) {
            auto [l, r] = nums[j];

            if(r - l  >= power) {
                add_event({0, power-1});
                continue;
            }

            l = l % power;
            r = r % power;

            if(l  <= r) {
                add_event({l, r});
            }
            else{
                add_event({0, r});
                add_event({l, power-1});
            }
        }


        sort(all(events));

        
        int ans = 0, active = 0;
        for(auto [x, type]: events) {    
            if(type == 0) active++;
            else active--;

            ans = max(ans, active);
        }

        ans_bit[i] = ans;
    }

    int q; cin>>q;
    while(q--){
        int w; cin>>w;
        int first_bit = __builtin_ctz(w);
        cout << ans_bit[first_bit] << endl;
    }

	return 0;
}

