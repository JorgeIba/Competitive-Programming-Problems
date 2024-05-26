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


lli n; 

vector<lli> getLastLeft(const vector<lli> &nums){

    vector<lli> last(n+1);
    stack<pair<lli,lli>> s;

    for(int i = 1; i <= n; i++) {
        auto num = nums[i];
        while(!s.empty() && s.top().first <= num) s.pop();

        if(s.empty()) last[i] = 1;
        else last[i] = s.top().second+1;

        s.push({num, i});
    }
    return last;
}

vector<lli> getLastRight(const vector<lli> &nums){

    vector<lli> last(n+1);
    stack<pair<lli,lli>> s;

    for(int i = n; i >= 1; i--) {
        auto num = nums[i];
        while(!s.empty() && s.top().first <= num) s.pop();

        if(s.empty()) last[i] = n;
        else last[i] = s.top().second-1;

        s.push({num, i});
    }
    return last;
}


const lli MOD = 1e9+7;
int main () {
	fastIO();

    cin>>n;
    vector<lli> nums(n+1);

    for(int i = 1; i <= n; i++) cin>>nums[i];

    
    auto lastLeft = getLastLeft(nums);
    auto lastRight = getLastRight(nums);


    
    for(int i = 1; i <= n; i++) {
        nums[i] = nums[i] % MOD;
        if(nums[i] < 0) nums[i] += MOD;
    }

    vector<lli> sum(n+1);

    for(int i = 1; i <= n; i++) {
        sum[i] = (sum[i-1] + nums[i]) % MOD;
    }



    vector<lli> total_sum(n+1);
    for(int i = 1; i <= n; i++) {
        total_sum[i] = (total_sum[i-1] + sum[i]) % MOD;
    }


    auto numsC = nums;
    numsC.push_back(0);
    reverse(all(numsC));

    vector<lli> sumC(n+2);

    for(int i = 1; i <= n; i++) {
        sumC[i] = (sumC[i-1] + numsC[i]) % MOD;
    }



    vector<lli> total_sumC(n+2);
    for(int i = 1; i <= n; i++) {
        total_sumC[i] = (total_sumC[i-1] + sumC[i]) % MOD;
    }




    /*
    for(int i = 1; i <= n; i++) cout << lastLeft[i] << " ";
    cout << endl;

    for(int i = 1; i <= n; i++)  cout << lastRight[i] << " ";
    cout << endl;
    */
    

    /*

    for(int i = 1; i <= n; i++)  cout << sum[i] << " ";
    cout << endl;

    for(int i = 1; i <= n; i++)  cout << total_sum[i] << " ";
    cout << endl;

    */
    
    auto changeIndex = [&](lli idx, lli n) -> lli{
        return n - idx + 1;
    };


    auto getTotalL = [&](lli l, lli r) {
        if(l > r) return 0LL;

        lli total = sum[r] * (r - l + 1) % MOD;

        lli take_off = (total_sum[r-1] - (l-2 >= 0? total_sum[l-2] : 0) ) % MOD;
        lli ans = (total - take_off) % MOD;

        return (ans < 0? ans + MOD : ans);
    };


    auto getTotalR = [&](lli l, lli r) {
        if(l > r) return 0LL;

        l = changeIndex(l, n);
        r = changeIndex(r, n);

        swap(l, r);

        // cout << l << " -- " << r << endl;
        // cout << sumC[r] << " ---- " << (r-l+1) << endl;

        lli total = sumC[r] * (r - l + 1) % MOD;

        lli take_off = (total_sumC[r-1] - (l-2 >= 0? total_sumC[l-2] : 0) ) % MOD;
        lli ans = (total - take_off) % MOD;

        return (ans < 0? ans + MOD : ans);
    };



    // cout << getTotalR(changeIndex(3), changeIndex(2)) << endl;

    
    lli ans = 0;
    for(int i = 1; i <= n; i++) {
        auto num = nums[i];
        lli idx_l = lastLeft[i], idx_r = lastRight[i];
        lli left = getTotalL(idx_l, i-1);
        lli right = getTotalR( i+1 , idx_r);


        lli l = (i - idx_l + 1) % MOD;
        lli r = (idx_r - i + 1) % MOD;

        lli total_left = left * (idx_r - i + 1) % MOD;
        lli total_right = right * (i - idx_l + 1) % MOD;
        lli ans_i = (total_left + total_right + (num*l % MOD *r % MOD)) % MOD;
        /*
        lli total_left = left * (idx_r - i + 1);
        lli total_right = right * (i - idx_l + 1);

        
        // lli ans_i =  0;
        
        */

        // cout << idx_l << " " << idx_r << " " <<  right  << " " << nums[i] << endl;

        // cout << total_left << " " << total_right << " " << idx_r << " " << idx_l << " " << ans_i << endl;

        assert(0 <= ans_i && ans_i < MOD);
        ans = (ans + ans_i) % MOD;
    }
    

    cout << ans << endl;
    

	return 0;
}

