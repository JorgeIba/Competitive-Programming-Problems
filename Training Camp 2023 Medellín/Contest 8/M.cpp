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


int fr[55];

int n; 
string f(int x){
    if(fr[x] == 0) return f(x+1);
    if(fr[x] <= n/2) return "Alice";
    return "Bob";
}


int main () {
	//fastIO();
	
    cin>>n;
    
    forn(i, n){
        int x; cin>>x;
        fr[x]++;
    }


    cout << f(1) << endl;



	return 0;
}

