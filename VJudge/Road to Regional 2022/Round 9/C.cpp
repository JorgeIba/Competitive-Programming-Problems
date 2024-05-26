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
    int a, b; cin>>a>>b;

    if(a-b == 0){
        cout << "infinity" << endl;
        return 0;
    }

    lli n = a-b;
    vector<lli> divs;
    for(lli i = 1; i * i <= n; i++){
        if(n % i == 0){
            divs.push_back(i);
            if(i*i != n) divs.push_back(n / i);
        }
    }

    lli ans = 0;
    for(auto d: divs)
        ans += (d > b);

    cout << ans << endl;

	return 0;
}

