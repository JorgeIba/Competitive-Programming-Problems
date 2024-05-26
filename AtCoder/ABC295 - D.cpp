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

    vector<int> curr(10);

    map< vector<int>, int > fr;
    fr[curr]++;


    lli ans = 0;
    for(int i = 0; i < SZ(s); i++){
        int d = s[i] - '0';
        curr[d] = (curr[d] + 1) % 2;
        
        ans += (fr[curr]);

        fr[curr]++;
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

