#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-7, inf = numeric_limits<ld>::max(), pi = acos(-1);
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
    lli idx;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-=(const point & p){*this = *this - p; return *this;}
	point operator*=(const ld & p){*this = *this * p; return *this;}
	point operator/=(const ld & p){*this = *this / p; return *this;}

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
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}


vector<point> maxIzq, maxDer;
vector< point > points, picos;
lli N; 

void getPicos()
{
    lli n = points.size();
    for(int i = 0; i<n; i++)
    {
        if(i==0 && (points[i].y > points[i+1].y) ){
            picos.push_back(points[i]); continue;
        }
        else if(i==n-1 && (points[i].y > points[i-1].y)){
            picos.push_back(points[i]); continue;
        }
        else if( (i>0 && i<n-1) &&  (points[i].y > points[i+1].y) && (points[i].y > points[i-1].y)){
            picos.push_back(points[i]);
        }
    }
}

void getMaxIzq()
{
    stack< point > pila;
    for(int i = 0; i<picos.size(); i++)
    {
        lli num = picos[i].y;
        while(!pila.empty() && num > pila.top().y)
        {
            pila.pop();
        }
        if(pila.empty()) maxIzq[i] = point(-1,-1);
        else  maxIzq[i] = pila.top();
        pila.push(picos[i]);
    }
}

void getMaxDer()
{
    stack< point > pila;
    for(int i = picos.size()-1; i>=0; i--)
    {
        lli num = picos[i].y;
        while(!pila.empty() && num > pila.top().y)
        {
            pila.pop();
        }
        if(pila.empty()) maxDer[i] = point(-1,-1);
        else  maxDer[i] = pila.top();
        pila.push(picos[i]);
    }
}


int intersectLinesInfo(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1 and a2+tv2
	ld det = v1.cross(v2);
	if(eq(det, 0)){
		if(eq((a2 - a1).cross(v1), 0)){
			return -1; //infinity points
		}else{
			return 0; //no points
		}
	}else{
		return 1; //single point
	}
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}



vector< pair<point,point> > events;

void getTopasIzq()
{
    for(int i = 0; i<picos.size(); i++)
    {
        if(maxIzq[i].x == -1) continue;
        point topas = maxIzq[i];
        point adelante = points[ topas.idx + 1 ];
        point aux = point(0,picos[i].y);
        point where = intersectLines( topas, adelante - topas,  aux, picos[i] - aux);
        events.push_back( {where, picos[i]} );
        points.push_back(where);
    }
}

void getTopasDer()
{
    for(int i = 0; i<picos.size(); i++)
    {
        if(maxDer[i].x == -1) continue;
        point topas = maxDer[i];
        point atras = points[ topas.idx - 1 ];
        point aux = point(1e9, points[i].y);
        point where = intersectLines(atras, topas-atras, picos[i], aux-picos[i]);
        points.push_back(where);
        events.push_back( {picos[i], where} );
    }
}


lli binBusqueda(ld s)
{
    lli l = 0, r = points.size();
    lli res = 0;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( le(points[mid].x, s) )
        {
            l = mid+1;
        }
        else
        {
            res = mid;
            r = mid-1;
        }
    }
    return res;
}

ld area(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += P[i].cross(P[(i + 1) % n]);
	}
	return abs(ans / 2);
}


ld answ = 0;

void getArea(ld l, ld r)
{
    lli idx = binBusqueda(l);
    vector< point > toGetArea;
    while( points[idx].x <= r && idx<points.size())
    {
        toGetArea.push_back(points[idx]);
        idx++;
    }
    answ += area(toGetArea);
    if(answ != answ)
    {
        for(auto x:toGetArea)
        {
            cout<<x<<endl;
        }
    }
}


bool cmp(point &a, point &b)
{
    if(a.x == b.x && a.y == b.y) return true;
    return false;
}

bool cmp2(pair< point,point> &a, pair< point,point> &b)
{
    return cmp(a.first, b.first) && cmp(a.second, b.second);
}

int main()
{
    fastIO();
    cin>>N;
    points.resize(N);
    lli cont=0;
    for(auto &x: points)
    {
        cin>>x;
        x.idx = cont++; 
    }
    getPicos();
    lli s = picos.size();
    maxIzq.resize(s); maxDer.resize(s); 
    
    getMaxIzq();
    getMaxDer();
    getTopasIzq();
    getTopasDer();


    //erase(unique(all(events), events.end()));
    sort(all(events));
    sort(all(points));
    //auto asd = unique(all(points),cmp);
    //points.erase(asd, points.end());
    
    //auto asb = unique(all(events), cmp2);
    //events.erase(asb, events.end());

    ld last = 0;

    for(auto x: events)
    {
        if( geq(x.first.x, last) )
        {
            getArea(x.first.x, x.second.x);
            last = x.second.x;
        }
    }
    
    //getArea(6.3333 , 8);
    cout<<fixed<<setprecision(7)<< answ <<endl;
    

    
    return 0;
}