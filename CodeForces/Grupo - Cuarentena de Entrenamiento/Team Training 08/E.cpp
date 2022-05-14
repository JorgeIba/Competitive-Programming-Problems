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
 
void solve()
{
    lli k, l; cin>>k>>l;
    if(l>=2000)
    {
        cout << -1 << endl;
        return;
    }

    vector<lli> ans(1999);
    ans[0] = -1;
    lli falta = k + 1999, maxi = 1e6;
    for(int i = 1; i<1999; i++)
    {
        if(falta >= 0)
        {
            lli aux = min(maxi, falta);
            ans[i] = aux;
            falta -= aux;
        }    
    }
    cout << SZ(ans) << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;
}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve() ;

	return 0;
}