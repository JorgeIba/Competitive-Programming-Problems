#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

vector< string > mat(2);
lli n;

const lli MAXN = 2e5 + 100;
lli dp[2][MAXN];


lli f(lli i, lli j) {
    if(j >= n-1) return 0;


    lli &ans = dp[i][j];
    if(ans != -1) return ans;

    if(i == 0) {
        lli down = mat[i+1][j] - '0';
        lli right = mat[i][j+1] - '0';

        if(down && right) {
            ans = min(  f(i+1, j+2),   f(i, j+1)  ) + 1;
        } else if(down && !right) {
            ans = min( f(i+1, j+2), f(i, j+1) + 1) ;
        } else if(!down && right) {
            ans = f(i, j+1);
        } else{
            ans = f(i, j+1);
        }

    } else {

        lli up = (mat[i-1][j] - '0');
        lli right = mat[i][j+1] - '0';
    
        if(up && right) {
            ans = min(  f(i-1, j+2),   f(i, j+1)  ) + 1;
        } else if(up && !right) {
            ans = min( f(i-1, j+2), f(i, j+1) + 1);
        } else if(!up && right) {
            ans = f(i, j+1);
        } else{
            ans = f(i, j+1);
        }
    }

    return ans;
}


int main () {
	//fastIO();

    memset(dp, -1, sizeof(dp));

    cin>>n;
    cin>>mat[0]>>mat[1];

    lli count_marks = count(all(mat[0]), '1') + count(all(mat[1]), '1');

    cout << count_marks - f(0, 0) << endl;

	return 0;
}

