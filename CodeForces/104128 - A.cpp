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


const int INF = 1e9;

void main_(){
    int n, m, k; cin>>n>>m>>k;

    string s; cin>>s;

    vector< pair<int,int> > moves;
    int curr_i = 0, curr_j = 0;
    moves.push_back({curr_i, curr_j});

    for(auto c: s){
        if(c == 'L'){
            curr_j--;
        } else if(c == 'R'){
            curr_j++;
        } else if(c == 'U'){
            curr_i--;
        } else if(c == 'D'){
            curr_i++;
        }
        moves.push_back({curr_i, curr_j});
    }

    sort(all(moves));
    moves.erase(unique(all(moves)), moves.end());

    int mx_i = -INF, mn_i = INF;
    int mx_j = -INF, mn_j = INF;

    for(auto [x, y]: moves){
        mx_i = max(mx_i, x);
        mn_i = min(mn_i, x);

        mx_j = max(mx_j, y);
        mn_j = min(mn_j, y);
    }

    auto is_valid = [&](int x, int y){
        return (0 <= x + mn_i && x + mx_i < n && 0 <= y + mn_j && y + mx_j < m);
    };

    vector< vector<bool> > valid(n, vector<bool>(m));
    forn(i, n){
        forn(j, m){
            valid[i][j] = is_valid(i, j);
        }
    }

    vector< array<pair<int,int>, 2> > corners(2);
    bool ok = false;
    forn(i, n){
        forn(j, m){
            if(valid[i][j]) {
                corners[0][0] = {i, j}; // Superior Izquierda
                ok = true;
                break;
            }
        }
        for(int j = m-1; j >= 0; j--){
            if(valid[i][j]){
                corners[0][1] = {i, j}; // Superior derecha
                ok = true;
                break;
            }
        }

        if(ok) break;
    }

    bool ok_2 = false;
    for(int i = n-1; i >= 0; i--){
        forn(j, m){
            if(valid[i][j]) {
                corners[1][0] = {i, j}; // Inferior izquierda
                ok_2 = true;
                break;
            }
        }
        for(int j = m-1; j >= 0; j--){
            if(valid[i][j]){
                corners[1][1] = {i, j}; // Inferior derecha
                ok_2 = true;
                break;
            }
        }

        if(ok_2) break;
    }

    if(!ok) {
        if(k == 0){
            cout << n * m << endl;
        } else 
            cout << 0 << endl;
        return;
    }

    #define x first
    #define y second

    vector< vector<int> > prefix(n+1, vector<int>(m+1));

    for(auto [x_move, y_move]: moves){
        int x_1 = corners[0][0].x + x_move; 
        int x_2 = corners[1][1].x + x_move;

        int y_1 = corners[0][0].y + y_move;
        int y_2 = corners[1][1].y + y_move;

        prefix[x_1][y_1]++;
        prefix[x_2+1][y_1]--;
        prefix[x_1][y_2+1]--;
        prefix[x_2+1][y_2+1]++;
    }

    forn(i, n){
        forn(j, m){
            if(i-1 >= 0)
                prefix[i][j] += prefix[i-1][j];
            if(j-1 >= 0)
                prefix[i][j] += prefix[i][j-1];
            if(i-1 >= 0 && j-1 >= 0)
                prefix[i][j] -= prefix[i-1][j-1];
        }
    }

    int alives = 0;
    forn(i, n){
        forn(j, m){
            alives += valid[i][j];
        }
    }

    int ans = 0;
    forn(i, n){
        forn(j, m){
            ans += ((alives - prefix[i][j]) == k);
        }
    }

    cout << ans << endl;
}


int main () {
	// fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

