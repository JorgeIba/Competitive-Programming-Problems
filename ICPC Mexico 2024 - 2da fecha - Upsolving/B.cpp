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


struct point{
    lli x, y;
    point(): x(0), y(0) {}
    point(lli x, lli y): x(x), y(y) {}

    lli cross(const point &p) const {
        return x * p.y - y * p.x;
    }

    bool operator<(const point &p) const {
        return (x < p.x) || (x == p.x && y < p.y);
    }

    point operator-(const point &p) const {
        return {x - p.x, y - p.y};
    }
};


#define fraction pair<lli,lli>
#define num first
#define den second

bool operator<(const fraction &f, const fraction &g) {
    return f.num * g.den < g.num * f.den;
}

bool operator==(const fraction &f, const fraction &g) {
    return f.num * g.den == g.num * f.den;
}

fraction operator*(const fraction &f, const fraction &g) {
    return {f.num * g.num, f.den * g.den};
}

fraction operator+(const fraction &f, const fraction &g) {
    return {f.num * g.den + g.num * f.den, f.den * g.den};
}

fraction operator-(const fraction &f, const fraction &g) {
    return {f.num * g.den - g.num * f.den, f.den * g.den};
}


const int MAXN = 5000 + 5;
const int INF = 1e9;
array<fraction, 2> ys[MAXN];
bool present[MAXN][MAXN];
int present_N[MAXN][MAXN];

fraction eval(lli x, fraction m, fraction c) {
    fraction fx; fx.num = x; fx.den = 1;
    return fx * m + c;
}

vector<point> convexHull(vector<point> P){
    sort(all(P));
	vector<point> L, U;
	for(int i = 0; i < SZ(P); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]) <= 0){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]) <= 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}


int main () {
	// fastIO();

    forn(i, MAXN) {
        ys[i][0] = {-INF, 1};
        ys[i][1] = {-INF, 1};
    }

    int n, m; cin>>n>>m;
    vector< point > points(n);

    for(auto &p: points) {
        cin>>p.x>>p.y;
    }

    if(m >= MAXN) {
        cout << 0 << endl;
        return 0;
    }

    points = convexHull(points);

    // for(auto p: points) {
    //     cout << "(" << p.x << ", " << p.y << "), ";
    // }
    // cout << endl;

    auto add = [&](int i, fraction f) {
        if(f == ys[i][0] || f == ys[i][1]) return;

        if(ys[i][0] < f) {
            ys[i][1] = ys[i][0];
            ys[i][0] = f;
        } else if(ys[i][1] < f) {
            ys[i][1] = f;
        }
    };

    // y - y0 = m(x-x0)

    // y = mx + (y0 - mx0)
    // m = (y-y0) / (x-x0)

    n = SZ(points);
    for(int i = 0; i < n; i++) {
        point p = points[i], q = points[(i+1) % n];
        if(p.x == q.x) {
            if(p.y > q.y)
                swap(p, q);

            for(int yy = p.y; yy <= q.y; yy++) {
                present[p.x][yy] = 1;
            }

            continue;
        } else {
            if(p.x > q.x)
                swap(p, q);
        }


        auto [x0, y0] = p;
        auto [x1, y1] = q;
        fraction m; m.num = y1 - y0; m.den = x1 - x0;
        fraction c; c.num = y0; c.den = 1;
        fraction fx0; fx0.num = x0; fx0.den = 1;

        c = c - m * fx0;
    
        assert(x0 < x1);
        for(int xx = x0; xx <= x1; xx++) {
            fraction ev = eval(xx, m, c);
            add(xx, ev);
        }
    }


    for(int x = 0; x < MAXN; x++) {
        if(ys[x][0].num == -INF) continue;
        if(ys[x][1].num == -INF) 
            ys[x][1] = ys[x][0];

        auto fr_up = ys[x][0];
        lli y_upper = fr_up.num / fr_up.den;

        auto fr_low = ys[x][1];
        lli y_down = (fr_low.num + (fr_low.den - 1)) / fr_low.den;

        for(int y = y_down; y <= y_upper; y++) {
            present[x][y] = 1;
        }
    }


    for(int x = 0; x < MAXN; x++) {
        for(int y = 0; y < MAXN; y++) {
            if(present[x][y]) {
                // cout << "(" << x << ", " << y << "), ";
                present_N[x % (m-1)][y % (m-1)]++;
            }
        }
    }

    int ans = 0;
    for(int x = 0; x < m; x++) {
        for(int y = 0; y < m; y++) {
            if(present_N[x][y] > 1) {
                ans += present_N[x][y];
            }
        }
    }
    cout << ans << endl;


	return 0;
}

