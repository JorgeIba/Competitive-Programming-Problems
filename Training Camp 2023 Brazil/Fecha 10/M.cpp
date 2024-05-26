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

    vector< string > mat(n);
    for(auto &s: mat) cin>>s;

    int ans = 1e9;

    
    for(int mask = 1; mask < (1 << n); mask++){
        vector<int> costs(n);
        for(int j = 0; j < n; j++){
            if(mask & (1 << j)){
                for(int k = 0; k < n; k++){
                    costs[k] += mat[j][k] - '0';
                }
            }
        }    

        int many = __builtin_popcount(mask);

        sort(all(costs));

        int ans_mask = 0;
        for(int j = 0; j <= n - many; j++){
            ans_mask += costs[j];
        }

        ans = min(ans, ans_mask);
    }

    cout << ans << endl;



	return 0;
}

