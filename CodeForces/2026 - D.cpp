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


const lli INF = 1e18;

void main_() {
    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
        cin>>x;

    vector< array<lli, 2> > ranges(n);
    for(lli i = 0, l = 0, r = n-1; i < n; i++, l = l + r+1, r--) {
        ranges[i] = {l, l + r};
    }

    auto get_pref = [&]() {
        auto pref = nums;
        partial_sum(all(pref), pref.begin());
        auto pref2 = pref;
        partial_sum(all(pref2), pref2.begin());

        return [pref, pref2](lli l, lli r) {
            return pref2[r] - (l ? pref2[l-1] : 0) - (l ? pref[l-1] : 0) * (r - l + 1);
        };
    }();

    auto get_pref_suf = [&]() {
        vector<lli> pref(n);
        forn(i, n) {
            if(i)
                pref[i] = pref[i-1];
            pref[i] += get_pref(i, n-1);
        }

        return [pref](lli idx) {
            return (idx >= 0 ? pref[idx] : 0);
        };
    }();

    auto get_sum = [&](lli idx) {
        if(idx < 0) return 0LL;

        auto itr = upper_bound(all(ranges), array<lli,2>{idx, INF}) - begin(ranges) - 1;
        auto [l, r] = ranges[itr];

        lli move_from_there = itr + (idx - l);
        lli sum_after = get_pref(itr, move_from_there);
        lli sum_bef = get_pref_suf(itr-1);

        return sum_bef + sum_after;
    };

    int q; cin>>q;
    forn(_, q) {
        lli l, r; cin>>l>>r;
        l--, r--;

        cout << get_sum(r) - get_sum(l-1) << endl;
    }
}

int main () {
	fastIO();

	int t = 1;
	// cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

