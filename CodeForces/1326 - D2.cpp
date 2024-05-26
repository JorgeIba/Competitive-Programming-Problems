#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

template<typename T> 
vector<int> manacher(const T& s) {
    if(s.empty()) return {};
	int l = 0, r = -1, n = s.size();
	vector<int> d1(n), d2(n);
	for (int i = 0; i < n; i++) {
		int k = i > r ? 1 : min(d1[l+r-i], r-i);
		while (i+k < n && i-k >= 0 && s[i+k] == s[i-k]) k++;
		d1[i] = k--;
		if (i+k > r) l = i-k, r = i+k;
	}
	l = 0, r = -1;
	for (int i = 0; i < n; i++) {
		int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1); k++;
		while (i+k <= n && i-k >= 0 && s[i+k-1] == s[i-k]) k++;
		d2[i] = --k;
		if (i+k-1 > r) l = i-k, r = i+k-1;
	}
	vector<int> ret(2*n-1);
	for (int i = 0; i < n; i++) ret[2*i] = 2*d1[i]-1;
	for (int i = 0; i < n-1; i++) ret[2*i+1] = 2*d2[i+1];
	return ret;
}


void main_(){
    string s; cin>>s;
    int n = SZ(s);

    if(SZ(s) == 1) {
        cout << s << endl;
        return;
    }
    
    int l = 0, r = n-1;
    while(l < r && s[l] == s[r]) l++, r--;


    string t;
    for(int i = l; i <= r; i++) {
        t.push_back(s[i]);
    }

    int sz_t = SZ(t);

    
    auto man = manacher(t);
    
    auto query = [&](int l, int r) {
        return man[l+r] >= (r - l + 1);
    };

    int m = SZ(t);
    int max_i = 0;
    for(int i = 0; i < m; i++) {
        if(query( 0, i )){
            max_i = i;
        }
    }

    int max_j = 0;
    for(int i = m - 1, j = 0; i >= 0; i--, j++){
        if(query(i, m-1)) {
            max_j = j;
        }
    }

    string intermediate;
    if(max_i < max_j) {
        intermediate = t.substr((sz_t - 1) - max_j, max_j+1);
    } else {
        intermediate = t.substr(0, max_i+1);
    }

    cout << s.substr(0, l) << intermediate << s.substr((n-1) - (l-1), l) << endl;
}


int main () {
	// fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

