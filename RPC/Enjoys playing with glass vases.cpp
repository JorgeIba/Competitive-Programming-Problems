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


lli la, lb;
set<pair<lli,lli>> ans;

void f(lli ca, lli cb, lli it)
{
    if(it == 10000) return;
    if(ans.count({ca, cb}))  return;

    ans.insert({ca, cb});

    //action 1
    if(ca > 0)
    {
        f(0, cb, it+1);
    }
    if(cb > 0)
    {
        f(ca, 0, it+1);
    }


    //action2
    f(la, cb, it+1);
    f(ca, lb, it+1);


    //action3
    lli poner_a_b = min(lb-cb, ca);
    f(ca - poner_a_b, cb+poner_a_b, it+1);

    lli poner_a_a = min(la-ca, cb);
    f(ca  + poner_a_a, cb - poner_a_a, it+1);
}



int main () {
	//fastIO();
    cin>>la>>lb;
    
    /*
    f(0, 0, 0);

    // for(auto x: ans) cout << x.first << " " << x.second << endl;;
    cout << SZ(ans) << endl;
    */
    
    lli ca = la, cb = lb; //cin>>ca>>cb;

    if(ca < cb) swap(ca, cb);

    lli g = __gcd(ca, cb);

    lli m = ca/g, n = cb/g;

    lli ans = 2*(m+1-2) + 2*(n+1);

    cout << ans << endl;
    

	return 0;
}

