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


/*
  ID_DIR       CCW          CW
    p_0     p_1 - p_0    p_0 - p_4
    p_1     p_2 - p_1    p_1 - p_0
    p_2     p_3 - p_2    p_2 - p_1
    p_3     p_4 - p_3    p_3 - p_2
    p_4     p_0 - p_4    p_4 - p_3
*/

/*
  ID_DIR     (cos(theta), sin(theta))         REPR
    p_0     4*cos(0*72°), 4*sin(0*72°)    ( 4, 0)
    p_1     4*cos(1*72°), 4*sin(1*72°)    (-1 + sqrt{5},  sqrt{10 + 2*sqrt{5}}) 
    p_2     4*cos(2*72°), 4*sin(2*72°)    (-1 - sqrt{5},  sqrt{10 - 2*sqrt{5}})
    p_3     4*cos(3*72°), 4*sin(3*72°)    (-1 - sqrt{5}, -sqrt{10 - 2*sqrt{5}})
    p_4     4*cos(4*72°), 4*sin(4*72°)    (-1 + sqrt{5}, -sqrt{10 + 2*sqrt{5}})
*/

struct Cosine{
    // a + b sqrt(5)
    lli a, b;

    Cosine(): a(0), b(0) {}
    Cosine(lli a, lli b): a(a), b(b) {}

    Cosine operator+(const Cosine &C) const{ return {a + C.a, b + C.b}; }

    Cosine operator-(const Cosine &C) const{ return {a - C.a, b - C.b}; }

    bool operator==(const Cosine &C) const{ return a == C.a && b == C.b; }

    bool operator!=(const Cosine &C) const { return !(*this == C); }

    ld real_value() const{
        return a + b*sqrt(5);
    }
};

struct Sine{
    // a*sqrt(10 + 2*sqrt(5)) + b*sqrt(10 - 2*sqrt(5))
    lli a, b;

    Sine(): a(0), b(0) {}
    Sine(lli a, lli b): a(a), b(b) {}

    Sine operator+(const Sine &S) const{ return {a + S.a, b + S.b}; }

    Sine operator-(const Sine &S) const{ return {a - S.a, b - S.b}; }

    bool operator==(const Sine &S) const{ return a == S.a && b == S.b; }

    bool operator!=(const Sine &S) const { return !(*this == S); }

    ld real_value() const{
        ld sqr5 = sqrt(5);
        return a*sqrt(10 + 2*sqr5) + b*sqrt(10 - 2*sqr5);
    }
};

struct Point{
    Cosine x;
    Sine y;

    Point() {}
    Point(Cosine x, Sine y): x(x), y(y) {}

    Point operator+(const Point &P) const { return {x + P.x, y + P.y}; }

    Point operator-(const Point &P) const { return {x - P.x, y - P.y}; }

    bool operator==(const Point &P) const{ return {x == P.x && y == P.y}; }

    bool operator!=(const Point &P) const{ return !(*this == P); }

    pair<ld,ld> real_values(){
        return {x.real_value(), y.real_value()};
    }
};

const vector< Point > dirs = {
    Point{ { 4,  0}, { 0,  0} },
    Point{ {-1,  1}, { 1,  0} },
    Point{ {-1, -1}, { 0,  1} },
    Point{ {-1, -1}, { 0, -1} },
    Point{ {-1,  1}, {-1,  0} }
};

const int LIMIT = 70;
map< array<lli, 5>, lli > dp[LIMIT+1]; // dp[{cos, sin, dir}]
int main () {

    auto move = [&](Point P, int dir, bool ccw) {
        if(ccw)
            return P + (dirs[ (dir+1)%5 ] - dirs[dir]);
        return P + (dirs[dir] - dirs[ (dir-1+5)%5 ]);
    };

    auto get_info = [](Point P, int dir) -> array<lli, 5> {
        return {P.x.a, P.x.b, P.y.a, P.y.b, dir};
    };

    Point origin({4, 0}, {0, 0});    
    dp[0][get_info(origin, 0)] = 1;

    forr(i, 1, LIMIT){
        for(auto [key, val]: dp[i-1]) {
            auto [a_x, b_x, a_y, b_y, dir] = key;

            Point P({a_x, b_x}, {a_y, b_y});
            Point P_ccw = move(P, dir, true);
            Point P_cw  = move(P, dir, false);

            dp[i][ get_info(P_ccw, (dir+1)%5) ] += val;
            dp[i][ get_info(P_cw,  (dir-1+5)%5) ] += val;
        }
    }

    cout << dp[LIMIT][get_info(origin, 0)] << endl;
    cout << dp[LIMIT][get_info(origin, 1)] << endl;
    cout << dp[LIMIT][get_info(origin, 2)] << endl;
    cout << dp[LIMIT][get_info(origin, 3)] << endl;
    cout << dp[LIMIT][get_info(origin, 4)] << endl;

	return 0;
}

