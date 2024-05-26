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


const int MAXN = 1e5+10;

lli dp[MAXN];

lli f(lli n) {
    if(n == 0 || n == 1) return 0;

    lli &ans = dp[n];
    if(ans != -1) return ans;

    vector<lli> to_mex;

    
    for(int l = 0; l < n-1; l++) {
        int r = n - (l+2);
        
        to_mex.push_back( f(l) ^ f(r) );
    }

    bitset<MAXN> mex;
    for(auto x: to_mex){
        if(x > n) continue; 
        mex[x] = 1;
    }

    int g = 0;
    while(mex[g]) g++;

    return ans = g;
}


vector< int > grundy = {8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4};


int main () {
	//fastIO();
    // memset(dp, -1, sizeof(dp));


    int cut = 34;

    int n = 1e6;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int f_i = grundy[i % cut];
        ans += (f_i != 0);
    }

    cout << ans-3 << endl;


	return 0;
}

