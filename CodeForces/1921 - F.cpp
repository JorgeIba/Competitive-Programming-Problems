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

void main_(){

    int n, q; cin>>n>>q;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    int threshold = sqrt(n);
    vector< vector<lli> > prefix_sum1(threshold, vector<lli>(n));
    vector< vector<lli> > prefix_sum2(threshold, vector<lli>(n));

    for(int d = 1; d < threshold; d++) {
        for(int start = 0; start < d; start++) {
            for(int i = start, j = 1; i < n; j++, i += d) {
                if(i-d >= 0)
                    prefix_sum1[d][i] = prefix_sum1[d][i-d];
                prefix_sum1[d][i] += nums[i];


                if(i-d >= 0)
                    prefix_sum2[d][i] = prefix_sum2[d][i-d];
                prefix_sum2[d][i] += j * nums[i];
            }
        }
    }

    auto get_sum = [&](int s, int d, int k) {
        lli sum2 = prefix_sum2[d][s + d*(k-1)] - (s-d >= 0 ? prefix_sum2[d][s - 1*d] : 0);
        lli sum1 = prefix_sum1[d][s + d*(k-1)] - (s-d >= 0 ? prefix_sum1[d][s - 1*d] : 0);

        return sum2 - (s / d) * sum1;
    };



    while(q--) {
        int s, d, k; cin>>s>>d>>k;
        s--;

        if(d < threshold) {
            cout << get_sum(s, d, k) << " ";
        } else {
            lli ans = 0;
            for(int i = s, j = 1; j <= k; j++, i += d) {
                ans += j*nums[i];
            }

            cout << ans << " ";
        }
    }


}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
        cout << endl;
	}

	return 0;
}

