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


void solve(){
	lli n, k, x; cin>>n>>k>>x; x--;

	string s; cin>>s;

	vector<lli> segments;
	lli cnt = 0;
	for(auto c: s)
	{
		if(c == '*') cnt++;
		else if(cnt > 0){
			segments.push_back(cnt);
			cnt = 0;
		}
	}
	if(cnt > 0) segments.push_back(cnt);

	reverse(all(segments));
	vector<lli> ans;
	
	for(auto how_many: segments){
		lli how_many_need = x % (how_many*k+1);
		x /= (how_many*k+1);
		ans.push_back(how_many_need);
	}

	reverse(all(ans));

	string s_ans;
	cnt = 0;
	lli idx_segment = 0;
	for(auto c: s)
	{
		if(c == '*') cnt++;
		else{
		
			if(cnt > 0){
				s_ans += string(ans[idx_segment++], 'b');
				cnt = 0;
			}
			s_ans.push_back('a');
		}
	}
	if(cnt > 0) s_ans += string(ans[idx_segment++], 'b');

	cout << s_ans << endl;
}



int main () {
	fastIO();
	lli t; cin>>t;

	while(t--) solve();



	return 0;
}

