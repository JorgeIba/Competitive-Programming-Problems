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

    string s, t; cin>>s>>t;
    int n = SZ(s);

    if(s == t){
        cout << "YES" << endl;
        return;
    }

    set<int> indx_00;
    for(int i = 0; i < n; i++) {
        if(s[i] == t[i] && s[i] == 0 + '0') indx_00.insert(i);
    }

    for(int i = n-1; i >= 0; i--){
        if(s[i] == t[i] && s[i] == 1 + '0'){
            if(indx_00.count(i-1)){
                cout << "YES" << endl;
                return;
            }
        }
    }

    cout << "NO" << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

