
#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

lli query(int x){
	cout << "- " << x << endl;
	cout.flush();
	lli cnt; cin>>cnt;
	if(cnt == -1 ){
		cout << "ADS" << endl;
		exit(0);
	}
	return cnt;
}




void main_(){
	lli cnt; cin>>cnt;
	

	lli num = 0, zeros_extras = 0;
	for(int i = 0; i <= 29;){
		lli next_query = query((1 << i));
		if(next_query < cnt) {
			num += (1 << i);
			i++;
		} else {
			int diff = next_query - cnt;
			zeros_extras += (diff+1);
			num += (1 << (i + diff + 1));

			i += (diff+2);
		}
		cnt = next_query;
		if(next_query == 0) break;
		if(zeros_extras == next_query) break;
	}

	cout << "! " << num << endl;
	cout.flush();
	
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

