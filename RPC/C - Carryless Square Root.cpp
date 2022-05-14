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


vector<lli> INF =  {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};


vector<lli> carryLessMult(const vector<lli> &a) {
	int n = SZ(a);
	if(!n) return {};
	vector<lli> c(2*n-1);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) {
			c[i+j] += a[i] * a[j];
			c[i+j] %= 10;
		}
	}
	return c;
}

string passToString(const vector<lli> &a) {
	int n = SZ(a);
	string num(n,'0');
	for(int i = 0; i < n; i++)
		num[i] = a[i] + '0';
	return num;
}

vector<lli> passToVector(const string &a) {
	int n = a.length();
	vector<lli> num(n);
	for(int i = 0; i < n; i++)
		num[i] = a[i] - '0';
	return num;
}

bool checkLower(const vector<lli> &a, const vector<lli> &b) {
	int n = SZ(a), m = SZ(b);
	if(n < m){
		return true;
	} else if(n > m) {
		return false;
	} else {
		return a < b;
	}
}

bool checkIfSuffix(const vector<lli> &a, const vector<lli> &b, int suffix_idx) {
	int n = SZ(a), m = SZ(b);
	for(int i = n-1, j = m-1; j >= suffix_idx ; i--, j--) {
		if(a[i] != b[j]) {
			return false;
		}
	}
	return true;
}


vector<lli> f(int suffix_idx, vector<lli> ans, vector<lli> &target) {
	auto transform = carryLessMult(ans);

	if(SZ(transform) > SZ(target)) {
		return INF;
	} else if( SZ(transform) == SZ(target) ) {
		if(transform == target) {
			return ans;
		} else {
			return INF;
		}
	} else {
		if( checkIfSuffix(transform, target, suffix_idx)  ) {
			// seguimos
		} else {
			return INF;
		}
	}


	auto current_ans = INF;

	for(int i = 0; i <= 9; i++) {
		auto copy_ans = ans;
		copy_ans.insert(copy_ans.begin(), i);
		auto go = f(suffix_idx-1, copy_ans, target);
		if( checkLower(go, current_ans) ){
			current_ans = go;
		}
	}
	return current_ans;
}



int main () {
	//fastIO();

	string num_s; cin>>num_s;
	int n = num_s.length();
	auto num = passToVector(num_s);

	

	auto ans = f(n, {}, num);
	
	if(ans == INF) {
		cout << -1 << endl;
	} else {
		cout << passToString(ans) << endl;
	}

	return 0;
}

