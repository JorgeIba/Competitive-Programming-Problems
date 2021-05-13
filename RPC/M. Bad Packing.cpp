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

const int maxN = 1e3+1, maxK = 1e5+1;
int dp[maxN][maxK][2];
vector<lli> wss;

lli n, k;
int INF = 1e9;

lli fun(lli idx, lli curr_w, bool taken)
{
    if(curr_w > k) return INF;
    if(idx == n) return (taken?curr_w:INF);

    int &ans = dp[idx][curr_w][taken];
    if(ans != -1) return ans;

    lli si = fun(idx+1, curr_w + wss[idx], true);
    lli no = fun(idx+1, curr_w, taken);

    
    return ans = min(si, no);
}


int main () {
	//fastIO();
    cin>>n>>k;

    wss.resize(n);
    for(auto &x: wss) cin>>x;

    sort(all(wss));

    memset(dp, -1, sizeof(dp));
    cout << fun(0, 0, false) << endl;


	return 0;
}