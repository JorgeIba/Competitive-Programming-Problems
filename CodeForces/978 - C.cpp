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

const lli INF = 1e15;
const int MAXN = 1e5 + 10;

lli dp[MAXN][3];

const int START = 0, UP = 1, DOWN = 2;

void main_() {
    int n; cin>>n;
    vector< string > mat(2);
    for(auto &s: mat)
        cin>>s;
    
    auto cnt_vote = [&](int i, int j) -> lli {
        if(j >= n) return -INF;
        return mat[i][j] == 'A';
    };

    auto is_vote = [&](int i_1, int j_1, int i_2, int j_2, int i_3, int j_3) -> bool {
        auto val = (cnt_vote(i_1, j_1) + cnt_vote(i_2, j_2) + cnt_vote(i_3, j_3)) >= 2;
        // if(val) {
        //     cout << i_1 << ", " << j_1 << ", " << i_2 << ", " << j_2 << " " << i_3 << ", " << j_3 << endl;
        // }
        return val;
    };

    forn(i, n+2) {
        forn(j, 3) {
            dp[i][j] = -1;
        }
    }

    auto f = [&](const auto &f, int idx, int pos) -> lli {
        if(idx > n) return -INF;
        if(idx == n) {
            if(pos == START) return 0;
            return -INF;
        }

        lli &ans = dp[idx][pos];
        if(ans != -1) return ans;

        ans = -INF;

        if(pos == START) {
            lli opt_1 = is_vote(0, idx, 1, idx, 0, idx+1) + f(f, idx+1, UP);
            lli opt_2 = is_vote(0, idx, 1, idx, 1, idx+1) + f(f, idx+1, DOWN);
            lli opt_3 = is_vote(0, idx, 0, idx+1, 0, idx+2) + is_vote(1, idx, 1, idx+1, 1, idx+2) + f(f, idx+3, START);
            
            return ans = max({opt_1, opt_2, opt_3});
        } else if(pos == UP) {
            lli opt_1 = is_vote(1, idx, 1, idx+1, 0, idx+1) + f(f, idx+2, START);
            lli opt_2 = is_vote(1, idx, 1, idx+1, 1, idx+2) + is_vote(0, idx+1, 0, idx+2, 0, idx+3) + f(f, idx+3, UP);
            
            return ans = max({opt_1, opt_2});

        } else {
            lli opt_1 = is_vote(0, idx, 0, idx+1, 1, idx+1) + f(f, idx+2, START);
            lli opt_2 = is_vote(0, idx, 0, idx+1, 0, idx+2) + is_vote(1, idx+1, 1, idx+2, 1, idx+3) + f(f, idx+3, DOWN);
            
            return ans = max({opt_1, opt_2});
        }
    };

    cout << f(f, 0, START) << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

