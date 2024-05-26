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
	//fastIO();
	
    lli a, b; cin>>a>>b;
    lli ans = 0;

    while(a != b){
        if(b > a) swap(a, b);

        lli q = a / b;
        if(a % b == 0){
            q--;
        }

        ans += q;
        a -= q*b;
    }
    cout << ans+1 << endl;

	return 0;
}

