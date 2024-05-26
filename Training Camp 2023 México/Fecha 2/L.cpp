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

    lli n; cin>>n;
    if(n == 1) {
        cout << 3 << endl;
        return 0;
    }

    auto get_how_many = [&](lli x) {
        lli odds = (x-1) / 2 ;
        lli multiples_4 = (x / 4) - 1;
        // cout << x << ": " << odds << " - " << multiples_4 << endl;
        return odds + multiples_4;
    };



    lli l = 3, r = 1e18;
    while(l <= r) {
        lli mid = (l+r) / 2;
        lli how_many = get_how_many(mid);
        if(how_many < n) {
            l = mid+1;
        } else if(how_many == n) {
            for(int ans = mid - 5; ans <= mid+5; ans++){
                if(ans > 0 && (ans % 2 == 1 || (ans % 4 == 0 && ans != 4))){
                    if(get_how_many(ans) == n) {
                        cout << ans << endl;
                        return 0;
                    }
                }
            }
        }  else {
            r = mid-1;
        }
    }


	return 0;
}

