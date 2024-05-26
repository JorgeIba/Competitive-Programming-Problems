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
    if(n <= 3) {
        cout << -1 << endl;
        return;
    }

    vector<int> ans(n);
    int blocks = n / 4;
    int start = 1;
    for(int j = 0; j < blocks-1; j++, start += 4){
        ans[4*j] = start + 1;
        ans[4*j+1] = start + 3;
        ans[4*j+2] = start;
        ans[4*j+3] = start + 2;
    }    

    int last = blocks-1;
    if(n % 4 == 0){
        ans[4*last]   = start + 1;
        ans[4*last+1] = start + 3;
        ans[4*last+2] = start;
        ans[4*last+3] = start + 2;
    } else if(n % 4 == 1) {
        ans[4*last]   = start + 1;
        ans[4*last+1] = start + 3;
        ans[4*last+2] = start;
        ans[4*last+3] = start + 2;
        ans[4*last+4] = start + 4;
    }
    else if(n % 4 == 2){
        ans[4*last]   = start;
        ans[4*last+1] = start + 3;
        ans[4*last+2] = start + 1;
        ans[4*last+3] = start + 5;
        ans[4*last+4] = start + 2;
        ans[4*last+5] = start + 4;
    } else {
        ans[4*last]   = start;
        ans[4*last+1] = start + 4;
        ans[4*last+2] = start + 2;
        ans[4*last+3] = start + 6;
        ans[4*last+4] = start + 3;
        ans[4*last+5] = start + 1;
        ans[4*last+6] = start + 5;
    }

    forn(i, n-1){
        bool ok = abs(ans[i] - ans[i+1]) >= 2 && abs(ans[i] - ans[i+1]) <= 4;
        assert(ok);
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

