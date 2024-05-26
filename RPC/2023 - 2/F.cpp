#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long long int
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	
	
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	lli norm() const{return x * x + y * y;}
	

	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool half(const point & p) const{return p.cross(*this) < 0 || (p.cross(*this) ==  0 && p.dot(*this) < 0);}
};

ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

void polarSort(vector< point > & P, const point & o, const point & v, const int dist = 1){
	sort(P.begin(), P.end(), [&](const auto & a, const auto & b){
		auto left = point((a - o).half(v), 0);
		auto right = point((b - o).half(v), (a - o).cross(b - o));

        if(left == right) {
            if(dist) return (a - o).norm() < (b - o).norm();
            return (a - o).norm() > (b - o).norm();
		}
		return left < right;
	});
}

int isLeft(point start, point end, point p_test) {
	auto cr = (end-start).cross(p_test - start);
	if(cr > 0) return 1;
	if(cr < 0) return 0;
	else return -1;
}

struct Fenwick {
  vector<long long> tree;
  int n;

  void init(int _n) {
    n = _n;
    tree.resize(n+1, 0);
    for (int i = 0 ; i <= n ; i++) {
      tree[i] = 0;
    }
  }

  void update(int idx, long long val) {
    for (; idx <= n ; idx += idx & -idx) {
      tree[idx] += val;
    }
  }

  long long query(int idx) {
    long long ret = 0;
    while (idx > 0) {
      ret += tree[idx];
      idx -= idx & -idx;
    }
    return ret;
  }

  long long query(int x, int y) {
    return query(y) - query(x-1);
  }
};


lli calc(vector<point> points, point p_start, point p_end, bool is_up = true) {
	int m = SZ(points);

    if(is_up)
	    polarSort(points, p_start, p_end - p_start);
    else {
        polarSort(points, p_start, p_start - p_end, 0);
        reverse(all(points));
    }

    map< point, int > index;
	for(int i = 0; i < m; i++){
        auto p = points[i];
        index[p] = i + 1;
	}

    if(is_up) {
        polarSort(points, p_end, p_end - p_start, 0);
        reverse(all(points));
    } else {
        polarSort(points, p_end, p_start - p_end);
    }
    
    vector<int> perm(m);
    for(int i = 0; i < m; i++) {
        auto p = points[i];
        perm[i] = index[p];
    }

    int MAX_M = m + 20;
    Fenwick *F = new Fenwick();
    F->init(MAX_M);
    lli ans = 0;
    for(int i = 0; i < m; i++) {
        int idx_perm = perm[i];
        ans += F->query(idx_perm);

        F->update(idx_perm, 1);
    }

	return ans;
}

int main () {
	fastIO();
    point p_start, p_end;
    cin>>p_start.x>>p_start.y;
    cin>>p_end.x>>p_end.y;

    int n; cin>>n;
    vector< point > spectators(n);
    for(auto &p: spectators) cin>>p.x>>p.y; 

	vector< point > up, down;
	vector< point > collinear_left, collinear_right;
	for(int i = 0; i < n; i++) {
		auto p = spectators[i];
		auto val = isLeft(p_start, p_end, p);
		if(val == 1) up.push_back(p);
		else if(val == 0) down.push_back(p);
		else {
			if((p - p_start).norm() < (p - p_end).norm()) 
				collinear_left.push_back(p);
			else 
				collinear_right.push_back(p);
		}
	}



	lli ans_up = calc(up, p_start, p_end);
	lli ans_down = calc(down, p_start, p_end, false);

	auto gauss = [](lli n){
		return n*(n+1) / 2;
	};

	cout << ans_up + ans_down + gauss(SZ(collinear_left) - 1) + gauss(SZ(collinear_right) - 1) << endl;
	return 0;
}

