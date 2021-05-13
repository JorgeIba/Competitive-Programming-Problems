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

lli n, m;
string s, t;
int main () {
	fastIO();
    cin>>s>>t;
    n = s.length();
    if(n<100)
    {
        if(s == t)
        {
            cout << "Long lost brothers D:\n";
        }
        else
        {
            cout << "Not brothers :(\n";
        }
        return 0;
    }
    

    //vector< vector<int> > mem(n+1, vector<int>(2005));
    vector<lli> dpVieja(2005), dpNueva(2005);
    for(int i = 0; i<n; i++)
    {
        for(int distancia = -1000; distancia <= 1000; distancia++)
        {
            lli j = i + distancia;
            lli distAbs = distancia+1000;
            if(j >= n || j < 0) continue;
            if(s[i] == t[j])
            {
                dpNueva[distAbs] = dpVieja[distAbs] + 1;
            }
            if(distAbs - 1 >= 0)
                dpNueva[distAbs-1] = max(dpVieja[distAbs], (distAbs-1<0? 0: dpNueva[distAbs-1]));
            dpVieja[distAbs+1] = max(dpVieja[distAbs], dpVieja[distAbs+1]);
        }
        swap(dpVieja, dpNueva);
    }

    lli ans = 0;
    for(int j = 0; j<2005; j++)
    {
        ans = max(ans, dpVieja[j]);
    }
    assert(ans >= 0);
    cerr << ans << endl;

    if(100LL*ans >= 99LL*n)
    {
        cout << "Long lost brothers D:\n";
    }
    else
    {
        cout << "Not brothers :(\n";
    }
    

	return 0;
}