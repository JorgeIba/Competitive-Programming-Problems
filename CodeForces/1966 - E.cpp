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

void main_() {
    int n; cin>>n;
    string s; cin>>s;


    string t;
    for(int i = 0; i < n; ) {
        int j = i;
        while(j < n && s[i] == s[j]) {
            j++;
        }
        if((j-i) % 2 == 1) {
            t.push_back(s[i]);
        } else {
            t.push_back(s[i]);
            t.push_back(s[i]);
        }

        i = j;
    }

    n = SZ(t);
    // cout << t << endl;
    int l = 0, r = 0;
    int dir = 1;
    int curr = 0;
    for(int i = 0; i < n-1; i++, curr += dir) {
        // debugg(curr);
        l = min(l, curr);
        r = max(r, curr);

        if(t[i] == t[i+1]) {
            curr += dir;
            dir *= -1;
        }
    }

    // debugg(curr);
    l = min(l, curr);
    r = max(r, curr);
    

    cout << r - l + 1 << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

