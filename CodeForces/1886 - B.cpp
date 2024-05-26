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


#define point pair<int,int>
#define x first
#define y second


const ld eps = 1e-9;
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b


void main_(){
    // int n; cin>>n;

    vector< point > points(3);
    forn(i, 3) cin>>points[i].x>>points[i].y;

    point O = {0,0};


    auto is_inside = [&](point p, point center, ld radius){
        lli x = (center.x - p.x);
        lli y = (center.y - p.y);

        // debugg(x);
        // debugg(y);
        // debugg(radius);

        if(leq(x*x + y*y, radius*radius)) {
            return true;
        }
        return false;
    };

    auto is_touching = [&](point p, point center, ld radius){
        lli x = (center.x - p.x);
        lli y = (center.y - p.y);

        // debugg(x);
        // debugg(y);
        // debugg(radius);

        if(leq(x*x + y*y, 4*radius*radius)) {
            return true;
        }
        return false;
    };



    auto check = [&](ld radius){
        if(is_inside(points[0], points[1], radius) && is_inside(O, points[1], radius)){
            return true;
        }

        if(is_inside(points[0], points[2], radius) && is_inside(O, points[2], radius)){
            return true;
        }

        bool inside_P = (is_inside(points[0], points[1], radius) || is_inside(points[0], points[2], radius));
        bool inside_O = (is_inside(O, points[1], radius) || is_inside(O, points[2], radius));
        bool touch = (is_touching(points[1], points[2], radius));

        // debugg(inside_O);
        // debugg(inside_P);
        // debugg(touch);

        if(inside_P && inside_O && touch){
            return true;
        }
        return false;
    };

    ld l = 0, r = 1e5, ans = r;
    while(r-l > eps){
        // debugg(l);
        // debugg(r);
        // debugg(r-l);
        ld mid = (l+r)/2;
        if(check(mid)){
            r = mid;
            ans = mid;
        } else {
            l = mid;
        }
    }

    // cout << check(3.3) << endl;

    cout << fixed << setprecision(20) << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

