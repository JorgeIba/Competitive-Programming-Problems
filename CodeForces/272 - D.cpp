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
    int n; cin>>n;
    vector<lli> a(n), b(n);

    map<lli, lli> freq;

    for(int i = 0; i<n; i++)
    {
        cin>>a[i]; freq[a[i]]++;
    }
    lli repeated = 0;
    for(int i = 0; i<n; i++)
    {
        cin>>b[i]; freq[b[i]]++;
        if(a[i] == b[i]) repeated++;
    }
    lli m; cin>>m;

    lli ans = 1;
    for(auto p: freq)
    {
        for(lli i = 1; i<=p.second; i++)
        {
            ans = (ans*i);
            if(repeated > 0 && ~ans&1)
            {
                ans>>=1; repeated--;
            }
            ans %= m;
        }
    }
    cout << ans << endl;
    
	return 0;
}