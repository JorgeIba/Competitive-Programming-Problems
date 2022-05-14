#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


// sum of floor((a*i+b)/m) , 0<=i<=n
lli f(lli a, lli b, lli c, lli n){
	lli m = (a*n + b)/c;
	if(n==0 || m==0) return b/c;
	if(n==1) return b/c + (a+b)/c;
	if(a<c && b<c) return m*n - f(c, c-b-1, a, m-1);
	else return (a/c)*n*(n+1)/2 + (b/c)*(n+1) + f(a%c, b%c, c, n);
}



void solve(){
    lli p, q, n; cin>>p>>q>>n;

    lli suma = p*(n*(n+1)/2);

    lli other_sum = f(p, 0, q, n);
    /*
    for(lli i = 1; i <= n; i++) {
        other_sum += (p*i/q);
    }*/
    cout << suma - other_sum*q << endl;

}


int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

