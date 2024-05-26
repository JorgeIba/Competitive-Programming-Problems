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
bool isPowerofTwo(lli s){ return (s & (s-1)) == 0; }

void main_(){
    lli n, m; cin>>n>>m;

    n = n % m;
    lli g = gcd(n, m);
    
    if(n == 0){
        cout << 0 << endl;
        return;
    }

    if(!isPowerofTwo(m/g)){
        cout << -1 << endl;
        return;
    }

    lli ans = 0;
    lli total_apples = n;
    while(true){
        if(total_apples < m){
            ans += total_apples;
            total_apples *= 2;
        } else {
            total_apples -= m;
        }
        if(total_apples == 0) break;
    }
    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

