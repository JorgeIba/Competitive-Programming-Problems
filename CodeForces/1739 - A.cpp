#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


vector<pair<int,int>> moves = {
    {-2, 1}, {-1, 2}, {1, 2}, {2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
};


int main () {
	//fastIO();
    lli t; cin>>t;
    
    while(t--) {
        lli n, m; cin>>n>>m;
        

        auto is_isolated = [&](int i, int j) {
            for(auto d: moves) {
                int x = i + d.first, y = j + d.second;

                if((1 <= x && x <= n && 1 <= y && y <= m)) {
                    return false;
                }

            }
            return true;
        };


        int n_ans = 1, m_ans = m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(is_isolated(i, j)) {
                    n_ans = i, m_ans = j;
                }
            }
        }
        cout << n_ans << " " << m_ans << endl;
    }

	return 0;
}

