#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef int lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

struct node{
	lli val, lazy;
	node *left, *right;
	node(){
		val = lazy = 0;
		left = right = NULL;
	}
	void extend(int l, int r){
		if(left == NULL && l != r){
			left = new node();
			right = new node();
		}
	}
	void propagate(int l, int r, lli x){
		val += x;
		extend(l, r);
		if(l != r){
			 left->lazy += x;
			 right->lazy += x;
		}
	}
};

lli merge(lli a, lli b) {return max(a, b);}

void update(node* curr, int l, int r, int ini, int fin, lli x){
	if(curr->lazy){
		curr->propagate(ini, fin, curr->lazy);
		curr->lazy = 0;
	}
	if(ini > r || fin < l) return;
	if(l <= ini && fin <= r){
		curr->propagate(ini, fin, x);
		return;
	}
	curr->extend(ini, fin);
	int m = (ini + fin) / 2;
	update(curr->left, l, r, ini, m, x);
	update(curr->right, l, r, m + 1, fin, x);
	curr->val = merge(curr->left->val, curr->right->val);
}

lli query(node* curr, int l, int r, int ini, int fin){
	if(curr->lazy){
		curr->propagate(ini, fin, curr->lazy);
		curr->lazy = 0;
	}
	if(ini > r || fin < l) return 0;
	if(l <= ini && fin <= r){
		return curr->val;
	}
	curr->extend(ini, fin);
	int m = (ini + fin) / 2;
	return merge(query(curr->left, l, r, ini, m), query(curr->right, l, r, m + 1, fin));
}

int main () {
	fastIO();
	int n, k;
	cin >> n >> k;
	node* st = new node();
	vpii v;
	set<int> s;
	map<int,int> id;
	int ans = 0;
	s.insert(0);
	s.insert(k - 1);
	forn(i, n){
		int l, r;
		cin >> l >> r;
		if(r - l + 1 >= k){
			ans++;
			continue;
		}
		v.pb({0, 0});
		v.back().fi = l % k;
		v.back().se = r % k;
		s.insert(v.back().fi);
		s.insert(v.back().se);
	}
	for(auto i:s) id[i] = id.size();
	forn(i, SZ(v)){
		int l, r;
		l = id[v[i].fi];
		r = id[v[i].se];
		/* if(r - l + 1 >= k){ */
		/* 	update(st, 0, k - 1, 0, k - 1, 1); */
		/* } */
		/* else{ */
			/* l = l % k; */
			/* r = r % k; */
			if(v[i].fi <= v[i].se) update(st, l, r, id[0], id[k - 1], 1);
			else{
				update(st, l, id[k - 1], id[0], id[k - 1], 1);
				update(st, id[0], r, id[0], id[k - 1], 1);
			}
		/* } */
	}
	/* cout << var(ans) << endl; */
	cout << ans + query(st, id[0], id[k - 1], id[0], id[k -1]) << endl;
	return 0;
}
 