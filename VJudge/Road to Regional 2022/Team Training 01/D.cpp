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

// sum of floor((a*i+b)/m) , 0<=i<=n
lli f(lli a, lli b, lli c, lli n){
	lli m = (a*n + b)/c;
	if(n==0 || m==0) return b/c;
	if(n==1) return b/c + (a+b)/c;
	if(a<c && b<c) return m*n - f(c, c-b-1, a, m-1);
	else return (a/c)*n*(n+1)/2 + (b/c)*(n+1) + f(a%c, b%c, c, n);
}


void main_(){

    lli n, m, r; cin>>n>>m>>r;

    lli ans = 0;
    for(int k = 0; k < 32; k++){
        lli upper = (n - r) / m;
        lli sum_left = f(m, r, 1LL << k, upper);
        lli sum_right = f(m, r, 1LL << (k+1), upper);
        ans += sum_left - 2*sum_right;
    }

    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

