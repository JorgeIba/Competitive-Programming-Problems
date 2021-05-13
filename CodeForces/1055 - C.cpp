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

lli get_area(lli la, lli ra, lli lb, lli rb)
{
    return min(ra, rb) - max(la, lb) + 1;
}


int main () {
	//fastIO();
    lli la, ra, ta; cin>>la>>ra>>ta;
    lli lb, rb, tb; cin>>lb>>rb>>tb;

    lli g = __gcd(ta, tb);


    lli q1 = floor((double)(lb-la)/g);
    lli q2 = ceil((double)(lb-la)/g);

    lli ans = 0;

    lli diff1 = la-lb+g*q1;
    lli diff2 = la-lb+g*q2;

    //cout << q1 << " " << q2 << endl;

    ans = max( get_area(lb+diff1, ra-la+lb+diff1, lb, rb),  get_area(lb+diff2, ra-la+lb+diff2, lb, rb) );
    if(ans < 0) cout << 0 << endl;
    else cout << ans << endl;

	return 0;
}