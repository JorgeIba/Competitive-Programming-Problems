// Problem: B. The String Has a Target
// Contest: Codeforces - Codeforces Round 862 (Div. 2)
// URL: https://codeforces.com/contest/1805/problem/B
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
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


void main_(){
	int n; cin>>n;
	string s; cin>>s;
	
	
	for(char target = 'a'; target <= 'z'; target++){
		for(int i = n-1; i >= 0; i--){
			if(s[i] == target){
				cout << s[i];
				for(int j = 0; j < n; j++){
					if(j == i) continue;
					cout << s[j];
				}
				cout << endl;
				return;
			}
		}		
	}
	

	
	
	cout << s << endl;
	
		
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

