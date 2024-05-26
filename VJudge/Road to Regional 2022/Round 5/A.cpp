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
	
    string a, b; cin>>a>>b;

    int n; cin>>n;

    cout << a << " " << b << endl;
    while(n--){
        string s, t; cin>>s>>t;
        if(s == a) {
            a = t;
        } else {
            b = t;
        }

        cout << a << " " << b << endl;
    }

	return 0;
}

