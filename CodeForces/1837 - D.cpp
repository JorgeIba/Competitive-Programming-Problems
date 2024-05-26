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


bool can_in_one(string s) {
    int cnt = 0;
    for(auto c: s) {
        if(c == '('){
            cnt++;
        } else {
            cnt--;
        }
        if(cnt < 0) return false;
    }
    return true;
}


void main_(){
	int n; cin>>n;
    string s; cin>>s;

    int cnt_open = count(all(s), '(');
    int cnt_close = count(all(s), ')');

    if(cnt_open != cnt_close) {
        cout << -1 << endl;
        return;
    }

    auto reversed = s;
    reverse(all(reversed));
    if(can_in_one(s) || can_in_one(reversed)) {
        cout << 1 << endl;
        forn(i, n) cout << 1 << " ";
        cout << endl;
        return;
    }

    int ok = 0, rev = 0;
    vector<int> v_ok, v_rev;
    for(int i = 0; i < n; i++) {
        auto c = s[i];

        if(c == '('){
            if(rev < 0) {
                v_rev.push_back(i);
                rev++;
            } else {
                v_ok.push_back(i);
                ok++;
            }
        } else {
            if(ok > 0) {
                v_ok.push_back(i);
                ok--;
            } else {
                v_rev.push_back(i);
                rev--;
            }
        }
    }

    cout << 2 << endl;
    vector<int> colors(n, 2);
    for(auto x: v_ok) colors[x] = 1;
    
    for(auto x: colors) cout << x << " ";
    cout << endl;


}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

