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
    int n, m; cin>>n>>m;

    vector< string > mat(n);
    for(auto &s: mat) cin>>s;


    vector< pair<int,int> > marks;

    forn(i, n) {
        forn(j, m) {
            if(mat[i][j] == '#') {
                marks.push_back({i, j});
            }
        }
    }

    auto get_total = [&](int i, int j) {
        int total = 0;
        for(auto [x, y]: marks) {
            total += abs(i - x) + abs(j - y);
        }

        int there = 0, not_there = 0;
        for(auto [x, y]: marks){
            there     += (x == i && y == j);
            not_there += (x != i || y != j); 
        }
            
        
        if(!there){
            total -= 2;
        } else {
            total -= not_there;
        }
        return total;
    };

    
    tuple< int, int, int > best = {n*m, 0, 0};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            tuple<int,int,int> opt = {get_total(i, j), i, j};
            best = min(best, opt);            
        }
    }


    auto [cost, best_x, best_y] = best;

    for(auto [x, y]: marks) {

        int dir_x = (x < best_x ? +1 : -1);
        int dir_y = (y < best_y ? +1 : -1);

        for(int i = x; i != best_x; i += dir_x)
            mat[i][y] = '#';

        for(int j = y; j != best_y; j += dir_y) {
            mat[best_x][j] = '#';
        }
    }

    mat[best_x][best_y] = '#';


    for(auto x: mat) cout << x << endl;




	return 0;
}

