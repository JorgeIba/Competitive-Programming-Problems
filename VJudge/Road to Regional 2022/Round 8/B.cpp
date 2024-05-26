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

const int maxN = 1e5+10;
vector<bool> broken(maxN);
lli dp[maxN];
int n, m; 
const lli MOD = 1e9+7;


lli fun(int idx) {
    if(idx == n) return 1;
    if(idx > n) return 0;

    lli &ans = dp[idx];
    if(ans != -1) return ans;

    if(broken[idx]) return ans = 0;

    return ans = (fun(idx+1) + fun(idx+2)) % MOD;
}


void main_(){
    cin>>n>>m;

    for(int i = 0; i < m; i++){
        int x; cin>>x;
        broken[x] = true;
    }

    memset(dp, -1, sizeof(dp));

    cout << fun(0) << endl;

	
}


int main () {
	//fastIO();
	
	int t = 1; 
	// cin>>t;
	while(t--) 
		main_();


	return 0;
}

