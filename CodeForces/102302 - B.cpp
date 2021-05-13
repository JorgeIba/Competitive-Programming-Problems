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
    lli a, b; cin>>a>>b;

    vector<lli> ans;
    for(lli i = 1; i*i <=a; i++)
    {
        if(a % i == 0)
        {
            if(i % b == 0) ans.push_back(i);
            if( (i*i != a) && (a/i % b == 0)) ans.push_back(a/i);
        }
    }

    sort(all(ans));
    for(auto x: ans) cout << x << " ";

	return 0;
}