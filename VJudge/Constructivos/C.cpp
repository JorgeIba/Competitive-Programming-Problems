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


int main () {
	fastIO();
	
    #define x first
    #define y second


    int n; cin>>n;
    cout << "YES" << endl;
    forn(i, n){
        pair<int,int> p1, p2;
        cin>>p1.x>>p1.y>>p2.x>>p2.y;
        p1.x = (p1.x & 1);
        p1.y = (p1.y & 1);
        cout << (2*p1.x + p1.y + 1) << endl;
    }


	return 0;
}

