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


bool eq(lli x, lli y) { return x == y; }
bool le(lli x, lli y) { return x < y; }

struct point{
	lli x, y;
    lli v=0;
	point(): x(0), y(0), v(0) {}
	point(lli x, lli y, lli v=0): x(x), y(y), v(v){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

void polarSort(vector<point> & P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}

struct Fenwick {
    int n;
    vector<long long> tree;

    Fenwick(int _n): n(_n), tree(n+1, 0) { }

    void update(int idx, long long val) {
        idx++;
        for (; idx <= n ; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    long long query(int idx) {
        idx++;
        long long ret = 0;
        for(; idx > 0 ; idx -= idx & -idx){
            ret += tree[idx];
        }
        return ret;
    }

    long long query(int x, int y) {
        return query(y) - query(x-1);
    }
};

map< pair<lli,lli>, int > idx_original;
map< pair<lli,lli>, int > idx_in_origin_cc; // counter clockwise
map< pair<lli,lli>, int > idx_in_origin_c; // clockwise
map< pair<lli,lli>, int > idx_in_fixed_c;
map< pair<lli,lli>, int > idx_in_fixed_cc;



vector<lli> get_Left(vector< point > points, point origin, point fixed, int n, int fix_x){
    Fenwick F_Left(n+2), F_Right(n+2);
    forn(i, n){
        auto p = points[i];
        if(p.x < 0) continue;

        int idx_p = idx_in_fixed_c[{p.x, p.y}];
        F_Right.update(idx_p, p.v);
    }

    vector<lli> ans(n);
    for(int i = n-1; i >= 0; i--){
        auto p = points[i];
        if(p.x >= 0) continue;

        int idx_p_origin = idx_in_origin_c[{p.x, p.y}];
        int idx_p_fixed  = idx_in_fixed_c[{p.x, p.y}];
        int idx_ans      = idx_original[{p.x, p.y}];

        ans[idx_ans] += F_Right.query(idx_p_fixed);
        ans[idx_ans] -= F_Left.query(idx_p_origin);

        F_Left.update(idx_p_origin, p.v);
        F_Right.update(idx_p_fixed, p.v);
    }

    return ans;
}

vector<lli> get_Mid(vector< point > points, point origin, point fixed, int n, int fix_x){
    Fenwick F_Left(n+2), F_Right(n+2);
    forn(i, n){
        auto p = points[i];
        if(p.x < 0) continue;
        if(p.x > fix_x) continue;
        
        int idx_p = idx_in_origin_cc[{p.x, p.y}];
        F_Left.update(idx_p, p.v);
    }

    vector<lli> ans(n);
    for(int i = n-1; i >= 0; i--){
        auto p = points[i];

        if(p.x < 0) continue;
        if(p.x > fix_x) continue;

        int idx_p_origin = idx_in_origin_cc[{p.x, p.y}];
        int idx_p_fixed  = idx_in_fixed_c[{p.x, p.y}];
        int idx_ans      = idx_original[{p.x, p.y}];

        
        F_Left.update(idx_p_origin, -p.v);

        ans[idx_ans] += F_Left.query (idx_p_origin);
        ans[idx_ans] += F_Right.query(idx_p_fixed);

        F_Right.update(idx_p_fixed, p.v);
    }

    return ans;
}

vector<lli> get_Right(vector< point > points, point origin, point fixed, int n, int fix_x){
    Fenwick F_Left(n+2), F_Right(n+2);
    forn(i, n){
        auto p = points[i];
        if(p.x > fix_x) continue;

        int idx_p = idx_in_origin_cc[{p.x, p.y}];
        F_Left.update(idx_p, p.v);
    }

    vector<lli> ans(n);
    for(int i = 0; i <= n-1; i++){
        auto p = points[i];
        if(p.x <= fix_x) continue;

        int idx_p_origin = idx_in_origin_cc[{p.x, p.y}];
        int idx_p_fixed  = idx_in_fixed_cc[{p.x, p.y}];
        int idx_ans      = idx_original[{p.x, p.y}];

        ans[idx_ans] += F_Left.query(idx_p_origin);
        ans[idx_ans] -= F_Right.query(idx_p_fixed);
    
        F_Left.update(idx_p_origin, p.v);
        F_Right.update(idx_p_fixed, p.v);
    }

    return ans;
}



int main () {
	fastIO();
	
    int n, x; cin>>n>>x;

    vector< point > points(n);
    for(auto &p: points){
        cin>>p.x>>p.y>>p.v;
    }

    forn(i, n){
        auto p = points[i];
        idx_original[{p.x, p.y}] = i;
    }
    sort(all(points));

    point origin(0,0);
    point fixed(x, 0);

    auto origin_cc = points;
    auto origin_c = points;
    auto fixed_cc = points;
    auto fixed_c = points;

    polarSort(origin_cc, origin, point(1, 0));

    polarSort(origin_c, origin, point(1, 0));
    reverse(all(origin_c));

    polarSort(fixed_cc, fixed, point(1, 0));

    polarSort(fixed_c, fixed, point(1, 0));
    reverse(all(fixed_c));
    
    forn(i, n){
        auto p = origin_cc[i];
        idx_in_origin_cc[{p.x, p.y}] = i;
    }
    forn(i, n){
        auto p = origin_c[i];
        idx_in_origin_c[{p.x, p.y}] = i;
    }


    forn(i, n){
        auto p = fixed_cc[i];
        idx_in_fixed_cc[{p.x, p.y}] = i;
    }
    forn(i, n){
        auto p = fixed_c[i];
        idx_in_fixed_c[{p.x, p.y}] = i;
    }


    auto Left = get_Left(points, origin, fixed, n, x);
    auto Mid = get_Mid(points, origin, fixed, n, x);
    auto Right = get_Right(points, origin, fixed, n, x);

    vector<lli> ans(n);
    for(int i = 0; i < n; i++){
        ans[i] = Left[i] + Mid[i] + Right[i];
    }

    for(auto x: ans) cout << x << endl;

	return 0;
}

/*

8 15
5 7 1
2 1 1
1 3 1
-1 5 1
-2 4 1
-4 2 1
-4 7 1
-5 6 1


// LEFT
9 8 
2 1 1
2 4 1
2 6 1
0 3 1
0 6 1
-1 4 1
-3 3 1
-4 6 1
-5 4 1

// MID
5 16
4 4 1
8 4 1
8 6 1
8 12 1
12 4 1


// RIGHT
10 4
1 2 1
2 3 1
3 1 1
4 1 1
4 5 1
5 3 1
6 3 1
6 5 1
7 1 1
9 5 1

*/