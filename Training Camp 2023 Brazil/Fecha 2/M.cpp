#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


int main () {
	//fastIO();
	
    string a, b; cin>>a>>b;

    int x = count(all(a), 'S');
    int y = count(all(b), 'S');

    int ans = x * y;
    if(ans == 0) {
        cout << 0 << endl;
    } else {
        string ans_s;
        for(int i = 0; i < ans; i++) {
            ans_s += "S(";
        }
        ans_s += '0';
        for(int i = 0; i < ans; i++) {
            ans_s += ')';
        }
        cout << ans_s << endl;
    }

	return 0;
}

