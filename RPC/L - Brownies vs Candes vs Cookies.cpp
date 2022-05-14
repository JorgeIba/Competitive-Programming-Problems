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

    lli t; cin>>t;

    for(int i = 1; i <= t; i++){
        lli n, s; cin>>n>>s;
        lli m; cin>>m;
        cout << "Practice #" << i << ": " << n << " " << s << endl;
        while(m--) {
            lli x; cin>>x;

            while(s <= x) s<<=1;
            s-=x;
            cout << x << " " << s << endl;
        }
    }


	return 0;
}

