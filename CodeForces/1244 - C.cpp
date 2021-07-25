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
	//fastIO();
    lli n, p, w, d; cin>>n>>p>>w>>d;

    for(lli y = 0; y<w; y++)
    {
        if((p - y*d) % w != 0) continue;

        lli x = (p - y*d)/w;

        if(x+y <= n && x >= 0)
        {
            cout << x << " " << y << " " << n-x-y << endl;
            return 0;
        }
    }
    

    cout << -1 << endl;

	return 0;
}

