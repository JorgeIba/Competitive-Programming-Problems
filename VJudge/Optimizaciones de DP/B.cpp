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



const int MAXN = 500 + 10;

int mat[MAXN][MAXN];

int main () {
	//fastIO();
	
    int n; cin>>n;

    forr(i, 1, n){
        forr(j, 1, n){
            cin>>mat[i][j];
        }
    }

    vector<int> A(n+1);
    forr(j, 1, n){
        int mn = 1e9;
        forr(i, 1, n) {
            mn = min(mn, mat[i][j]);
        }
        A[j] = mn;
    }

    vector<int> B(n+1);
    bool ok = true;
    forr(i, 1, n){
        vector<int> diffs(n+1);
        forr(j, 1, n) {
            diffs[j] = mat[i][j] - A[j];
        }
        int mn = *min_element(diffs.begin()+1, diffs.end());
        int cnt = count(diffs.begin()+1, diffs.end(), mn);

        ok = ok && (cnt == n);
        B[i] = mn;
    }

    if(ok){
        cout << "Yes" << endl;
        forr(i, 1, n) cout << B[i] << " ";
        cout << endl;
        forr(i, 1, n) cout << A[i] << " ";
        cout << endl;
    } else {
        cout << "No" << endl;
    }





	return 0;
}

