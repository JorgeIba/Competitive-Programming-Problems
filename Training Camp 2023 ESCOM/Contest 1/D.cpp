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

bool le(lli a, lli b){return a < b;}
bool eq(lli a, lli b){return a == b;}

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

void polarSort(vector<point> & P, const point & o, const point & v){
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}

lli nC4(lli n){
    return n * (n-1) * (n-2) * (n-3) / 24;
}

lli nC3(lli n){
    return n * (n-1) * (n-2) / 6;
}

int main () {
	fastIO();

    int n; cin>>n;
    vector< point > points(n);

    for(auto &p: points) cin>>p.x>>p.y;

    lli ans = 0;
    for(int i = 0; i < n; i++){
        vector< point > points_p;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            points_p.push_back(points[j]);
        }

        point fixed = points[i];

        polarSort(points_p, fixed, point(1, 0));

        int m = SZ(points_p);
        int cnt_k = 0;
        lli not_inside = 0;
        for(int j = 0, k = 0; j < m; j++){
            while((points_p[j] - fixed).cross( points_p[k] - fixed ) >= 0 && cnt_k < m) {
                k = (k+1) % m;
                cnt_k++;
            }

            not_inside += nC3(cnt_k-1);
            cnt_k--;
        }

        not_inside += nC3(m);
        lli f_p = nC4(n) - not_inside;
        ans += f_p;
    }

    cout << ans << endl;



	return 0;
}

