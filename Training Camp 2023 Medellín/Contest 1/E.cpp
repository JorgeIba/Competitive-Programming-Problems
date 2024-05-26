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



const int MAXN = 1e5+100;
const int MOD = 1e9+7;
int main () {
	//fastIO();
	
    int n, m; cin>>n>>m;

    vector<lli> fib(MAXN);
    fib[0] = fib[1] = 1;
    forr(i, 2, MAXN-1)
        fib[i] = (fib[i-1] + fib[i-2]) % MOD;

    lli ans = (2*fib[n] + 2*fib[m]) % MOD;
    cout << (ans - 2 + MOD) % MOD << endl;



	return 0;
}

