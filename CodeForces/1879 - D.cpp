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


const int MOD = 998244353;
const int MAXN = 3e5 + 1000;
const int MAXLOG = 32;

int main () {
	//fastIO();
	
	int n; cin>>n;
    vector<lli> nums(n+1);

    forr(i, 1, n) cin>>nums[i];


    vector< vector<int> > prefix(n+1, vector<int>(MAXLOG));

    for(int bit = 0; bit < MAXLOG; bit++){
        for(int i = 0; i <= n; i++){
            if(i)
                prefix[i][bit] = prefix[i-1][bit];

            lli x = nums[i];
            if(x & (1LL << bit)){
                prefix[i][bit] ^= 1; 
            }
        }
    }


    lli ans = 0;

    for(int bit = 0; bit < MAXLOG; bit++){
        array<lli, 2> ones = {0, 0}, zeros = {0, 0}; // {many, sum}

        for(int i = 0; i <= n; i++){
            if(prefix[i][bit] == 0){
                (ans += (1LL << bit) * (i + 1) % MOD * ones[0] % MOD) %= MOD;
                ans -= (1LL << bit) * ones[1] % MOD;
                if(ans < 0) ans += MOD;

                zeros[0]++;
                zeros[1] = (zeros[1] + i + 1) % MOD;
            } else {
                (ans += (1LL << bit) * (i + 1) % MOD * zeros[0] % MOD) %= MOD;
                ans -= (1LL << bit) * zeros[1] % MOD;
                if(ans < 0) ans += MOD;

                ones[0]++;
                ones[1] = (ones[1] + i + 1) % MOD;
            }
        }
    }

    cout << ans << endl;



	return 0;
}

