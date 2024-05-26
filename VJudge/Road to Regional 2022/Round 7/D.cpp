#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
    int n, k; cin>>n>>k;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    map<int, int> last;
    for(auto x: nums) last[x] = 1e9;


    vector<int> next_equal(n);
    for(int i = n-1; i >= 0; i--) {
        next_equal[i] = last[ nums[i] ];
        last[nums[i]] = i;
    }



    set< pair<int,int> > pq;
    map<int, int> metiste;

    int ans = 0;
    for(int i = 0; i < n; i++) {
        auto num = nums[i];

        if(metiste.count(num)) {
            pair<int,int> quitar = {metiste[num], num};
            pq.erase(quitar);

            metiste[num] = next_equal[i];

            pq.insert({next_equal[i], num});
        } else {
            ans++;

            if(SZ(pq) < k) {
                metiste[num] = next_equal[i];
                pq.insert({next_equal[i], num});
            } else {
                auto [next_greatest, greatest] = *pq.rbegin(); 
                pq.erase({next_greatest, greatest});


                metiste.erase(greatest);
                
                metiste[num] = next_equal[i];
                pq.insert({next_equal[i], num});
            }
        }

    }

    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

