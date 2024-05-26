

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
	int n, k, d, w; cin>>n>>k>>d>>w;
	
	vector<int> times(n);
	for(auto &x: times) cin>>x;

	lli ans = 0;
	lli last_day = -1, left = 0;
	for(auto day: times){
		if(left == 0 || last_day < day) {
			ans++;
			left = k;
			last_day = day + d + w; 
		}
		
		left--;
	}
	cout << ans << endl;
		
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

