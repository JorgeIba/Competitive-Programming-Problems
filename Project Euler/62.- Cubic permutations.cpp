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

    const lli maxN = 1e5;

    map<string, int> fr;

    for(lli i = 1; i <= maxN; i++) {
        lli cube = i*i*i;
        string s_cube = to_string(cube);
        sort(all(s_cube));


        fr[s_cube]++;
    }

    set<string> cubes;
    for(auto x: fr) {
        if(x.second == 5) {
            cubes.insert(x.first);
        }
    }

    lli ans = -1;
    for(lli i = 1; i <= maxN; i++) {
        lli cube = i*i*i;
        string s_cube = to_string(cube);
        sort(all(s_cube));


        if(cubes.count(s_cube)) {
            ans = i;
            break;
        }
    }

    cout << ans << "^3 = " << ans*ans*ans << endl;

	return 0;
}

