#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){

    int n; cin>>n;

    auto check = [&](const string &s) {
        int m = SZ(s);
        for(int i = 0; i < m-1; i++){
            if(s[i] == 'C' && s[i+1] == 'D') {
                return true;
            }
        }
        return false;
    };

    int ans = 0;
    for(int i = 0; i < n; i++){
        string s; cin>>s;
        ans += (!check(s));
    }
    cout << ans << endl;


}



int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

