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

    lli A, B, C, D; cin>>A>>B>>C>>D;

    lli g = __gcd(A, B);

    if(D % g != 0) {
        cout << "No solution." << endl;
        return 0;
    }

    lli ans_x = 0, ans_y = 0;
    for(lli x = 0; x <= 1000000; x++) {
        lli num = (A*x - D);

        if(num < 0 || num % B != 0) continue;

        lli y = num / B;

        // if(x == 3) cout << num << " " << y << endl;

        assert(A*x-B*y == D);

        if(A*x >= C + D) {
            ans_x = x, ans_y = y;
            break;
        }
    }

    // assert(ans_x > 0 && ans_y > 0);

    string ans_trucks, ans_boats;
    if(ans_x == 1) {
        ans_trucks = to_string(ans_x) + " truck";
    } else {
        ans_trucks = to_string(ans_x) + " trucks";
    }

    if(ans_y == 1) {
        ans_boats = to_string(ans_y) + " boat";
    } else {
        ans_boats = to_string(ans_y) + " boats";
    }

    cout << "We need " << ans_trucks << " and " << ans_boats << ".\n";



	return 0;
}

