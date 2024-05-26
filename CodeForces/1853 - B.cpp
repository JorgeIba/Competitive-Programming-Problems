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
    int n, k; cin>>n>>k;

    lli ans = 0;
    for(int i = 1; i <= n; i++){
        int x = i;
        int y = n;
        bool ok = true;
        for(int j = k-2; j >= 1; j--){
            int aux = y - x;
            if(aux < 0 || aux > x){
                ok = false;
                break;
            }
            y = x;
            x = aux;
        }

        ans += ok;
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

