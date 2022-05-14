#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define x first
#define y second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

typedef pair<lli,lli> point;
const lli INF = 1e18;

struct Segment{
    point p1, p2;
    Segment() {}
    Segment(point p1, point p2): p1(p1), p2(p2) {}
};

struct Event{
    Segment s;
    bool horizontal;
    bool start;

    Event() {}
    //if vertical
    Event(Segment s): s(s), horizontal(0) {}
    //if horizontal
    Event(Segment s, bool start): s(s), horizontal(1), start(start){}

    bool operator<(const Event &e) const {
        if(s.p1.x != e.s.p1.x) return s.p1.x < e.s.p1.x;
        
        //! Mucho ojo con esto, depende de que se considera interseccion y qué no
        if(start && horizontal) return horizontal < e.horizontal;
        else if(!start && horizontal) return horizontal > e.horizontal;

        return horizontal < e.horizontal;
    }
};


bool segmentIntersections(const vector<Segment> &segments) {
    vector<Event> events;
    for(Segment s: segments) {
        if(s.p1.y == s.p2.y){ //horizontal
            events.push_back({{s.p1, s.p2}, true});  // start
            events.push_back({{s.p2, s.p1}, false}); // end
        } else {
            events.push_back({s});
        }
    }

    stable_sort(all(events));

    auto cmp = [](point a, point b) {
        return (a.y == b.y ? a.x < b.x : a.y < b.y);
    };
    set<point, decltype(cmp)> points_in_y(cmp);

    for(auto e: events) {
        if(e.horizontal) {
            if(e.start) {
                points_in_y.insert(e.s.p2);
            } else {
                points_in_y.erase(e.s.p1);
            }
        } else {
            auto p_low = e.s.p1, p_high = e.s.p2;
            auto it_lowest = points_in_y.lower_bound({-INF, p_low.y});
            if(it_lowest == points_in_y.end()) continue;
            
            if(it_lowest->second <= p_high.y) { // At least one point that intersects
                // Use order-statistics data structure to get how many crosses.
                return true;
            }
        }
    }
    return false;
}




int main () {
	//fastIO();

    lli n; cin>>n;
    
    vector<Segment> segments;
    for(int i = 0; i < n; i++) {
        lli x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;

        Segment first_vertical = {{x1, y1}, {x1, y2}};
        Segment second_vertical = {{x2, y1}, {x2, y2}};

        Segment first_horizontal = {{x1, y1}, {x2, y1}};
        Segment second_horizontal = {{x1, y2}, {x2, y2}};

        segments.push_back(first_vertical);
        segments.push_back(second_vertical);
        segments.push_back(first_horizontal);
        segments.push_back(second_horizontal);
        
    }


    if(segmentIntersections(segments)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }



	return 0;
}

