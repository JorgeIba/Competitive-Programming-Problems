#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define point pair<lli,lli>
#define x first
#define y second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

lli N;

bool respuesta(string s)
{
  return s == "Yes";
}

bool query1(point p) //Punto
{
  cout << "? 1 " << p.x << " " << p.y << endl;
  fflush(stdout);
  string ans; cin>>ans;
  return respuesta(ans);
}

bool query2(point p1, point p2) //Segmento
{
  cout << "? 2 " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
  fflush(stdout);
  string ans; cin>>ans;
  return respuesta(ans);
}

bool query3(point p1, point p2, point p3) //Triangulo
{
  cout << "? 3 " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y << endl;
  fflush(stdout); 
  string ans; cin>>ans;
  return respuesta(ans);
}

vector<point> triangulo(lli lower_x, lli upper_x, lli lower_y, lli upper_y)
{
  lli mid = (lower_x + upper_x) / 2;
  lli constante = upper_x + upper_y;
  point p1 = {mid, lower_y}; //Abajo izquierda
  point p2 = {constante - lower_y, lower_y}; // Abajo derecha
  point p3 = {mid, constante - mid}; //Arriba
  return {p1, p2, p3};
}



lli search_col(){
  lli l, r, m;
  l = 1; r = N;
  while(l < r){
    m = (l + r) >> 1;
    if((l + 1) == r){
      if(query2({r, 1}, {r, N}))
        return r;
      return l;
    }
    vector<point> T = triangulo(l, r, 1, N);
    if(query3(T[0], T[1], T[2]))
      l = m;
    else
      r = m - 1;
  }
  return l;
}

lli search_row(lli x){
  lli l, r, m;
  l = 1; r = N;
  while(l < r){
    m = (l + r) >> 1;
    if((l + 1) == r){
      if(query1({x,r}))
        return r;
      return l;
    }
    if(query2({x, m}, {x, r}))
      l = m;
    else
      r = m - 1;
  }
  return l;
}

int main () {
	//fastIO();
  cin >> N;

  lli x = search_col();

  lli y = search_row(x);

  cout << "! " << x << ' ' << y << endl;

	return 0;
}