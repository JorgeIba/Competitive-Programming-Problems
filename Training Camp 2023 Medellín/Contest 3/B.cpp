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


const int MAXN = 1e6+10;
int n, k; 
vector<int> nums;
int pos[MAXN];
lli dp[MAXN][2];


bool is_inside(int num, int l, int r){
    if(l <= r) return l <= pos[num] && pos[num] <= r;
    return l <= pos[num] || pos[num] <= r;
}

int distance(int pos, int l, int r, bool in_left) {
    if(in_left) return min((l - pos + n) % n, (pos - l + n) % n);
    return min((r - pos + n) % n, (pos - r + n) % n);
}

lli f(int idx, bool is_in_left) {
    int l, r;

    if(is_in_left){
        l = idx;
        r = (l + k - 1 + n) % n;
    } else {
        r = idx;
        l = (r - k + 1 + n) % n;
    }

    lli &ans = dp[idx][is_in_left];
    if(ans != -1) return ans;

    int curr = nums[idx];

    while(curr <= n && is_inside(curr, l, r)) {
        curr++;
    }

    if(curr == n+1) return ans = 0;

    lli move_l = f(pos[curr], true) + distance(pos[curr], l, r, true);
    lli move_r = f(pos[curr], false) + distance(pos[curr], l, r, false);

    return ans = min(move_l, move_r);
}


void main_(){
    cin>>n>>k;

    nums.resize(n);
    for(auto &x: nums) cin>>x;
    forn(i, n){
        pos[nums[i]] = i;
    }

    if(k == n) {
        cout << 0 << endl;
        return;
    }

    forn(i, n){ 
        memset(dp[i], -1, sizeof(dp[i]));
    }

    int curr = 1;
    int l = 0, r = k-1;
    while(curr <= n && is_inside(curr, l, r)) {
        curr++;
    }

    lli move_l = f(pos[curr], true) + distance(pos[curr], l, r, true);
    lli move_r = f(pos[curr], false) + distance(pos[curr], l, r, false);

    lli ans = min(move_l, move_r);

    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

