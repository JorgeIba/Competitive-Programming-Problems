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


// Works for minimum

// O(n*k*log(n))
vector<int> dp_before, dp_curr;
template<class G>
void dac(int l, int r, int l_ans, int r_ans, const G &cost) {
    if(l > r) return;

    int mid = (l+r) / 2;

    // Find the best r option to do the cut: cost[mid, m_ans] + dp(r+1, k-1)
    pair<int,int> m_ans = {1e9, -1};
    for(int i = l_ans; i <= r_ans; i++){
        m_ans = min(m_ans, {cost(mid, i) + dp_before[i+1], i});
    }
    dp_curr[mid] = m_ans.first;

    dac(l, mid-1, l_ans, m_ans.second, cost);
    dac(mid+1, r, m_ans.second, r_ans, cost);
}

template<class G>
void divide_and_conquer(int n, int k, const G &cost){
    dp_curr.resize(n+2);
    for(int l = 1; l <= n; l++){ // Base cases
        dp_curr[l] = cost(l, n); // dp[l][1] -> 1 cut
    }
    dp_curr[n+1] = 0;

    for(int j = 2; j <= k; j++){
        dp_before = dp_curr;
        dac(1, n, 1, n, cost);
    }
}

int main () {
    fastIO();
	
    int n, k; cin>>n>>k;

    vector< vector<int> > mat(n+1, vector<int>(n+1));

    forr(i, 1, n){
        forr(j, 1, n){
            cin>>mat[i][j];
        }
    }

    forr(i, 1, n){
        forr(j, 1, n){
            mat[i][j] += mat[i][j-1] + mat[i-1][j] - mat[i-1][j-1];
        }
    }

    auto cost = [&](int i, int j){
        if(i > j) swap(i, j);
        int ans = (mat[j][j] - mat[i-1][j] - mat[j][i-1] + mat[i-1][i-1]) / 2;
        return ans;
    };


    divide_and_conquer(n, k, cost);
    cout << dp_curr[1] << endl;

	return 0;
}

