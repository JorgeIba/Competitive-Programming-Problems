#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


int main () {
	//fastIO();
	
    int x; cin>>x;
    cout << min(15, 3000 / x + (3000 % x != 0)) << endl;

	return 0;
}

