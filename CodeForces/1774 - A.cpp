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
	string s; cin>>s;
	
	int ones = count(all(s), '1');
	int half = ones / 2;
	int other_half = ones - half;
	
	string ans(n-1, '+');
	for(int i = 0; i < n-1; i++){
		if(s[i+1] == '1' && half) {
			ans[i] = '-';
			half--;
		}else if(s[i+1] == '1' && other_half){
			assert(other_half);
			ans[i] = '+';
			other_half--;
		}
		
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

