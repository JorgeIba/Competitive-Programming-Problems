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
	
    lli n, a, b; cin>>n>>a>>b;
    a--, b--;

    string s; cin>>s;

    
    if(s[a] == s[b]) cout << 0 << endl;
    else {
        
        char looking = (s[a] == '1' ? '0' : '1');

        vector<pair<lli,lli>> last(n);
        lli last_1 = 1e9, last_2 = 1e9;
        for(int i = n-1; i >= 0; i--) {
            last[i].second = last_2;
            if(s[i] == looking) last_2 = i;
        }

        for(int i = 0; i < n; i++) {
            last[i].first = last_1;
            if(s[i] == looking) last_1 = i;
        }

        lli ans = n+1;
        for(int i = 0; i < n; i++) {
            if(s[a] == s[i])
                ans = min({ans,  abs(i - last[i].first), abs(i - last[i].second)   });
        }
        
        cout << ans << endl;
    }


	return 0;
}

