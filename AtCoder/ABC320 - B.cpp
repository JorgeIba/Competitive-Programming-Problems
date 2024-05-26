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
    string s; cin>>s;
    int ans = 1;
    int n = SZ(s);


    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            string sr = s.substr(i, j-i+1);
            string aux = sr;
            reverse(all(aux));
            if(sr == aux){
                ans = max(ans, SZ(sr));
            }
        }
    }
    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

