#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXN = 2e5 + 100;

int main () {
	// fastIO();

    int n; cin>>n;
    vector< pair<int,int> > builds(n);

    int sum = 0;
    int G = 0;
    bool zeros = false;
    for(auto &[g, f]: builds) {
        cin>>g>>f;
        sum += g;
        zeros = zeros || (g == 0);
        G = gcd(G, f);
    }
    
    if(sum == 0) {
        cout << "Y" << endl;
        return 0;
    }

    vector<int> fr(MAXN);
    for(auto [g, f]: builds) {
        fr[g]++;
    }

    // Check which sums you can do
    vector<int> options;
    for(int i = 0; i < MAXN; i++) {
        if(fr[i] == 0) continue;
        int f = fr[i];
        int x = 1;
        while(f) {
            int nxt = min(x, f);
            int opt = nxt * i;
            x <<= 1;
            options.push_back(opt);
            f -= nxt;
        }
    }

    bitset<MAXN> dp;
    dp[0] = 1;
    for(auto x: options) {
        dp = dp | (dp << x);
    }

    bool ans = false;
    dp[0] = zeros;
    for(int i = 0; i <= sum; i++) {
        if(dp[i]) {
            int left = i;
            int right = sum - left;
            // assert(dp[left] && dp[right]);
            assert(left >= 0 && right >= 0);

            if(!dp[left] || !dp[right]) continue;

            if(left % G == right % G) {
                ans = true;
            }
        }
    }

    if(ans) {
        cout << "Y" << endl;
    } else {
        cout << "N" << endl;
    }


	return 0;
}

