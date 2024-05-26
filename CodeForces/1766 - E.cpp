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


const int NONE = 4;
lli n; 
vector<lli> nums;

const int maxN = 3e5+100;
lli dp[maxN][5][5][5];


lli f(int idx, int first, int second, int third) {
    if(idx == n) return 0;

    auto num = nums[idx];

    lli &ans = dp[idx][first][second][third];
    if(ans != -1) return ans;
    ans = 0;


    if(num == 0) {
        return ans += (n-idx) + f(idx+1, first, second, third);
    } else if(num == 1){
        
        if(first == 1 || first == 3) {
            return ans += f(idx+1, 1, second, third);
        }

        if(first == NONE) {
            return ans += (n-idx) + f(idx+1, 1, second, third);
        }
        
        assert(first == 2);

        if(second == 1) {
            return ans += f(idx+1, first, second, third);
        }

        if(second == NONE) {
            return ans += (n-idx) + f(idx+1, first, 1, third);
        }

        assert(second == 2);

        if(third == 1) {
            return ans += f(idx+1, first, second, third);
        }

        if(third == NONE) {
            return ans += (n-idx) + f(idx+1, first, second, 1);
        }

        assert(false);

    } else if(num == 2) {

        if(first == 2 || first == 3) {
            return ans += f(idx+1, 2, second, third);
        }

        if(first == NONE) {
            return ans += (n-idx) + f(idx+1, 2, second, third);
        }

        assert(first == 1);

        if(second == 2) {
            return ans += f(idx+1, first, second, third);
        }

        if(second == NONE) {
            return ans += (n-idx) + f(idx+1, first, 2, third);
        }

        assert(second == 1);
        
        if(third == 2) {
            return ans += f(idx+1, first, second, third);
        }

        if(third == NONE) {
            return ans += (n-idx) + f(idx+1, first, second, 2);
        }

        assert(false);

    } else if(num == 3) {
        if(first == NONE) {
            return ans += (n-idx) + f(idx+1, 3, second, third);
        }
        
        return ans += f(idx+1, 3, second, third);
    }

    assert(false);

    return 0;
}



int main () {
	//fastIO();

    cin>>n;
    nums.resize(n);
    for(auto &x: nums) cin>>x;


    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    for(int i = 0; i < n; i++)
        ans += f(i, NONE, NONE, NONE);

    cout << ans << endl;
    


	return 0;
}

