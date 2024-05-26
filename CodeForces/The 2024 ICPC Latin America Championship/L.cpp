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



int main () {
	// fastIO();

    int r, c, k; cin>>r>>c>>k;

    vector<string> mat(r);
    vector<string> pattern(r);

    forn(i, r) {
        cin>>mat[i]>>pattern[i];
    }

    vector<int> row_works(r);
    for(int i = 0; i < r; i++) {
        int cnt_ = count(all(mat[i]), '-');
        row_works[i] = (cnt_ == 0);
    }

    bool ans = true;
    for(int i = 0; i < r; i++) {
        int cnt_as = count(all(pattern[i]), '*');
        if(cnt_as == 0) continue;
        if(!row_works[i]) {
            ans = false;
        }
    }

    cout << (ans ? "Y" : "N") << endl;




	return 0;
}

