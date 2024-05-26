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

const int MAX_P = 1600;
const int MAX_N = 18;

bool is_prime[MAX_P];
void sieve(){
    fill(is_prime, is_prime + MAX_P, true);
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i < MAX_P; i++){
        for(int j = 2*i; j < MAX_P; j += i) {
            is_prime[j] = false;
        }
    }
}


lli dp[MAX_N][MAX_P][2];
vector< vector<int> > nums;
lli f(int idx, int sum, bool already, const vector<int> &limit){
    if(idx == -1) {
        return is_prime[sum];
    }

    int limit_d = (already ? 9 : limit[idx]);

    lli &ans = dp[idx][sum][already];
    if(ans != -1) return ans;

    ans = 0;
    for(int d = 0; d <= limit_d; d++){
        ans += f(idx-1, sum + d, already || (d < limit_d), limit);
    }

    return ans;
}



int main () {
	//fastIO();

    sieve();


    auto check = [&](lli k){
        vector<int> limit;
        while(k){
            limit.push_back(k % 10);
            k /= 10;
        }

        memset(dp, -1, sizeof(dp));

        return f(SZ(limit)-1, 0, false, limit);
    };

    lli n = 1e16;

    lli l = 1, r = 1e18, ans = r;
    while(l <= r){
        lli mid = (l+r)/2;
        if(check(mid) >= n){
            ans = mid;
            r = mid-1;
        } else {
            l = mid+1;
        }
    }

    cout << ans << endl;


	return 0;
}

