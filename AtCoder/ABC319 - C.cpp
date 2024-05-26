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

const int N = 3;

int mat[N][N];

int main () {
	//fastIO();

    forn(i, N){
        forn(j, N){
            cin>>mat[i][j];
        }
    }


    vector<int> perm = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    auto get_idx = [](int idx) -> pair<int,int> {
        return {idx/N, idx % N};
    };

    auto get_diss = [](vector< pair<int,int> > choose) -> int {
        vector<int> line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8;

        for(int i = 0; i < 9; i++){
            auto [x, y] = choose[i];
            if(x == 0){
                line_1.push_back(mat[x][y]);
            } else if(x == 1){
                line_2.push_back(mat[x][y]);
            } else if(x == 2){
                line_3.push_back(mat[x][y]);
            }

            if(y == 0){
                line_4.push_back(mat[x][y]);                
            } else if(y == 1){
                line_5.push_back(mat[x][y]);
            }else if(y == 2){
                line_6.push_back(mat[x][y]);
            }

            if(x == 0 && y == 0){
                line_7.push_back(mat[x][y]);
            }

            if(x == 1 && y == 1){
                line_7.push_back(mat[x][y]);
            }

            if(x == 2 && y == 2){
                line_7.push_back(mat[x][y]);
            } 


            if(x == 0 && y == 2){
                line_8.push_back(mat[x][y]);
            }

            if(x == 1 && y == 1){
                line_8.push_back(mat[x][y]);
            }

            if(x == 2 && y == 0){
                line_8.push_back(mat[x][y]);
            }
        }

        if(SZ(line_1) >= 3 && line_1[0] == line_1[1]) return 1;
        if(SZ(line_2) >= 3 && line_2[0] == line_2[1]) return 1;
        if(SZ(line_3) >= 3 && line_3[0] == line_3[1]) return 1;
        if(SZ(line_4) >= 3 && line_4[0] == line_4[1]) return 1;
        if(SZ(line_5) >= 3 && line_5[0] == line_5[1]) return 1;
        if(SZ(line_6) >= 3 && line_6[0] == line_6[1]) return 1;
        if(SZ(line_7) >= 3 && line_7[0] == line_7[1]) return 1;
        if(SZ(line_8) >= 3 && line_8[0] == line_8[1]) return 1;

        return 0;
    };

    int cnt_yes = 0, cnt_no = 0;
    do{
        vector< pair<int,int> > choose;
        forn(i, 9) choose.push_back(get_idx(perm[i]));

        if(get_diss(choose)) cnt_yes++;
        else cnt_no++;
    }while(next_permutation(all(perm)));

    // cout << cnt_no << " " << cnt_yes << endl;
    cout << fixed << setprecision(20) << (long double) cnt_no / (cnt_yes + cnt_no) << endl;

	return 0;
}

