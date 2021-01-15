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

const ld eps = 1e-9; //for use with integers set eps=0
bool geq(ld a, ld b){ return a-b >= -eps; }
bool leq(ld a, ld b){ return b-a >= -eps; }
bool ge(ld a, ld b){ return a-b > eps; }
bool le(ld a, ld b){ return b-a > eps; }
bool eq(ld a, ld b){ return abs(a-b) <= eps; }
bool neq(ld a, ld b){ return abs(a-b) > eps; }

template<typename T = lli>
struct point{
	T x,y;
	point(): x(0), y(0){}
	point(T a, T b): x(a), y(b){}
	/*--Operators--*/
	point<T> operator+(const point<T>& p)const{ return point<T>(x+p.x,y+p.y); }
	point<T> operator-(const point<T>& p)const{ return point<T>(x-p.x,y-p.y); }
	point<T> operator*(const ld& k)const{ return point<T>(x*k,y*k); }

	/*--Functions--*/
	T cross(const point& p)const{
		return x*p.y - y*p.x;
	}

	ld length()const{ return sqrtl(x*x + y*y); }
};

point<ld> intersectLines(point<lli> a1, point<lli> v1, point<lli> a2, point<lli> v2){ //Este no va o si?
    point<ld> aa1(a1.x, a1.y);
    point<ld> vv1(v1.x, v1.y);
    point<ld> aa2(a2.x, a2.y);
    point<ld> vv2(v2.x, v2.y);

	return aa1 + vv1 * ((aa2 - aa1).cross(vv2) / vv1.cross(vv2));
}


bool isVisible(point<lli> &A, point<lli> &B, point<lli> &C) //A -> el que quieres checar, C -> Punto mas alto, D -> onta el ojo
{
  if(leq((B-C).cross(A-C), 0)) 
    return true;
  return false;
}

int main () {
    fastIO();
    lli n,H; cin >> n >> H;

    vector<point<lli>> P(n);

    forn(i,n) cin >> P[i].x >> P[i].y;

    point<lli> ojo = P[n-1];
    ojo.y += H;
    point<lli> alto = P[n-1];

    ld ans = 0;

    for(int i = n-1; i > 0; i--){

    bool firstVisible = isVisible(P[i], alto, ojo), secondVisible = isVisible(P[i-1], alto, ojo);

    if(!firstVisible && secondVisible){ //Nomas se ve el siguiente

        point<ld> inter = intersectLines(P[i],P[i]-P[i-1],alto,alto-ojo);
        point<ld> aux(P[i-1].x, P[i-1].y);
        ans += (aux - inter).length();
    }

    else if(firstVisible && secondVisible){ //Se ven los dos
        ans += (P[i-1] - P[i]).length();
    }


    if( ge((P[i-1]-ojo).cross(alto - ojo), 0) ) alto = P[i-1];  
    }
    cout << fixed << setprecision(8) << ans << endl; 
	return 0;
}