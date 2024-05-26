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

vector< array<lli, 3> > points;


ld getCost(ld x, ld y) {
    ld total_cost = 0;
    for(auto p: points) total_cost = max(total_cost, p[2] * sqrt((p[0] - x)*(p[0] - x) +  (p[1] - y)*(p[1] - y)) );
    return total_cost;
}


ld solveY(ld x) {
    ld l = -1e4, r = 1e4;

    for(int i = 0; i < 100; i++) {
        ld yl = l + (r-l)/3;
        ld yr = r - (r-l)/3;

        if(getCost(x, yl) < getCost(x, yr)) {
            r = yr;
        } else {
            l = yl;
        }
    }

    return l;
}


pair<ld,ld> solveXY() {
    ld l = -1e4, r = 1e4;
    for(int i = 0; i < 100; i++) {
        ld xl = l + (r-l)/3;
        ld xr = r - (r-l)/3;

        if( getCost(xl, solveY(xl)) < getCost(xr, solveY(xr)) ) {
            r = xr;
        } else {
            l = xl;
        }
    }

    return {l, solveY(l)};
}


int main () {
	//fastIO();

    lli n; cin>>n;

    points.resize(n);
    for(auto &p: points) cin>>p[0]>>p[1]>>p[2];


    auto [x, y] = solveXY();

    cout << fixed << setprecision(10) << getCost(x, y) << endl;

	return 0;
}

