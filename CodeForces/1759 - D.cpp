// Problem: D. Make It Round
// Contest: Codeforces - Codeforces Round  #834 (Div. 3)
// URL: https://codeforces.com/contest/1759/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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


lli pot(lli n){
	lli pot2 = 0, pot5 = 0;
	while(n > 0 && n % 2 == 0) {
		n /= 2;
		pot2++;
	}
	
	
	while(n > 0 && n % 5 == 0) {
		n /= 5;
		pot5++;
	}
	
	return min(pot2, pot5);
}



int main () {
	fastIO();
	
	int t; cin>>t;
	while(t--) {
		lli n, m; cin>>n>>m;
	
		lli max_pot = -1, max_num = -1;
		lli mult = 1;
		for(lli i = 0; i <= 30; i++) {
			for(lli k = 0; k <= 12; k++) {
				mult = (1LL << i) * pow(5, k);
				
				lli j = m/mult;
				if(j > m) j--;
				

				if(j*mult > m) break;
				
		
				lli cand = n*j*mult;
				auto poti = pot(cand);
                            

				if(poti > max_pot) {
					max_pot = poti;
					max_num = cand;
				} else if(poti == max_pot) {
					max_num = max(max_num, cand);
				}

			}
			

		}
		
		if(pot(max_num) == 0) {
			cout << n*m << endl;
		} else {
			cout << max_num << endl;
		}
			
	}

	return 0;
}

