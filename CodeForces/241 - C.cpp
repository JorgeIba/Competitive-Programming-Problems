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


struct Point{
    lli x, y; 
    lli v;
    int idx;

    Point(): x(0), y(0) {}
    Point(lli x, lli y): x(x), y(y) {}

    Point operator-(const Point &P) const {
        return {x - P.x, y - P.y};
    }

    lli dot(const Point &P) const {
        return x * P.x + y * P.y;
    }
    lli cross(const Point &P) const {
        return x * P.y - y * P.x;
    }
};



bool pointInLine(const Point & a, const Point & v, const Point & p){
	return (p - a).cross(v) == 0;
}

bool pointInSegment(const Point & a, const Point & b, const Point & p){
	//segment ab, Point p
	return pointInLine(a, b - a, p) && (a-p).dot(b-p) <= 0;
}

int sgn(lli x){
    if(x == 0) return 0;
    else if(x < 0) return -1;
    return 1;
}

int intersectSegmentsInfo(const Point & a, const Point & b, const Point & c, const Point & d){
	//segment ab, segment cd
	Point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no Point
			}
		}else{
			return 0; //no Point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single Point, 0: no Point
	}
}



const int INF = 1e9;
const int WIDTH = 1e5;
const int HEIGHT = 100;
int main () {
	//fastIO();
	
	int h_1, h_2, n; cin>>h_1>>h_2>>n;

    Point S(0, h_1), E(WIDTH, h_2);

    vector<array<int, 3>> ranges_up, ranges_down;
    forn(i, n){
        int v, l, r;
        char c;
        cin>>v>>c>>l>>r;
        if(c == 'F'){
            ranges_down.push_back({l, r, v});
        } else {
            ranges_up.push_back({l, r, v});
        }
    } 

    sort(all(ranges_down), [&](auto a, auto b){
        auto [l_a, r_a, v_a] = a;
        auto [l_b, r_b, v_b] = b;
        return l_a < l_b;
    });
    sort(all(ranges_up), [&](auto a, auto b){
        auto [l_a, r_a, v_a] = a;
        auto [l_b, r_b, v_b] = b;
        return l_a < l_b;
    });

    auto add_non = [&](int last_x, int y, int l) -> vector<Point> {
        Point non_l = Point(last_x,y);
        Point non_r = Point(l-1, y);
        if(non_l.x < non_r.x) {
            non_l.v = -INF;
            return {non_l, non_r};
        }
        return {};
    };

    vector< pair<Point,Point> > segments_up;
    int last_x = 0;
    for(auto [l, r, v]: ranges_up){
        auto non_segm = add_non(last_x, HEIGHT, l);
        if(!non_segm.empty()) {
            segments_up.push_back({non_segm[0], non_segm[1]});
        }

        Point segm_l = Point(l, HEIGHT);
        Point segm_r = Point(r, HEIGHT);
        segm_l.v = v;
        segments_up.push_back({segm_l, segm_r});
        last_x = r+1;
    }
    auto non_segm = add_non(last_x, HEIGHT, WIDTH);
    if(!non_segm.empty()){
        segments_up.push_back({non_segm[0], non_segm[1]});
    }


    vector< pair<Point,Point> > segments_down;
    last_x = 0;
    for(auto [l, r, v]: ranges_down){
        auto non_segm = add_non(last_x, 0, l);
        if(!non_segm.empty()) {
            segments_down.push_back({non_segm[0], non_segm[1]});
        }

        Point segm_l = Point(l, 0);
        Point segm_r = Point(r, 0);
        segm_l.v = v;
        segments_down.push_back({segm_l, segm_r});
        last_x = r+1;
    }
    non_segm = add_non(last_x, 0, WIDTH);
    if(!non_segm.empty()) {
        segments_down.push_back({non_segm[0], non_segm[1]});
    }


    auto get_ans = [&](){
        vector< pair<Point,Point> > all_segments;

        int m = SZ(segments_up), k = SZ(segments_down);

        const int ITER = 105;

        for(int i = 0; i < m; i++){
            forr(level, -ITER, ITER){
                auto [a, b] = segments_up[i];
                a.y = 2*HEIGHT * level + 100;
                b.y = 2*HEIGHT * level + 100;
                a.idx = i;
                all_segments.push_back({a, b});
            }
        }
        
        for(int i = 0; i < k; i++){
            forr(level, -ITER, ITER){
                auto [a, b] = segments_down[i];
                a.y = 2*HEIGHT * level;
                b.y = 2*HEIGHT * level;
                a.idx = i + m;
                all_segments.push_back({a, b});
            }
        }


        vector< Point > holes;
        int last_h = h_2;
        forr(level, 0, ITER){
            int above = (level+1) * HEIGHT;
            int diff = above - last_h;
            int new_h = above + diff;
            holes.push_back(Point(WIDTH, new_h));

            last_h = new_h;
        }

        last_h = h_2;
        for(int level = -1; level >= -ITER; level--){
            int above = (level+1) * HEIGHT;
            int diff = last_h - above;
            int new_h = above - diff;
            holes.push_back(Point(WIDTH, new_h));

            last_h = new_h;
        }

        lli ans = 0;
        for(auto hole: holes){
            lli score = 0;
            set<int> idx_touch;
            for(auto [a, b]: all_segments){
                if(intersectSegmentsInfo(S, hole, a, b) != 0) {
                    if(a.v > 0) {
                        if(idx_touch.count(a.idx)) {
                            score = -INF;
                            break;
                        } else {
                            score += a.v;
                            idx_touch.insert(a.idx);
                        }
                    } else {
                        score = -INF;
                        break;
                    }
                }
            }

            ans = max(ans, score);
        }

        return ans;
    };

    auto ans = get_ans();
    cout << ans << endl;



	return 0;
}

