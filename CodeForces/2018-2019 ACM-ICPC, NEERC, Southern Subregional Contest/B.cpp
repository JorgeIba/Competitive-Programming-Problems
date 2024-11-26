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

const int INF = 2e9 + 100;

int main () {
	fastIO();

    int n;
    lli h; 
    cin>>n>>h;

    vector< pair<int,int> > ranges(n);
    for(auto &[l, r]: ranges)
        cin>>l>>r;

    ranges.push_back({INF, INF});

    vector<lli> prefix(n);
    for(int i = 0; i < n; i++) {
        auto [l_1, r_1] = ranges[i];
        auto [l_2, r_2] = ranges[i+1];
        lli sz = (l_2-1) - (r_1) + 1;
        if(i)
            prefix[i] = prefix[i-1];

        prefix[i] += sz;
    }

    lli max_ans = 0;
    for(int i = 0; i < n; i++) {
        auto [x, _] = ranges[i];

        lli prev = (i ? prefix[i-1] : 0);

        int l = i, r = n, ans = l;
        while(l <= r) {
            int mid = l + (r-l) / 2;
            if(prefix[mid] - prev >= h) {
                r = mid-1;
                ans = mid;
            } else {
                l = mid+1;
            }
        }

        lli taken = ans ? prefix[ans-1] - prev : 0;
        lli moves = h - taken;

        lli finish = ranges[ans].second-1 + moves;
        max_ans = max(max_ans, finish - x + 1);
    }
    cout << max_ans << endl;




	return 0;
}

