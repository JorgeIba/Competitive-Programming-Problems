#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const lli MAXA = 1e18;

int main () {
	//fastIO();

    int n; cin>>n;

    vector<lli> primes(n);
    for(auto &p: primes) cin>>p;

    int k; cin>>k;

    int half = n / 2;
    vector<lli> nums_1, nums_2;
    auto f = [&](const auto &f, int idx, int limit, lli num) {
        if(idx == limit) {
            if(limit == half)
                nums_1.push_back(num);
            else 
                nums_2.push_back(num);

            return;
        }

        int log_a = 0;
        auto p = primes[idx];
        lli aux = num;
        while(aux <= MAXA/p) {
            aux *= p;
            log_a++;
        }

        for(int i = 0; i <= log_a; i++){
            f(f, idx+1, limit, num);
            num *= p;
        }
    };


    f(f, 0, half, 1);
    f(f, half, n, 1);

    sort(all(nums_1));
    sort(all(nums_2));

    int m_1 = SZ(nums_1);
    int m_2 = SZ(nums_2);

    auto check = [&](lli mid) -> lli {
        #define i128 __int128

        lli lower = 0;
        for(int l = 0, r = m_2-1; l < m_1; l++) {
            while(r >= 0 && (i128) nums_1[l] * nums_2[r] >= mid) {
                r--;
            }
            lower += (r + 1);
        }
        return lower;
    };


    lli l = 1, r = 1e18, ans = r;
    while(l <= r){
        lli mid = (l+r) / 2;
        auto cnt = check(mid);
        if(cnt == k-1){
            ans = mid;
            l = mid+1;
        } if(cnt > k-1){
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << endl;

	return 0;
}

