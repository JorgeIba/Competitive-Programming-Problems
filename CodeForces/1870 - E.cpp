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


const int MAXN = 5000 + 10;
const int INF = 1e9;
bool dp[MAXN][MAXN];
int mexes[MAXN][MAXN];

void main_(){
	
    int n; cin>>n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;

    int ptr = 0;
    vector< bool > vis(n+2);
    auto get_mex = [&](){
        while(vis[ptr]) ptr++;
        return ptr;
    };

    for(int l = n-1; l >= 0; l--){
        fill(all(vis), 0);
        ptr = 0;
        for(int r = l; r < n; r++){
            vis[a[r]] = 1;
            mexes[l][r] = get_mex();
        }
    }

    dp[n][0] = 1;
    for(int l = n-1; l >= 0; l--){
        for(int k = 0; k < MAXN; k++)
            dp[l][k] = dp[l+1][k];
    
        for(int r = l; r < n; r++){
            int mex = mexes[l][r];
			bool dist_prev = (r == 0 ? 1 : (mexes[l][r-1] != mex));
			bool dist_next = (l == n-1 ? 1 : (mexes[l+1][r] != mex));

            if(dist_next && dist_prev) {
                for(int k = 0; k < MAXN; k++){
                    if(dp[r+1][k] && (k ^ mex) < MAXN) {
                        dp[l][k^mex] = 1;
                    }
                }
            }
        }
    }

    int ans = 0;
    for(int k = 0; k < MAXN; k++){
        if(dp[0][k])
            ans = k;
    }    
    cout << ans << endl;

    forn(i, n)
        forn(j, MAXN)
            dp[i][j] = 0;
    forn(i, n)
        vis[i] = 0;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}
