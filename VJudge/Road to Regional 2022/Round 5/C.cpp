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


lli solveab(lli k){
    //ab <= k

    lli ans = 0;
    for(lli l = 1, r; l <= k; l = r+1) {
        r = k/(k/l);

        ans += (r-l+1) * (k/l);
    }

    return ans;
}


int main () {
	fastIO();

    lli k; cin>>k;

    lli ans = 0;
    for(lli l = 1, r; l <= k; l = r+1) {
        r = k/(k/l);


        ans += (r - l + 1) * solveab(k / l);
    }

    cout << ans << endl;
    


	return 0;
}

