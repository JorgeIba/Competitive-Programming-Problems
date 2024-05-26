#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const lli INF = 1e9;
int main () {
	//fastIO();
	lli P; cin>>P;

    auto nC2 = [](lli n) {
        return n*(n-1) / 2;
    };

	vector< array<lli,2> > dp(P+1, {INF, -INF});

	dp[0] = {0,0};
    for(int p = 0; p <= P; p++){
        for(int nodes = 2; p + nC2(nodes) <= P; nodes++){
            lli new_p = p + nC2(nodes);
            if(dp[p][0] + nodes < dp[new_p][0]) {
                dp[new_p] = {dp[p][0] + nodes, dp[p][1] + dp[p][0]*nodes};
            } else if(dp[p][0] + nodes == dp[new_p][0]) {
                dp[new_p][1] = max( dp[new_p][1], dp[p][1] + dp[p][0]*nodes );
            }
            
        }
    }

    cout << dp[P][0] << " " << dp[P][1] << endl;


	return 0;
}

