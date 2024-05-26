// Problem: A. Hayato and School
// Contest: Codeforces - Codeforces Round #846 (Div. 2)
// URL: https://codeforces.com/contest/1780/problem/0
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n; cin>>n;

	vector<int> odds, evens;
	for(int i = 0; i < n; i++){
		int x; cin>>x;
		if(x & 1) odds.push_back(i+1);
		else evens.push_back(i+1);
	}
	
	
	if(SZ(evens) == 0) {
		cout << "YES" << endl;
		cout << odds[0] << " " << odds[1] << " " << odds[2] << endl;
	} else if(SZ(evens) == 1){
		if(SZ(odds) >= 3) {
			cout << "YES" << endl;
			cout << odds[0] << " " << odds[1] << " " << odds[2] << endl;
		} else {
			cout << "NO" << endl;			
		}
	} else {
		if(SZ(odds) >= 1) {
			cout << "YES" << endl;
			cout << evens[0] << " " << evens[1] << " " << odds[0] << endl;
		}  else {
			cout << "NO" << endl;
		}
	}
	
	
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

