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


void main_(){

    int n; cin>>n;
    string s; cin>>s;

    vector<int> ans(n+1);

    int cnt_diff = 0, cnt_equal = 0;
    int l = 0, r = n-1;
    while(l < r){
        cnt_equal += (s[l] == s[r]);
        cnt_diff  += (s[l] != s[r]);

        l++, r--;
    }


    if(n % 2 == 1){
        for(int i = cnt_diff; i <= n - cnt_diff; i++){
            ans[i] = 1;
        }
        for(auto x: ans) cout << x;
        cout << endl;
    } else {
        for(int i = cnt_diff; i <= n-cnt_diff; i += 2){
            ans[i] = 1;
        }
        for(auto x: ans) cout << x;
        cout << endl;
    }

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

