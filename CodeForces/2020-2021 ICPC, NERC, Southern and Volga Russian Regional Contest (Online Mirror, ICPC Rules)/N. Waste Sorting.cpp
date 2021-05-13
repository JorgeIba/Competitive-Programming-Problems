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
    int t; cin>>t;
    while(t--)
    {
        lli c1, c2, c3; cin>>c1>>c2>>c3;
        lli a, b, c, d, e; cin>>a>>b>>c>>d>>e;
        c1 -= a, c2 -= b, c3 -= c;
        if(c1 < 0 || c2 < 0 || c3 < 0)
        {
            cout << "NO\n";
            continue;
        }
        lli caben_d = min(c1, d);
        lli caben_e = min(c2, e);
        
        d -= caben_d;
        e -= caben_e;

        c1 -= caben_d;
        c2 -= caben_e;

        c3 -= d;
        c3 -= e;

        if(c1 < 0 || c2 < 0 || c3 < 0)
        {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
    
	return 0;
}