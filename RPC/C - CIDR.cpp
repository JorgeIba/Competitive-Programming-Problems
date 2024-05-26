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



bool check(lli mid, const vector<lli> &ips){
    set<lli> distinct;
    int rest = 32 - mid;
    
    uint32_t mask = (1LL << rest) - 1;
    
    mask = ~mask;

    
    // cout << mask << endl;
    

    // bitset<32> bs(mask);
    // cout << bs.to_string() << endl;

    for(auto ip: ips) {
        distinct.insert( ip & mask );
    }

    return SZ(distinct) == 1;
}



int main () {
	//fastIO();

    
    lli n; cin>>n;

    vector<lli> ips(n);

    for(int i = 0; i < n; i++){
        string ipstr; cin>>ipstr;

        istringstream ss(ipstr);
        string token;

        vector<lli> nums;
        while(getline(ss, token, '.')) {
            nums.push_back(stoll(token));
        }

        lli ip = (nums[0]<<24) + (nums[1]<<16) + (nums[2]<<8) + nums[3];
        ips[i] = ip;
    }

    
    lli l = 0, r = 32, ans = -1;
    while(l <= r) {
        lli mid = (l+r)/2;
        if(check(mid, ips)) {
            ans = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }

    if(ans == -1) {
        cout << 32 << endl;
    } else {
        cout << ans << endl;
    }

    




	return 0;
}

