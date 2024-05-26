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
	int n; cin>>n;

    vector<int> A(n);
    for(auto &x: A) cin>>x;

    int P = 0;
    vector<int> vault(450);
    for(auto x: A) {
        vault[0]++;
        rotate(vault.begin(), vault.begin() + SZ(vault) - x, vault.end());
    }

    for(int i = 4; i < SZ(vault); i++) P += vault[i];

    cout << P << endl;
	return 0;
}

