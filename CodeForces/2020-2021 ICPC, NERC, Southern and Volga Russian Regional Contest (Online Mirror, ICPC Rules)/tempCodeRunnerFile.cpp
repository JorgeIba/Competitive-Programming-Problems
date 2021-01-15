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

template<typename T = long double>
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

	ld length()const{ return sqrt(x*x + y*y); }
};

point<ld> intersectLines(point<ld> a1, point<ld> v1, point<ld> a2, point<ld> v2){ //Este no va o si?
	return a1 + v1 * ((a2 - a1).cross(v2) / v1.cross(v2));
}

int n,H;
vector<point<ld>> P;

bool isVisible(point<ld> A, point<ld> B, point<ld> C) //A -> el que quieres checar, C -> Punto mas alto, D -> onta el ojo
{
  if( (B-C).cross(A-C) <= 0 ) //Pasa algo no me acuerdo cual era
    return true;
  return false;
}

int main () {
    fastIO();
  cin >> n >> H;
  P.resize(n);
  forn(i,n) cin >> P[i].x >> P[i].y;
  point<ld> ojo = P[n-1];
  ojo.y += H;
  point<ld> alto = P[n-1];

  ld ans = 0;

  for(int i = n-1; i > 0; i--){ //por que desde i = n-2?

    if(!isVisible(P[i], alto, ojo) && isVisible(P[i-1], alto, ojo) ){ //Nomas se ve el siguiente
      point<ld> inter = intersectLines(P[i],P[i]-P[i-1],alto,alto-ojo);
      ans += (P[i-1] - inter).length();
    }
    else if(isVisible(P[i], alto, ojo) && isVisible(P[i-1], alto, ojo) ){ //Se ven los dos
      ans += (P[i-1] - P[i]).length();
    }
    //este if no es con el cross? la ultima?
    if( (P[i-1]-ojo).cross(alto - ojo) > 0 ) alto = P[i-1];
    
  }
  cout << fixed << setprecision(10) << ans << endl; 
	return 0;
}