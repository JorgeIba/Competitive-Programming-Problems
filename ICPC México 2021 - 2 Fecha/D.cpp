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


int main () {
	fastIO();
    lli t; cin>>t;

    while(t--)
    {
        lli c, r, s; cin>>c>>r>>s;
        lli cabe = 0;
        lli total = c+r;
        if(total == 0)
        {
            cout << 0 << " " << 0 << endl;
            return 0;
        }
        if( total % s == 0 ) cabe = total/s;
        else cabe = total/s + 1;

        lli max_mamo = min(r, cabe);
        lli min_ans = cabe - max_mamo;

        lli max_ans = c / s;
        if( c % s != 0 && r == 0) max_ans++;

        cout << max_ans << " " << min_ans << endl;
    }

	


	return 0;
}

