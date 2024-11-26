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

int main () {
    // fastIO();

    string s; cin>>s;
    int k; cin>>k;

    int n = SZ(s);
    string ans(n, '.');

    for(int i = 0; i < k; i++) {
        vector<char> cs;
        for(int j = i; j < n; j += k) {
            cs.push_back(s[j]);
        }
        sort(all(cs));
        for(int j = i, l = 0; j < n; j += k, l++) {
            ans[j] = cs[l];
        }
    }

    cout << ans << endl;

	return 0;
}

