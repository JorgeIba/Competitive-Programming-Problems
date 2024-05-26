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
	int n; cin>>n;
	vector<int> A(n), B(n);
	for(auto &x: A) cin>>x;
	for(auto &x: B) cin>>x;
	
	if(A.back() >= B.back()) {

	} else{
		swap(A[n-1], B[n-1]);
	}
	
	for(int i = 0; i < n; i++){
		if(A[i] < B[i]) swap(A[i], B[i]);	
	}	
	
	lli maxi_A = *max_element(all(A));
	lli maxi_B = *max_element(all(B));
	
	if(maxi_A <= A.back() && maxi_B <= B.back()) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

