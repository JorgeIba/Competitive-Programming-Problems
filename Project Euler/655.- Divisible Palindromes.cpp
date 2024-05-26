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


const int MOD = 10000019;
const int N = 32;
// const int MOD = 109;
// const int N = 6;
// const int MOD = 104729;
// const int N = 14;

int pow10[N+1];
int dp[N][MOD];

int f(int l, int mod, const int start){
    int r = start - l;
    if(r > l) {
        return mod == 0;
    }

    int &ans = dp[l][mod];
    if(ans != -1) return ans;

    ans = 0;
    for(int d = 0; d <= 9; d++){
        lli new_mod = mod + d*pow10[l];
        if(l != r){
            new_mod += d*pow10[r];
        }
        ans += f(l-1, new_mod % MOD, start);
        assert(ans >= 0);
    }

    return ans;
}


int main () {
	//fastIO();
    pow10[0] = 1;
    forr(i, 1, N) pow10[i] = 10LL * pow10[i-1] % MOD;

    memset(dp, -1, sizeof(dp));
    int odd = f(N-1, 0, N-1) - 1 ;
    cout << odd << endl;


    memset(dp, -1, sizeof(dp));
    int even = f(N-2, 0, N-2) -1;
    cout << even << endl;

    int ans = odd + even;

    cout << ans << endl;



	return 0;
}

