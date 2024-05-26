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


const lli INF = 2e18;

struct Point{
	lli x, y;
	Point(): x(0), y(0) {}
	Point(lli x, lli y): x(x), y(y) {}

	Point operator-(const Point &P) const {
		return {x - P.x, y - P.y};
	}

	lli norm2() const {
		return x*x + y*y;
	}

	bool operator==(const Point &P) const {
		return pair<lli,lli>{x, y} == pair<lli,lli>{P.x, P.y};
	}

	bool operator<(const Point &P) const {
		return pair<lli,lli>{x, y} < pair<lli,lli>{P.x, P.y};
	}
};


bool onx(Point a, Point b){return a.x<b.x;}
bool ony(Point a, Point b){return a.y<b.y;}
struct Node {
	Point pp;
	lli x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	lli distance(Point p){
		lli x=min(max(x0,p.x),x1);
		lli y=min(max(y0,p.y),y1);
		return (Point(x,y)-p).norm2();
	}
	Node(vector<Point>&& vp):pp(vp[0]){
		for(Point p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(SZ(vp)>1){
			sort(all(vp),x1-x0>=y1-y0?onx:ony);
			int m=SZ(vp)/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<Point>& vp):root(new Node({all(vp)})) {}
	pair<lli,Point> search(Point p, Node *node){
		if(!node->first){
			//avoid query point as answer
			if(p==node->pp) return {INF,Point()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		lli bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.first) best=min(best,search(p,s));
		return best;
	}
	pair<lli,Point> nearest(Point p){return search(p,root);}
};

void main_(){
	
	int n; cin>>n;
	vector< Point > points(n);
	for(auto &p: points) cin>>p.x>>p.y;

	KDTree *KD = new KDTree(points);

	forn(i, n){
		cout << KD->nearest(points[i]).first << endl;
	}


}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

