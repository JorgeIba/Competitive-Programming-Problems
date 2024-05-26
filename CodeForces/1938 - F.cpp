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
    int n; cin>>n;
    vector<int> nums_or(n);
    forn(i, n) cin>>nums_or[i];

    int aux_n = n;
    vector<int> primes;
    for(lli i = 2; i * i <= n; i++) {
        if(aux_n % i == 0) {
            primes.push_back(i);
            while(aux_n % i == 0) aux_n/= i;
        }
    }
    if(aux_n > 1) primes.push_back(aux_n);

    auto cmp = [&](const pair<lli,lli> &a, const pair<lli,lli> &b) {
        auto [x_max, x_min] = a;
        auto [y_max, y_min] = b;
        return x_max * y_min < y_max * x_min;
    };

    auto check = [&](int k) {
        auto nums = nums_or;
        vector<lli> groups(k);
        for(int i = 0; i < n; i++) {
            groups[i % k] += nums[i];
        }
        multiset<int> xs(all(groups));

        pair<int,int> ans = {*xs.rbegin(), *xs.begin()};

        for(int i = 0; i < n-1; i++) {
            int last = i % k, nextt = (i+1) % k;

            xs.extract(groups[last]);
            xs.extract(groups[nextt]);

            groups[last] -= nums[i];
            groups[nextt] -= nums[i+1];

            groups[last] += nums[i+1];
            groups[nextt] += nums[i];

            swap(nums[i], nums[i+1]);
            xs.insert(groups[last]);
            xs.insert(groups[nextt]);

            pair<int,int> ans_x = {*xs.rbegin(), *xs.begin()};

            if(!cmp(ans, ans_x)) swap(ans, ans_x);
        }

        return ans;
    };

    const int INF = 2e9;
    pair<int,int> ans = {INF, 1};
    for(auto d: primes) {
        if(d == 1) continue;
        if( cmp(check(d), ans) ) ans = check(d);
    }

    int g = gcd(ans.first, ans.second);
    ans.first /= g;
    ans.second /= g;

    cout << ans.first << " " << ans.second << endl;
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

