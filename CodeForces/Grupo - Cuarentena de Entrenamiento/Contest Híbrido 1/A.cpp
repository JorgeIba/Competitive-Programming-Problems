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
    lli n, s; cin>>n>>s;

    s--;

    vector< vector<int> > stations(2, vector<int>(n));

    for(int i = 0; i < n; i++) 
        cin>>stations[0][i];

    for(int i = 0; i < n; i++) 
        cin>>stations[1][i];

    if(stations[0][0] != 1) {
        cout << "NO" << endl;
        return 0;
    }

    // 1 al inicio

    if(stations[0][s] == 0 && stations[1][s] == 0) {
        cout << "NO" << endl;
        return 0;
    }


    if(stations[0][s] == 1) {
        cout << "YES" << endl;
        return 0;
    }


    for(int i = s; i < n; i++) {
        if(stations[0][i] == 1 && stations[1][i] == 1) {
            cout << "YES" << endl;
            return 0;
        }
    }


    cout << "NO" << endl;




	return 0;
}

