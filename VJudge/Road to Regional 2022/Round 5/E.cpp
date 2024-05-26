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


vector<lli> getPrefix(const string t, char c) {
    lli n = SZ(t);
    vector<lli> prefix(n);
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            prefix[i] = (t[i] == c ? (i+1) : 0);
        } else {
            prefix[i] = prefix[i-1] + (t[i] == c ? (i+1) : 0);
        }
    }
    return prefix;
}

vector<lli> getSuffix(const string t, char c) {
    lli n = SZ(t);
    vector<lli> suffix(n);
    for(int i = n-1; i >= 0; i--) {
        if(i == n-1) {
            suffix[i] = (t[i] == c ? (n-i) : 0);
        } else {
            suffix[i] = suffix[i+1] + (t[i] == c ? (n-i) : 0);
        }
    }
    return suffix;
}




int main () {
	//fastIO();
	
	lli n; cin>>n;
    string s, t; cin>>s>>t;



    vector<vector<lli>> prefixB(27), suffixB(27);

    for(int i = 0; i < 27; i++) {
        prefixB[i] = getPrefix(t, i+'A');
        suffixB[i] = getSuffix(t, i+'A');
    }

    ld total = (ld)n*(n+1)*(2*n+1) / (6);

    ld ans = 0;
    for(int i = 0; i < n; i++) {
        auto c_a = s[i] - 'A';
        ld ans_i = (1.0 * prefixB[c_a][i] / total) * (n - i);
        ld ans_j = 0;
        if(i+1 < n)
            ans_j = (1.0 * suffixB[c_a][i+1] / total) * (i+1);
        // cout << ans_i << " - " << ans_j << endl;
        ans += ans_i + ans_j;
    }


    

    // cout << ans << " " << total << endl;

    cout << fixed << setprecision(10) << (ld) ans << endl;



	return 0;
}

