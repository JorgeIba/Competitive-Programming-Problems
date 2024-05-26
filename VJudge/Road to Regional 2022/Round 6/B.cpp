#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void main_(){
    lli n; cin>>n;
    vector<lli> A(n, 1e18), B(n-1);

    for(auto &x: B) cin>>x;

    for(int i = 0; i < n-1; i++) {
        lli b = B[i];
        A[i] = min(A[i], b);
        A[i+1] = min(A[i+1], b);
    }


    lli sum = 0;
    for(auto x: A) sum += x;
    cout << sum << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

