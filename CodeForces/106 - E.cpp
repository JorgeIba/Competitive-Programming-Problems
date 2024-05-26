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


ld sq(ld x, ld y, ld z) {
    return sqrtl(x*x + y*y + z*z);
}

tuple<ld,ld,ld> gradientDescent(ld x, ld y, ld z) {
    ld rate = 1, coef = 0.999;
    for(lli T = 1; T <= 500000; T++, rate *= coef) {
        ld gradient_x = 0, gradient_y = 0, gradient_z = 0, max_cost = 0;
        for(int i = 0; i < SZ(points); i++) {
            auto [x_i, y_i, z_i] = points[i];
            ld dist = sq(x_i - x, y_i - y, z_i - z);

            if(dist > max_cost) {
                max_cost = dist;
                gradient_x = (x_i - x)*(-1);
                gradient_y = (y_i - y)*(-1);
                gradient_z = (z_i - z)*(-1);
            }
        }

        x = x - gradient_x * rate;
        y = y - gradient_y * rate;
        z = z - gradient_z * rate;
    }

    return {x, y, z};
}


int main () {
	//fastIO();

    lli n; cin>>n;

    
    points.resize(n);
    for(auto &x: points) cin>>x[0]>>x[1]>>x[2];

    ld mean_x = 0, mean_y = 0, mean_z = 0;
    for(auto p: points) {
        mean_x += p[0];
        mean_y += p[1];
        mean_z += p[2];
    }

    mean_x /= n, mean_y /= n, mean_z /= n;

    auto [ans_x, ans_y, ans_z] = gradientDescent(mean_x, mean_y, mean_z);

    auto getCost = [&](ld x, ld y, ld z) {
        ld max_i = 0;
        for(auto p: points) max_i = max(max_i, sq(p[0]-x, p[1]-y, p[2]-z));
        return max_i;
    };

    cerr << getCost(ans_x, ans_y, ans_z) << endl;

    cout << fixed << setprecision(10) << ans_x << " " << ans_y << " " << ans_z << endl;

	return 0;
}

