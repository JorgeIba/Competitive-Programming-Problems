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

    int n, m; cin>>n>>m;
    pair<int,int> upper, lower;
    cin>>upper.first>>upper.second;
    cin>>lower.first>>lower.second;

    int ans = 0;
    int y_up = lower.first;
    int y_low = upper.first;
    int x_left = upper.second;
    int x_right = lower.second;

    
    int ones = 0;
    for(int i = 1; i <= n; i++) {
        if(y_low <= i && i <= y_up) {
            int left = x_left-1;
            int right = m - x_right;

            if((left & 1) && ones == 0) {
                ans++;
                ones++;
            } else if((left & 1) && ones > 0) {
                ones--;
            }

            if((right & 1) && ones == 0) {
                ans++;
                ones++;
            } else if((right & 1) && ones > 0) {
                ones--;
            }

        } else {
            if((m & 1) && ones == 0) {
                ans++;
                ones++;
            } else if((m & 1) && ones > 0) {
                ones--;
            }
        }
    }
    cout << ans << endl;


	return 0;
}

