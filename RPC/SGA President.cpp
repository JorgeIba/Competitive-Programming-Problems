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
    vector< map<string,lli> > fr(28);
    int n; cin>>n;
    for(int i = 0; i<n; i++)
    {
        string s; cin>>s;
        char first = s[0];
        fr[first - 'A'][s]++;
    }

    lli ans = 0;
    for(auto c: fr){
        lli suma = 0;
        for(auto x: c)
        {
            suma += x.second;
            ans -= ((x.second)*(x.second-1)) / 2;
        }
        ans += (suma*(suma-1))/2;
    }
    
    cout << 2*ans << endl;

	return 0;
}