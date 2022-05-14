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

bool check(lli teams, lli a, lli b)
{
    a -= teams;
    b -= teams;

    if(a < 0 || b < 0) return false;


    if(teams*2 <= a+b) return true;
    return false;
}



lli solve()
{
    lli a, b; cin>>a>>b;
    

    lli l = 0, r = 2e9, ans = 0;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;

        if(check(mid, a, b))
        {
            ans = mid;
            l = mid+1;
        }
        else
        {
            r = mid-1;
        }
    }

    return ans;
}

int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) cout << solve() << endl;


	return 0;
}

