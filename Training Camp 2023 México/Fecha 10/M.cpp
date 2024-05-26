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

vector<int> z_function(const string & s){
    int n = s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; ++i){
        if(i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if(i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

template<typename T> 
vector<int> manacher(const T& s) {
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

int main () {
	fastIO();
	
	string s, t; cin>>s>>t;
    int n = SZ(s), m = SZ(t);

    reverse(all(s));

    vector<int> how_many(n+1);
    auto man_s = manacher(s);
    
    for(int i = 0; i < SZ(man_s); i++) {
        int mx_pal =  man_s[i];
        if(i & 1) {
            // int pos_l = (i - 1) / 2;
            int pos_r = (i + 1) / 2;

            // int l = pos_l - mx_pal/2 + 1;
            int r = pos_r + mx_pal/2 - 1;
            how_many[pos_r]++;
            how_many[r+1]--;

        } else {
            int pos = i / 2;
            // int l = pos - (mx_pal - 1) / 2;
            int r = pos + (mx_pal - 1) / 2;
            how_many[pos]++;
            how_many[r + 1]--;
        }
    }


    partial_sum(all(how_many), how_many.begin());

    auto z_f = z_function(t + "$" + s);

    lli ans = 0;
    for(int i = 0; i < SZ(s); i++) {
        if( z_f[i + (m + 1)] ) {
            ans += 1LL*(z_f[i + (m+1)]) * ((i ? how_many[i-1] : 0));
        }
    }

    cout << ans << endl;

	return 0;
}

