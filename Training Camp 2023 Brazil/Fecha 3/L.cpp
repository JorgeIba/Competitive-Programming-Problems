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
	
    int n; cin>>n;

    auto lcm = [](lli x, lli y) {
        return (x / __gcd(x, y)) * y;
    };


    lli ans = 1e9;
    for(int i = 0; i < n; i++){
        lli year, x, y; cin>>year>>x>>y;
        ans = min(ans, year + lcm(x, y));
    }

    cout << ans << endl;

	return 0;
}

