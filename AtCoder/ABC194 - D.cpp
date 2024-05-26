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



int main () {
	//fastIO();
	
    int n; cin>>n;

    vector<ld> dp(n);
    dp[n-1] = 0;
    for(int i = n-1 - 1; i >= 0; i--){
        dp[i] = (ld) (i + 1 + (n - i - 1) * (1 + dp[i+1])) / (n - (i + 1));
    }

    cout << fixed << setprecision(20) <<  dp[0] << endl;


	return 0;
}

