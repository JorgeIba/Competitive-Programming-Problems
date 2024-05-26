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

int solve(const vector<string> &mat, int k) {
    int n = SZ(mat);
    int m = SZ(mat[0]);
    k++;

    vector< vector<int> > acum_col(n, vector<int>(m));
    vector< vector<int> > acum_diag(n, vector<int>(m));

    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            if(i)
                acum_col[i][j] = acum_col[i-1][j];

            acum_col[i][j] += mat[i][j] == '#';
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i-1 >= 0 && j-1 >= 0)
                acum_diag[i][j] += acum_diag[i-1][j-1];

            acum_diag[i][j] += mat[i][j] == '#';
        }
    }

    auto is_inside = [&](int i, int j) {
        return 0 <= i && i < n && 0 <= j && j < m;
    };


    auto limits = [&](int i_right, int j_right, int k) -> tuple<int, int, int, int> {
        int i_left = i_right - k + 1;
        int j_left = j_right - k + 1;

        if(is_inside(i_left, j_left) && is_inside(i_right, j_right)) {
            return {i_left, j_left, i_right, j_right};
        } else if(!is_inside(i_left, j_left) && is_inside(i_right, j_right)) {
            int moves = min(i_right+1, j_right+1);

            tie(i_left, j_left) = pair<int,int> {i_right - moves + 1, j_right - moves + 1};

            return {i_left, j_left, i_right, j_right};

        } else if(is_inside(i_left, j_left) && !is_inside(i_right, j_right)) {

            int moves = min(n-i_left, m-j_left);

            tie(i_right, j_right) = pair<int,int> {i_left + moves - 1, j_left + moves - 1};

            return {i_left, j_left, i_right, j_right};
        } else {
            if(j_left >= n) return {-1, -1, -1, -1};

            int need_left_i = abs(i_left);
            int moves_j = m - j_left - 1;

            if(need_left_i > moves_j) return {-1, -1, -1, -1};

            i_left += need_left_i;
            j_left += need_left_i;

            int moves = min(n-i_left, m-j_left);
            tie(i_right, j_right) = pair<int,int> {i_left + moves - 1, j_left + moves - 1};

            return {i_left, j_left, i_right, j_right};
        }


    };


    // cout << " ------ " << endl;
    // for(auto x: mat) cout << x << endl;
    // cout << " ------ " << endl;


    int ans = 0;

    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = 0, up = k; j < min(m, k); j++, up--) {
            int above = max(0, i - up + 1);
            
            int sum_col = acum_col[i][j] - (above - 1 >= 0 ? acum_col[above - 1][j] : 0);
            // debugg(sum_col);
            sum += sum_col;
        }

        ans = max(ans, sum);

        for(int l = 0, r = k; l < m; l++, r++) {
            int above = max(0, i - k + 1);

            auto [i_left, j_left, i_right, j_right] = limits(i, r, k);


            if(i_left != -1)
                sum += acum_diag[i_right][j_right] - (i_left-1 >= 0 && j_left-1 >= 0 ? acum_diag[i_left-1][j_left-1] : 0);


            sum -= (acum_col[i][l] - (above-1 >= 0 ? acum_col[above-1][l] : 0));

            ans = max(ans, sum);
        }
    }

    return ans;
}

void rotate(vector<string> &mat) {
    int n = SZ(mat);
    int m = SZ(mat[0]);

    vector<string> b(m, string(n, '.'));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            b[m - j - 1][i] = mat[i][j]; 
        }
    }

    mat = b;
}


void main_(){
    int n, m, k; cin>>n>>m>>k;

    vector<string> mat(n);
    for(auto &x: mat) cin>>x;


    // auto print_mat = [&]() -> void {
    //     cout << " ------ " << endl;
    //     for(auto x: mat) cout << x << endl;
    //     cout << " ------ " << endl;
    // };

    int ans = 0;
    // print_mat();
    ans = solve(mat, k);


    rotate(mat);
    // print_mat();
    ans = max(ans, solve(mat, k));


    rotate(mat);
    // print_mat();
    ans = max(ans, solve(mat, k));


    rotate(mat);
    // print_mat();
    ans = max(ans, solve(mat, k));


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

