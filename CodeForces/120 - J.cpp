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

const ld eps = 0, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	point rotate(const ld & a) const{return point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));}
	point perp() const{return point(-y, x);}
	ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	ld length() const{return sqrtl(x * x + y * y);}
	point unit() const{return (*this) / length();}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

bool comp1(const point & a, const point & b){
	return le(a.y, b.y);
}

pair<point, point> closestPairOfPoints(vector<point> P){
	sort(P.begin(), P.end(), comp1);
	set<point> S;
	ld ans = inf;
	point p, q;
	int pos = 0;
	for(int i = 0; i < SZ(P); ++i){
		while(pos < i && geq(P[i].y - P[pos].y, ans)){
			S.erase(P[pos++]);
		}
		auto lower = S.lower_bound({P[i].x - ans - eps, -inf});
		auto upper = S.upper_bound({P[i].x + ans + eps, -inf});
		for(auto it = lower; it != upper; ++it){
			ld d = (P[i] - *it).length();
			if(le(d, ans)){
				ans = d;
				p = P[i];
				q = *it;
			}
		}
		S.insert(P[i]);
	}
	return {p, q};
}

lli oposite(lli option)
{
    switch(option)
    {
        case 1:
            return 4;
        case 2:
            return 3;
        case 3:
            return 2;
        default:
            return 1;
    }
}

int main () {
	//fastIO();


    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    int n; cin>>n;
	vector<point> points(n);



    for(int i = 0; i<n; i++)
        cin>>points[i].x>>points[i].y;
    

    map< point, int > option;
    map< pair<point, int>, int> idx;


    set< point > duplicates;

    vector<point> abs_points(n);
    for(int i = 0; i<n; i++)
    {
        lli x = points[i].x, y = points[i].y;
        lli new_x = abs(x), new_y = abs(y);
        
        point new_point(new_x, new_y);

        

        lli op = 0;

        if(x <= 0 && y <= 0){
            op = 4;
        }
        else if(x >= 0 && y <= 0){
            op = 3;
        }
        else if(x <= 0 && y >= 0){
            op = 2;
        }
        else{
            op = 1;
        }
        
        
        if( duplicates.count(new_point) )
        {
            lli op1 = option[new_point];
            cout << idx[{new_point, op1}] << " " << op1 << " " << i+1 << " " << oposite(op) << endl;
            return 0;
        }
        duplicates.insert(new_point);
                
        //cout << new_point << " " << op << endl;
        abs_points[i] = new_point;

        option[new_point] = op;
        idx[{new_point, op}] = i+1;


    }


    auto p_p = closestPairOfPoints(abs_points);

    lli op1 = option[p_p.first], op2 = option[p_p.second];

    cout << idx[{p_p.first, op1}] << " " << op1 << " " << idx[{p_p.second, op2}] << " " << oposite(op2) << endl;




	return 0;
}

