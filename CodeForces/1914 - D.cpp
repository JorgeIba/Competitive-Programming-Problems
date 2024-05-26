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

void main_(){
    int n; cin>>n;

    vector< vector<pair<int,int>> > scores(3, vector<pair<int,int>>(n));
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < n; i++) {
            cin>>scores[j][i].first;
            scores[j][i].second = i;
        }
    }

    for(int j = 0; j < 3; j++) {
        sort(all(scores[j]));
        reverse(all(scores[j]));
    }


    int ans = 0;
    for(int i = 0; i < min(n, 10); i++) {
        auto [score_i, idx_i] = scores[0][i];
        for(int j = 0; j < min(n, 10); j++) {
            auto [score_j, idx_j] = scores[1][j];
            for(int k = 0; k < min(n, 10); k++) {
                auto [score_k, idx_k] = scores[2][k];
                if(idx_i != idx_j && idx_i != idx_k && idx_j != idx_k) {
                    ans = max(ans, score_i + score_j + score_k);
                }
                
            }
        }
    }
    cout << ans << endl;

    

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

