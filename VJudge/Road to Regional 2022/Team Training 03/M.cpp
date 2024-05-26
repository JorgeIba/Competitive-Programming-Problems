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



int main () {
	//fastIO();

    int n; cin>>n;
    string s, t; cin>>s>>t;

    auto doble_tt = t + t;

    auto glued = s+ "$" + doble_tt;
    auto zf = z_function(glued);

    int max_ans = 0, idx_ans = 0;

    for(int i = SZ(s) + 1; i < SZ(glued); i++) {
        if(zf[i] > max_ans) {
            max_ans = zf[i];
            idx_ans = i;
        }
    }

    cout << idx_ans - (SZ(s) + 1) << endl;


	return 0;
}

