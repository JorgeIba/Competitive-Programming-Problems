#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


void main_(){
	int n; cin>>n;
    if(n <= 6) {
        cout << "NO" << endl;
        return;
    }

    if(n % 3 != 0) {
        cout << "YES" << endl;
        cout << 1 << " " << 2 << " " << (n - 3) << endl;
    } else {
        if(n == 9) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            if(n == 12){
                cout << 1 << " " << 4 << " " << 7 << endl;
            } else {
                cout << 2 << " " << 5 << " " << (n-7) << endl;
            }
        }
    }

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

