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


vector<int> get_L(const vector<int> &nums) {
    int n = SZ(nums);
    vector<int> L(n);
    stack< pair<int,int> > s;
    for(int i = 1; i < n; i++) {
        int x = nums[i];
        while(!s.empty() && s.top().second < x) {
            s.pop();
        }

        if(s.empty()) {
            L[i] = 0;
        } else {
            L[i] = s.top().first;
        }

        s.push({i, x});
    }
    return L;
}

vector<int> get_R(const vector<int> &nums) {
    int n = SZ(nums);
    vector<int> R(n);
    stack< pair<int,int> > s;
    for(int i = n-1; i >= 1; i--) {
        int x = nums[i];
        while(!s.empty() && s.top().second <= x) {
            s.pop();
        }

        if(s.empty()) {
            R[i] = n;
        } else {
            R[i] = s.top().first;
        }

        s.push({i, x});
    }
    return R;
}

const int MAXN = 5e5 + 100;
const int MOD = 1e9 + 7;

vector<int> divs[MAXN + 10];
int mu[MAXN + 10];
int dirichlet[MAXN + 10];

void prec(int n) {
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            divs[j].push_back(i);
        }
    }

    fill(mu, mu + n + 1, -1);
    mu[0] = 0; mu[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(mu[i]) {
            for(int j = 2*i; j <= n; j += i) {
                mu[j] -= mu[i];
            }
        }

        if(mu[i] < 0) mu[i] += MOD;
    }

    for(int i = 1; i <= n; i++) {
        int sum = 0;
        for(auto d: divs[i]) {
            sum += 1LL * d * d % MOD * mu[i / d] % MOD;
            if(sum >= MOD) sum -= MOD;
        }
        dirichlet[i] = sum;
    }
}


int main () {
	fastIO();

    prec(MAXN);

    int n; cin>>n;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];

    auto L = get_L(nums);
    auto R = get_R(nums);

    auto f = [&](int x, int n) {
        int ans = 0;
        for(auto y: divs[x]) {
            (ans += 1LL * (n / y) * dirichlet[y] % MOD) %= MOD;
        }
        return ans;
    };

    auto get_gcd_ranges = [&](int lower, int idx, int upper) {
        int ans = 0;
        for(int x = lower; x <= idx; x++) {
            int contribution = f(x, upper) - f(x, idx-1);
            if(contribution < 0) contribution += MOD;

            ans += contribution;
            if(ans >= MOD) ans -= MOD;
        }
        return ans;
    };

    auto get_ans_per_idx = [&](int idx) {
        int lower = L[idx] + 1;
        int upper = R[idx] - 1;
        return 1LL * nums[idx] * get_gcd_ranges(lower, idx, upper) % MOD;
    };


    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += get_ans_per_idx(i);
        if(ans >= MOD) ans -= MOD;
    }
    cout << ans << endl;

	return 0;
}

