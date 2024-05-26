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


int maxD = 20;

lli dp[21][10][10];
lli f(lli pos, int last, int second_last) {
    if(pos == 20) return 1;


    lli &ans = dp[pos][last][second_last];
    if(ans != -1) return ans;

    ans = 0;
    for(int d = 0; d <= 9; d++) {
        if(last + second_last + d <= 9)
            ans += f(pos+1, second_last, d);
    }

    return ans;
}



int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    for(int d = 1; d <= 9; d++){
        ans += f(1, 0, d);
    }

    cout << ans << endl;

	return 0;
}

