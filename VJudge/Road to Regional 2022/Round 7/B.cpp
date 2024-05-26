#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
    lli n; cin>>n;
    lli odds = 0, evens = 0;

    for(int i = 0; i < n; i++){
        lli x; cin>>x;
        if(x % 2) odds++;
        else evens++;
    }

    if(odds % 2 == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

