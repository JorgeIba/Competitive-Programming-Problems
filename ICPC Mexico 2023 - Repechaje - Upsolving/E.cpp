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

const int MAXF = 1e6 + 10;

int main () {
    fastIO();

    auto get_sum = [&](int n) {
        int sum = 0;
        while(n) {
            sum += (n % 10);
            n /= 10;
        }
        return sum;
    };

    int n, k; cin>>n>>k;
    vector<int> cnt(MAXF);

    forn(i, n) {
        int x; cin>>x;
        cnt[x]++;
    }

    int ans = 0;
    for(int i = MAXF-1; i >= 0; i--) {
        if(cnt[i] == 0) continue;

        auto biggest = i;
        int cnt_biggest = cnt[biggest];
        int next_move = biggest - get_sum(biggest);

        // Move all flowers with pollen = biggest
        // As all of them will have pollen = biggest - get_sum(biggest)
        cnt[biggest] = 0;
        cnt[next_move] += cnt_biggest;

        k -= cnt_biggest;
        if(k <= 0) {
            ans = i;
            break;
        }
    }
    cout << get_sum(ans) << endl;


	return 0;
}

