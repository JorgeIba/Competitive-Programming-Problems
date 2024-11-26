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



const int MAXN = 80 + 5;
const lli INF = 1e18;
lli P[MAXN][MAXN];
lli mat[MAXN][MAXN][2];
lli sp[MAXN][MAXN][MAXN][MAXN];
int n; 


struct state{
    lli p_need = INF, remaining = -INF;
    state() {}

    state(lli p, lli rem): p_need(p), remaining(rem) {}

    bool operator<(const state &s) const {
        if(p_need != s.p_need) {
            return p_need < s.p_need;
        }
        return remaining > s.remaining;
    }
};



bool is_inside(int x, int y){
    return (0 <= x && x < n && 0 <= y && y < n);
}


int main () {
	// fastIO();

    cin>>n;
    forn(i, n) {
        forn(j, n) {
            cin>>P[i][j];
        }
    }

    forn(i, n) {
        forn(j, n-1) {
            lli x; cin>>x;
            mat[i][j][0] = x;
        }
    }

    forn(i, n-1) {
        forn(j, n) {
            lli x; cin>>x;
            mat[i][j][1] = x;
        }
    }

    forn(i, n) {
        forn(j, n) {
            forn(k, n){
                forn(l, n) {
                    sp[i][j][k][l] = INF;
                }
            }
        }
    }


    forn(i_start, n) {
        forn(j_start, n) {
            sp[i_start][j_start][i_start][j_start] = 0;
            queue<pair<int,int>> q;
            q.push({i_start, j_start});

            
            vector< vector<int> > cnt(n, vector<int>(n, 0));
            forn(x, n) {
                forn(y, n) {
                    if(is_inside(x-1, y) && x-1 >= i_start)
                        cnt[x][y]++;
                    if(is_inside(x, y-1) && y-1 >= j_start)
                        cnt[x][y]++;
                    
                }
            }

            while(!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                lli cost = sp[i_start][j_start][x][y];

                if(is_inside(x+1, y)) {
                    sp[i_start][j_start][x+1][y] = min(sp[i_start][j_start][x+1][y], cost + mat[x][y][1]);
                    cnt[x+1][y]--;
                    if(cnt[x+1][y] == 0) {
                        q.push({x+1, y});
                    }
                }

                if(is_inside(x, y+1)) {
                    sp[i_start][j_start][x][y+1] = min(sp[i_start][j_start][x][y+1], cost + mat[x][y][0]);
                    cnt[x][y+1]--;
                    if(cnt[x][y+1] == 0) {
                        q.push({x, y+1});
                    }
                }
            }
        }
    }



    vector< vector<state> > dp(n, vector<state>(n));
    dp[0][0] = state(0, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == 0 && j == 0) continue;

            for(int x = 0; x <= i; x++) {
                for(int y = 0; y <= j; y++) {

                    if(x == i && y == j) continue;

                    // bool check = (x == 0 && y == 0) || (P[x][y] < P[i][j]) || (i == n-1 && j == n-1);

                    // if(!check) continue;
                    
                    auto [points, rem] = dp[x][y];
                    lli p_move = abs(x-i) + abs(y-j);


                    if(rem >= sp[x][y][i][j]) {
                        dp[i][j] = min(dp[i][j], state(points + p_move, rem - sp[x][y][i][j]));
                    } else {
                        lli need = sp[x][y][i][j] - rem;
                        lli p_need = (need + P[x][y] - 1) / P[x][y];
                        dp[i][j] = min(dp[i][j], state(points + p_need + p_move, p_need * P[x][y] - need));
                    }
                }
            }
        }
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         cout << "(" << dp[i][j].p_need << ", " << dp[i][j].remaining << ")   ";
    //     }
    //     cout << endl;
    // }


    cout << dp[n-1][n-1].p_need << endl;


	return 0;
}

