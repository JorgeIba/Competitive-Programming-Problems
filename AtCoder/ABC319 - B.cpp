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

    int n; cin>>n;

    string ans(n+1, '-');
    for(int i = 0; i <= n; i++){
        int ans_i = -1;
        for(int j = 1; j <= 9; j++){
            if(n % j == 0 && i % (n/j) == 0){
                ans_i = j;
                break;
            }
        }
        
        if(ans_i != -1) ans[i] = ans_i + '0';
    }

    cout << ans << endl;


	return 0;
}

