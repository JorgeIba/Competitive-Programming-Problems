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
        while(i + z[i] < n && (s[z[i]] == s[i + z[i]] || s[z[i]] == '?' || s[i+z[i]] == '?'))
            ++z[i];
        if(i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve(){
    int n; cin>>n;
    string s; cin>>s;

    auto zf = z_function(s);

    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if((i+1) + zf[i] == n) ans.push_back(i);
        cout << i << " " << zf[i] << endl;
    }

    for(int d = 1; d <= n; d++) {
        for(int j )
    }

    // cout << SZ(ans) << endl;
    // for(auto x: ans) cout << x << " ";
    // cout << endl;
}


int main () {
	//fastIO();
	
    int t; cin>>t;

    while(t--) solve();


	return 0;
}

