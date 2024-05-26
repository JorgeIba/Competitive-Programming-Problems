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


#define point pair<int,int>
#define x first
#define y second


const int MAXN = 1e5 + 100;
lli dp[MAXN][3][3];


int main () {
	fastIO();
	
    int n; cin>>n;

    vector< point > points(n);
    for(auto &p: points) cin>>p.x>>p.y;

    if(n == 1) {
        cout << 0 << endl;
        return 0;
    }


    map< int, vector<lli> > prov;
    for(auto [x, y]: points) {
        prov[x].push_back(y);
    }


    map< int, vector<lli> > good;
    for(auto [x, ys]: prov) {
        auto y_min = *min_element(all(ys));
        auto y_max = *max_element(all(ys));

        good[x].push_back(y_min);
        good[x].push_back(y_max);
    }

    vector< pair<int, array<lli,2> > > good_p;
    for(auto [x, ys]: good) {
        good_p.push_back({x,  {ys[0], ys[1]}  });
    }


    auto get_dist = [](lli x_1, lli y_1, lli x_2, lli y_2) -> lli{
        return abs(x_2 - x_1) + abs(y_2 - y_1);
    };


    memset(dp, -1, sizeof(dp));


    auto f = [&](auto const &f, int idx, int pos, bool completed) -> lli {
        if(idx == SZ(good_p)-1 && completed) return 0; 

        lli &ans = dp[idx][pos][completed];
        if(ans != -1) return ans;


        if(completed) {
            int x = good_p[idx].first;
            int y = good_p[idx].second[pos];
            int next_x = good_p[idx+1].first;
            int next_y0 = good_p[idx+1].second[0];
            int next_y1 = good_p[idx+1].second[1];


            lli total_0 = get_dist(x, y, next_x, next_y0);
            lli total_1 = get_dist(x, y, next_x, next_y1);
            

            return ans = min( f(f, idx+1, 0, false) + total_0,   f(f, idx+1, 1, false) + total_1 );


        } else {
            lli total = abs(good_p[idx].second[0] - good_p[idx].second[1]);
            if(pos == 1) {
                return ans = f(f, idx, 0, true) + total;
            } else {
                return ans = f(f, idx, 1, true) + total;
            }
        }
    };


    cout << min(f(f, 0, 0, false), f(f, 0, 1, false)) << endl;


	return 0;
}

