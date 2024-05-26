// Problem: B. Stand-up Comedian
// Contest: Codeforces - Educational Codeforces Round 142 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1792/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

	vector< int > jokes(4);
	cin>>jokes[0]>>jokes[1]>>jokes[2]>>jokes[3];
	
	
	// FIRST 11
	lli alice = 0, bob = 0;
	alice += jokes[0];
	bob += jokes[0];
	lli ans = jokes[0];
	jokes[0] = 0;
	
	debugg(ans);
	debugg(alice);
	debugg(bob);
	
	// If one is already dead
	if(alice == 0 && bob == 0){
		if(jokes[1] || jokes[2] || jokes[3]) {
			ans++;
			cout << ans << endl;
			return;
		}
	}
	
	//THEN 10 and 01
	lli mini = min(jokes[1], jokes[2]);
	ans += 2*mini;
	jokes[1] -= mini;
	jokes[2] -= mini;
	
	// Lefts
	lli rests = max(jokes[1], jokes[2]);

	if(jokes[1] == rests) {
		lli how_much = min(rests, bob+1);
		
		ans += how_much;
		
		jokes[1] -= how_much;
		bob -= how_much;
		
		if(bob == -1) {
			cout << ans << endl;
			return;
		}
		
		
	} else {
		lli how_much = min(rests, alice+1);
		
		ans += how_much;
		
		jokes[2] -= how_much;
		alice -= how_much;
		
		if(alice == -1) {
			cout << ans << endl;
			return;
		}	
	}

	
	if(alice == -1 || bob == -1) {
		cout << ans << endl;
		return;
	}
	
	
	rests = jokes[3];
	lli mini_mood = min(alice, bob);
	lli how_much = min(mini_mood+1, rests);


	ans += how_much;
	
	cout << ans << endl;
	return;
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

