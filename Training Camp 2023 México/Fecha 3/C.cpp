#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define ALL(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define fore(i, a, b) for(int i = a; i < b; i++)
#define pb push_back

using namespace std;

const ld EPS = 1e-9, DINF = 1e9;

struct pt {  // for 3D add z coordinate
	ld x,y;
	pt(ld x, ld y):x(x),y(y){}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<=EPS&&abs(y-p.y)<=EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ld t){return pt(x*t,y*t);}
	pt operator/(ld t){return pt(x/t,y/t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	
	pt unit(){return *this/norm();}
	ld operator%(const pt &p) const{return x*p.y-y*p.x;}
	
};

struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}

	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<=EPS;} // 2D
	
	pt operator^(ln l){ // intersection
		if(*this/l)return pt(DINF,DINF);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
		return r;
	}
};


// polygon intersecting left side of halfplanes
struct halfplane:public ln{
	ld angle;
	halfplane(){}
	halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
	bool out(pt q){return pq%(q-p)<-EPS;}
};
vector<pt> intersect(vector<halfplane> b){
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	fore(i,0,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(ALL(b));
	int n=SZ(b),q=1,h=0;
	vector<halfplane> c(SZ(b)+10);
	fore(i,0,n){
		while(q<h&&b[i].out(c[h]^c[h-1])) h--;
		while(q<h&&b[i].out(c[q]^c[q+1])) q++;
		c[++h]=b[i];
		if(q<h&&abs(c[h].pq%c[h-1].pq)<EPS){
			if(c[h].pq*c[h-1].pq<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
	while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
	if(h-q<=1)return {};
	c[h+1]=c[q];
	vector<pt> s;
	fore(i,q,h+1) s.pb(c[i]^c[i+1]);
	return s;
}

ld get_area(const vector<pt> &points) {
    ld area = 0;
    int n = SZ(points);
    for(int i = 0; i < n; i++) {
        area += (points[i] % points[(i+1)%n]);
    }
    return abs(area) / 2;
}


bool check(int k, const vector<pt> &points) {
    vector< halfplane > planes;
    int n = SZ(points);
    for(int i = 0; i < n; i++) {
        auto point_i = points[i], point_j = points[ (i + k + 1) % n];
        // planes.push_back( {point_i, point_j} );
        planes.push_back( {point_j, point_i} );
    }

    auto poly = intersect(planes);


    return get_area(poly) > 0;
}



int main () {
	//fastIO();

    #ifdef ONLINE_JUDGE
        freopen("jungle.in", "r", stdin);
        freopen("jungle.out", "w", stdout);
    #endif
	
    int n; cin>>n;

    vector< pt > points(n);
    for(auto &p: points) cin>>p.x>>p.y;


    int l = 0, r = n-2, ans = r;
    while(l <= r) {
        int mid = (l+r) / 2;
        if(check(mid, points)) {
            l = mid+1;
        } else {
            r = mid-1;
            ans = mid;
        }
    }

    cout << ans << endl;



	return 0;
}

