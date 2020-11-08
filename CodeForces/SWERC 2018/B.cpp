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
 
using namespace std;
 
typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

template<class T, class compare>
struct monotonic_queue{
	deque<pair<T,int>> Q;
	int cnt_added = 0;
	int cnt_removed = 0;
	int _size = 0;
	void push(T x){
		while(!Q.empty() && compare()(x,Q.back().first))
			Q.pop_back();
		Q.push_back({x,cnt_added});
		cnt_added++;
		_size++;
	}
	void pop(){
		if(!Q.empty() && Q.front().second == cnt_removed)
			Q.pop_front();
		cnt_removed++;
		_size--;
	}
	//returns the minimum/maximum element in the queue
	T monotonic(){
		return Q.front().first;
	}
	int size(){ return _size; }
	void clear(){
		Q.clear();
		cnt_added = 0;
		cnt_removed = 0;
		_size = 0;
	}
};

int n;
vpii ranges;

bool check(int x){
	monotonic_queue<int,greater_equal<int>> left;
	monotonic_queue<int,less_equal<int>> right;
	int i;
	for(i = 0; i<x-1; i++){
		left.push(ranges[i].fi);
		right.push(ranges[i].se);
//		cout << "l: " << left.monotonic() << " r: " << right.monotonic() << endl;
	}
	while(i < n){
		left.push(ranges[i].fi);
		right.push(ranges[i].se);
		int l = left.monotonic();
		int r = right.monotonic();
//		cout << "l: " << l << " r: " << r << endl;
		if(r-l+1 >= x)
			return true;
		left.pop();
		right.pop();
		i++;
	}
	return false;
}

int solve(){
	int l,r,m;
	l = 1; r = n;
//	cout << "check(n): " << check(n) << endl;
	while(l<r){
		m = (l+r+1)/2;
		if(check(m))
			l = m;
		else
			r = m-1;
	}
	return l;
}

int main () {
	fastIO();
	cin >> n;
	ranges.resize(n);
	forn(i,n){
		cin >> ranges[i].fi >> ranges[i].se; 
	}
	cout << solve() << endl;
	return 0;
}
