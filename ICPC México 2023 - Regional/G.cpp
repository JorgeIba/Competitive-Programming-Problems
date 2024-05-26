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
    lli d;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
};

int sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return (p - a).cross(v) == 0;
}

bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && (a - p).dot(b - p) <= 0;
}

int intersectLinesInfo(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1 and a2+tv2
	lli det = v1.cross(v2);
	if(det == 0){
		if((a2 - a1).cross(v1) == 0){
			return -1; //infinity points
		}else{
			return 0; //no points
		}
	}else{
		return 1; //single point
	}
}

const lli INF = 1e15;
point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	lli det = v1.cross(v2);
    auto num = v1 * ((a2 - a1).cross(v2));
    if(num.x % det == 0 && num.y % det == 0) 
	    return a1 + num / det;
    return {INF, INF};
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	//line a+tv, segment cd
	point v2 = d - c;
	lli det = v.cross(v2);
	if(det == 0){
		if((c - a).cross(v) == 0){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}


int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
    if(a == b) {
        if(c == d && a == c) return 2;
        if(pointInSegment(c, d, a)) return 3;
    } else if(c == d) {
        if(a == b && a == c) return 2;
        if(pointInSegment(a, b, c)) return 4;
    }
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}


int main () {
	//fastIO();
	
    int n; cin>>n;

    vector< point > radios(n);
    for(auto &p: radios) {
        cin>>p.x>>p.y>>p.d;
    }


    auto get_lines = [&](point &r) {
        point a = r + point(0, r.d);
        point b = r + point(r.d, 0);
        point c = r + point(0, -r.d);
        point d = r + point(-r.d, 0);
        vector< pair<point,point> > segments;
        segments.push_back({a, b});
        segments.push_back({b, c});
        segments.push_back({c, d});
        segments.push_back({d, a});
        return segments;
    };

    vector< pair<point,point> > lines;
    lines = get_lines(radios[0]);

    for(int i = 1; i < n; i++) {
        auto lines_i = get_lines(radios[i]);
        vector< pair<point,point> > valids;
        for(auto [p, q]: lines) {
            for(auto [r, s]: lines_i){
                auto info = intersectSegmentsInfo(p, q, r, s);
                // debugg(info);
                if(info == -1) {
                    vector< point > aux;
                    aux.push_back(p);
                    aux.push_back(q);
                    aux.push_back(r);
                    aux.push_back(s);
                    sort(all(aux));
                    valids.push_back({aux[1], aux[2]});
                } else if(info == 1){
                     auto crossing = intersectLines(p, q-p, r, s-r);
                     if(crossing.x != INF) 
                        valids.push_back({crossing, crossing});

                } else if(info == 2){
                    valids.push_back({p, p});
                } else if(info == 3) {
                    valids.push_back({p, p});
                } else if(info == 4){
                    valids.push_back({r, r});
                }
            }
        }
        // sort(all(valids));
        // valids.erase(unique(all(valids)), valids.end());
        lines = valids;
    }

    sort(all(lines));
    lines.erase(unique(all(lines)), lines.end());

    vector< point > ans;
    for(int i = 0; i < SZ(lines); i++) {
        auto [p, q] = lines[i];
        if(p == q) {
            // cout << p.x << " -- " << p.y << endl;
            ans.push_back(p);
            continue;
        }

        auto diff = q - p;
        int x = diff.x / abs(diff.x);
        int y = diff.y / abs(diff.y);

        auto curr = p;
        ans.push_back(curr);
        while(curr != q) {
            curr = curr + point(x, y);
            ans.push_back(curr);
        }
    }

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());

    for(auto p: ans) cout << p.x << " " << p.y << endl;


	return 0;
}


