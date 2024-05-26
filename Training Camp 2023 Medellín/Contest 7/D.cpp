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


const int SIG = 30;

int main () {
	//fastIO();

    int n; cin>>n;
    string s, t; cin>>s>>t;


    vector< vector< vector<int> > > mat(SIG, vector<vector<int>>(SIG));

    int cnt = 0;
    forn(i, n){
        if(s[i] == t[i]) continue;
        cnt++;

        auto c = s[i] - 'a';
        auto d = t[i] - 'a';

        if(SZ(mat[c][d]) > 2) continue;

        mat[c][d].push_back(i+1);
    }

    if(cnt < 2) {
        cout << cnt << endl;
        cout << -1 << " " << -1 << endl;
        return 0;
    }

    forn(i, SIG){
        forn(j, SIG){
            if(SZ(mat[i][j]) > 0 && SZ(mat[j][i]) > 0){
                assert(i != j);
                cout << cnt-2 << endl;
                cout << mat[i][j][0] << " " << mat[j][i][0] << endl;
                return 0;
            }
        }
    }


    forn(i, SIG){
        forn(j, SIG){
            if(SZ(mat[i][j]) == 0) continue;

            forn(k, SIG){
                if(SZ(mat[k][i]) > 0){
                    assert(k != j);
                    assert(k != i);
                    assert(i != j);

                    cout << cnt-1 << endl;
                    cout << mat[i][j][0] << " " << mat[k][i][0] << endl;
                    return 0;
                }
            }
        }
    }

    cout << cnt << endl;
    cout << -1 << " " << -1 << endl;

	return 0;
}

