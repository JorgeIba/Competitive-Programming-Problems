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
    
    forn(i, n){
        string s; cin>>s;
        if(s == "and" || s == "not" || s == "that" || s == "the" || s == "you") {
            cout << "Yes" << endl;
            return;
        } 
    }
    cout << "No" << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	
	
	while(t--) main_();


	return 0;
}

