#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

void main_() {
    vector<vector<lli>> nums(3);
    forn(i, 3) {
        int n; cin>>n;
        nums[i].resize(n);
        for(auto &x: nums[i]) cin>>x;
    }

    set<lli> check;
    for(auto x: nums[0]) {
        for(auto y: nums[1]) {
            for(auto z: nums[2]) {
                check.insert(x + y + z);
            }
        }
    }

    int x; cin>>x;
    forn(i, x){
        lli y; cin>>y;
        cout << (check.count(y) ? "Yes" : "No") << endl;
    }

}

int main () {
	// fastIO();

	int t = 1;
	// cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

