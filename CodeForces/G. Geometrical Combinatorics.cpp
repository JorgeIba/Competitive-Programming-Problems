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

#define type lli
struct Point{
    type x, y; 
    Point() {}
    Point(type x, type y): x(x), y(y) {}

    Point operator+(const Point & p) const{return Point(x + p.x, y + p.y);}
	Point operator-(const Point & p) const{return Point(x - p.x, y - p.y);}
	Point operator*(const type & k) const{return Point(x * k, y * k);}
    bool operator==(const Point & P) const{return x == P.x && y == P.y;}


    type dot(const Point & p) const{return x * p.x + y * p.y;}
	type cross(const Point & p) const{return x * p.y - y * p.x;}
};


int sgn(int a)
{
    if(a < 0) return -1;
    else if(a > 0) return 1;
    return 0;
}

lli piso(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

lli techo(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

int intersectLineSegmentInfo( Point & a,  Point & v,  Point & c,  Point & d){
	//line a+tv, segment cd
	Point v2 = d - c;
	type det = v.cross(v2);
	if(det==0){
		if((c - a).cross(v) ==  0){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}

//13
const lli maxN = 1e6;
const lli MOD = 1e9+7; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}


lli nCr(lli n, lli r)
{
    if( r > n || r < 0 || n < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

Point a, v;
bool compare( pair<Point, Point> A, pair<Point, Point> B)
{
    lli det1 = v.cross(A.second);
    lli det2 = v.cross(B.second);

    lli aux1 = (A.first - a).cross(A.second);
    lli aux2 = (B.first - a).cross(B.second);

    return aux1 * det2 < aux2 * det1;
}

void solve()
{
    vector<Point> p(3);
    for(int i = 0; i < 3; i++) cin>>p[i].x>>p[i].y;


    lli ans = 0;
    for(int i = 0; i<=maxN; i++)
    {
        Point seg1 = p[0] - p[1], seg2 = p[1] - p[2], seg3 = p[2] - p[0];
        
        a = {2*i, 0}, v = {-1, 1};

        int is_inter1 = intersectLineSegmentInfo(a, v, p[0], p[1]);
        int is_inter2 = intersectLineSegmentInfo(a, v, p[1], p[2]);
        int is_inter3 = intersectLineSegmentInfo(a, v, p[2], p[0]);

        vector<pair<Point,Point>> p_inter;
        if(is_inter1==1)
        {
            p_inter.push_back({p[0], seg1});
        }
        if(is_inter2==1)
        {
            p_inter.push_back({p[1], seg2});
        }
        if(is_inter3==1)
        {
            p_inter.push_back({p[2], seg3});
        }
        if(!SZ(p_inter)) continue;
        sort(all(p_inter), compare);

        auto aux_left = p_inter[0];
        auto aux_right = p_inter.back();

        lli det1 = v.cross(aux_left.second);
        lli det2 = v.cross(aux_right.second);


        lli aux1 = (aux_left.first - a).cross(aux_left.second);
        lli aux2 = (aux_right.first - a).cross(aux_right.second);

        auto left = a.y + piso(aux1, det1);
        auto right = a.y + techo(aux2, det2);

        if(right > left) continue;


        ans += (nCr(left+1, i+1) - nCr(right, i+1) + MOD)%MOD;
        if(ans >= MOD) ans-=MOD;

    }
    assert(ans >= 0 && ans < MOD);
    cout << ans << endl;
    return;
}


int main () {
	//fastIO();
    prec();
    lli t; cin>>t;
    while(t--) solve();


	return 0;
}