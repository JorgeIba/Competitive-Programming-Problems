#include<bits/stdc++.h>
#include <queue>
#define lli long long int
#define ld long double
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lli> vlli;

const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point {
        ld x, y;
        point(ld x, ld y): x(x), y(y) {}
        point(): x(0), y(0) {}

        point operator+(const point & p) const{return point(x + p.x, y + p.y);}
        point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
        point operator/(const ld & k) const{return point(x / k, y / k);}

        point perp() const{return point(-y, x);}
        ld norm() const{return x * x + y * y;}
        ld dot(const point & p) const{return x * p.x + y * p.y;}
        ld length() const{return sqrtl(x * x + y * y);}
        ld ang() const{
		    ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
        }

};

struct circ {
        point c;
        int r;
        circ(): r(0), c(0,0) {}
};

vector<vector<point>> tangents(const point & c1, ld r1, const point & c2, ld r2, bool inner = false){
	//returns a vector of segments or a single point
	if(inner) r2 = -r2;
	point d = c2 - c1;
	ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
	if(eq(d2, 0) || le(h2, 0)) return {};
	point v = d*dr/d2;
	if(eq(h2, 0)) return {{c1 + v*r1}};
	else{
		point u = d.perp()*sqrt(h2)/d2;
		return {{c1 + (v - u)*r1, c2 + (v - u)*r2}, {c1 + (v + u)*r1, c2 + (v + u)*r2}};
	}
}

ld get_arc_len(circ& c, point a, point b) {
        ld angle = (b-c.c).ang() - (a-c.c).ang();
        return angle * c.r;
}

ld band_sz(circ& circ1, circ& circ2) {
        ld ans = 0.0l;
        auto tang = tangents(circ1.c, circ1.r, circ2.c, circ2.r);
        for(auto par : tang) ans += (par[1] - par[0]).length();

        point pp1 = tang[0][0];
        point pp2 = tang[0][1];

        ans += get_arc_len(circ1, pp2, pp1);

        pp1 = tang[1][0];
        pp2 = tang[1][1];

        ans += get_arc_len(circ2, pp2, pp1);

        return ans;
}

struct DSU {
        int N;
        vector<int> pa, sz;
        DSU(int n): pa(n), sz(n, 1), N(n) {
                forn(i,n) pa[i] = i;
        }
        int find(int u) {
                return pa[u] = (pa[u] == u? u : find(pa[u]));
        }
        bool join(int u, int v) {
                u = find(u), v = find(v);
                if(u == v) return false;
                if(sz[u] < sz[v]) swap(u,v);

                pa[v] = u;
                sz[u] += sz[v];
                N--;
                return true;
        }
        int size() {
                return N;
        }
};

ld kruskal(int n, vector<tuple<ld, int,int> >& edges) {
        ld ans = 0;

        DSU uf(n);
        
        sort(all(edges));
        for(auto [c, u, v]: edges) {
            if(uf.join(u,v))
                    ans += c;
        }

        return ans;
}

void solve(int n) {
        vector<circ> circs(n);
        forn(i,n)
                cin >> circs[i].c.x >> circs[i].c.y >> circs[i].r;
        vector<tuple<ld, int, int> > edges;
        forn(i,n) {
                forr(j,i + 1,n - 1) {
                        ld dis = band_sz(circs[i], circs[j]);
                        edges.pb(make_tuple(dis, i, j));
                }
        }
        cout << fixed << setprecision(3) << kruskal(n, edges) << endl;
}

int main() {
//   fastIO();

  int n = 0;
  while(cin >> n && n != -1)
          solve(n);
  return 0;
}

