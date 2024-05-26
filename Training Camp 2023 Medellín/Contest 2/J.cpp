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

// OPT1 = 0 0 0
// OPT2 = 1 0 1
// OPT3 = 1 1 1

// int n, m;
// vector<int> row;

// const int MAXN = 2000 + 10;
// int dp[MAXN+10][2][2];

// bool f(int idx, int ant, int sent){
//     if(idx == m) return ant == 1;

//     int &ans = dp[idx][ant][sent];


//     int curr = row[idx] ^ sent;

//     if(curr && ant) {
//         bool opt1 = f(1, idx+1, 0);
        
//         return opt1;
//     } else if(curr && !ant){
//         bool opt2 = f(1, idx+1, 1);
//         bool opt3 = f(0, idx+1, 1);

//         return max(opt2, opt3);
//     } else if(!curr && ant) {
//         bool opt1 = f(0, idx+1, 0);
        
//         return opt1;
//     } else { // !curr && !ant
//         bool opt2 = f(0, idx+1, 1);
//         bool opt3 = f(1, idx+1, 1);

//         return max(opt2, opt3);
//     }
// }


vector< pair<int,int> > dir = {
        {-1, 0},
    {0, -1}, {0, 1},
        {1, 0}
};

int main () {
	//fastIO();

    int n, m; cin>>n>>m;

    vector< vector<int> > mat(n, vector<int>(m));

    forn(i, n){
        forn(j, m){
            char t; cin>>t;
            mat[i][j] = (t == 'B');
        }
    }

    
    auto is_inside = [&](int i, int j){
        if(i < 0 || i >= n || j < 0 || j >= m) return false;
        return true;
    };


    vector< vector<int> > ans(n, vector<int>(m, 3));
    forn(i, n){
        forn(j, m){
            mat[i][j] ^= 1;
            for(auto [dx, dy]: dir){
                if( is_inside(i+dx, j+dy) ){
                    mat[i+dx][j+dy] ^= 1;
                }
            }
        }
    }

    forn(i, n){
        forn(j, m){
            if(mat[i][j] == 1) {
                ans[i][j] = 2;
            }
        }
    }

    cout << 1 << endl;
    forn(i, n){
        forn(j, m){
            cout << ans[i][j];
        }
        cout << endl;
    }





	return 0;
}

