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
typedef __int128 i128;

const int MOD = 1e9 + 7;

lli powerMod(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

void main_() {
    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> pot(n);
    forn(i, n) {
        lli &x = nums[i];
        while(x % 2 == 0) {
            pot[i]++;
            x /= 2;
        }
    }

    auto compare = [&](lli a_1, lli b_1, lli a_2, lli b_2) {
        lli r = min(b_1, b_2);
        b_1 -= r; 
        b_2 -= r;

        if(b_1 > 31) return false;
        if(b_2 > 31) return true;

        return a_1 * (1LL << b_1) < a_2 * (1LL << b_2);
    };

    stack< pair<lli,lli> > st;
    lli sum = 0;
    for(int i = 0; i < n; i++) {
        lli x = nums[i];
        lli b = pot[i];

        while(!st.empty() && compare(st.top().first, st.top().second, x, b + st.top().second)) {
            sum -= st.top().first * powerMod(2, st.top().second) % MOD;
            if(sum < 0) sum += MOD;

            (sum += st.top().first) %= MOD;

            b += st.top().second;
            st.pop();
        }


        (sum += x * powerMod(2, b) % MOD) %= MOD;
        st.push({x, b});

        cout << sum << " ";
    }
    cout << endl;

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