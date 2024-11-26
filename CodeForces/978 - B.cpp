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
    int n, x; cin>>n>>x;
    vector<int> nums(n);
    for(auto &x: nums) {
        cin>>x;
    }

    auto mx = *max_element(all(nums));
    auto sum = accumulate(all(nums), 0LL);

    cout << max(1LL * mx, (sum + x - 1) / x) << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

