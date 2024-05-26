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

vector< vector<string> > mat;

vector<int> z_function(const string & s){
    int n = s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; ++i){
        if(i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if(i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}


void solve_2(){
    string s_1 = mat[1][0];
    string s_2 = mat[0][1];

    auto check_1 = s_1 + "$" + s_2;
    auto check_2 = s_2 + "$" + s_1;

    auto zf_1 = z_function(check_1);
    auto zf_2 = z_function(check_2);

    vector<string> sol(2);

    int n = SZ(s_1);
    int offset = n+1;

    bool multiple = false;
    bool is_ans = false;
    for(int i = offset; i < SZ(check_1); i++) {
        if(multiple) break;
        if(i + zf_1[i] == SZ(check_1)) {
            int j = zf_1[i] + offset;
            if(j == SZ(check_2)) continue;
            
            if( j + zf_2[j] == SZ(check_2)  ) {
                is_ans = true;
                if(!sol[0].empty()) multiple = true;
                sol[0] = s_1.substr(j - offset, zf_2[j]);
                sol[1] = s_2.substr(i - offset, zf_1[i]);
                // cout << "VALID 1: " << s_2.substr(i - offset, zf_1[i]) << endl;
                // cout << "VALUD 2: " << s_1.substr(j - offset, zf_2[j]) << endl;
            }            
        }
    }  

    if(!is_ans) {
        cout << "NONE" << endl;
    } else if(multiple) {
        cout << "MANY" << endl;
    } else {
        cout << "UNIQUE" << endl;
        for(auto s: sol) cout << s << endl;
    }

}


int main () {
	//fastIO();

    int n; cin>>n;

    mat.assign(n, vector<string>(n));

    forn(i, n) {
        forn(j, n) {
            cin>>mat[i][j];
        }
    }

    if(n == 2) {
        solve_2();
        return 0;
    }


    int total = 0;
    forn(i, n) {
        forn(j, n) {
            if(i == j) continue;
            total += SZ(mat[i][j]);
        }
    }

    int total_s = total / (2 * (n-1));

    vector<int> sizes(n);
    vector<string> poss(n);
    for(int i = 0; i < n; i++) {
        int total_i = 0;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            total_i += SZ(mat[i][j]);
        }

        sizes[i] = (total_i - total_s) / (n-2);
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            poss[i] = mat[i][j].substr(0, sizes[i]);
        }
    }


    // Check

    vector< vector<string> > check(n, vector<string>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) check[i][j] = "*";
            else check[i][j] = poss[i] + poss[j];
        }
    }

    bool non_empty = false;
    for(auto s: poss) non_empty |= (s.empty());

    if(mat == check && !non_empty) {
        cout << "UNIQUE" << endl;
        for(auto s: poss) cout << s << endl;
        
    } else {
        cout << "NONE" << endl;
    }

	return 0;
}

