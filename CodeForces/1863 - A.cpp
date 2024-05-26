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
	int n, a, q; cin>>n>>a>>q;
	string s; cin>>s;

	int cnt_plus = count(all(s), '+');
	if(a + cnt_plus < n){
		cout << "NO" << endl;
		return;
	} 


	bool yes = (a + cnt_plus >= n);
	if(!yes){
		cout << "NO" << endl;
		return;
	}

	bool no = true;

	int connected = a;
	forn(i, q){
		if(connected >= n) {
			no = false;
		}
		if(s[i] == '-') connected--;
		else connected++;

		if(connected >= n) {
			no = false;
		}
	}

	// debugg(yes);
	// debugg(no);

	if(yes && no){
		cout << "MAYBE" << endl;
	} else if(!yes && no){
		cout << "NO" << endl;
	} else if(yes & !no){
		cout << "YES" << endl;
	} else {
		assert(false);
	}
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

