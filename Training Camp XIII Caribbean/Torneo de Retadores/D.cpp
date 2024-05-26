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


const int MAXN = 5000 + 100;
ld dp[MAXN][MAXN];
bool visited[MAXN][MAXN];

ld f(int left, int right) {
    if(left == 0) return 1;
    if(left < 0 || right < 0 ) return 0;

    ld &ans = dp[left][right];
    if(visited[left][right]) return ans;

    visited[left][right] = true;
    ans = 0;

    if(right){
        ans += (ld) right / ((left - 1) + 1 + right) * f(left-1, right-1);
        ans += (ld) (left-1) / (((left - 1)) + 1 + right) * f(left - 2, right);
    } else{
        ans += (ld) (left-1) / ((left-1) + 1) * f(left-2, right);
    }

    return ans;
}


int main () {
	//fastIO();
	

    int n; cin>>n;
    vector<lli> nums(n);
    lli total_sum = 0;
    for(auto &x: nums) cin>>x, total_sum += x;

    sort(all(nums));
    reverse(all(nums));
    
    memset(dp, -1, sizeof(dp));

    ld sum = 0;
    for(int i = 0; i < n; i++) {
        sum += f(i, n - i - 1) * nums[i];
    }

    cout << fixed << setprecision(10) << sum << " " << total_sum - sum << endl;

	return 0;
}

