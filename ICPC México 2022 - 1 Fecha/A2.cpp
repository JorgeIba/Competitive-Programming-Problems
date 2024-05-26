#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

vector< array<lli,3> > points;

ld sq(ld x, ld y) {
    return sqrtl(x*x + y*y);
}


pair<ld, ld> gradientDescent(ld x, ld y) {
    ld rate = 0.95, coef = 0.95;
    for(lli T = 1; T <= 1000; T++, rate *= coef) {
        ld gradient_x = 0, gradient_y = 0, max_cost = 0;
        for(int i = 0; i < SZ(points); i++) {
            auto [x_i, y_i, c_i] = points[i];
            ld dist = sq(x_i - x, y_i - y);

            if(dist*c_i > max_cost) {
                max_cost = dist*c_i;
                gradient_x = (x_i - x)*(-1)*c_i * (1.0 / dist);
                gradient_y = (y_i - y)*(-1)*c_i * (1.0 / dist);
            }
        }

        x = x - gradient_x * rate;
        y = y - gradient_y * rate;
    }

    return {x, y};
}


int main () {
	//fastIO();

    lli n; cin>>n;

    
    points.resize(n);
    for(auto &x: points) cin>>x[0]>>x[1]>>x[2];


    auto getCost = [&](ld x, ld y) {
        ld max_i = 0;
        for(auto p: points) max_i = max(max_i, sq(p[0]-x, p[1]-y) * p[2]);
        return max_i;
    };


    ld ans = 1e9;
    for(int k = 0; k < n; k++) {
        auto [x, y] = gradientDescent(points[k][0], points[k][1]);

        ans = min(ans, getCost(x,y));
    }

    cout << fixed << setprecision(10) << ans << endl;

	return 0;
}

