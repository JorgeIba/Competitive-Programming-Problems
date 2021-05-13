#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;
 
typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

int k;
string s;

bool is_digit(char c){
	return '0' <= c && c <= '9';
}

string solve(){
	int i = 0;
	string ans;
	lli tot_len = 0;
	while(i < s.size()){
		string aux;
		while(is_digit(s[i])){
			aux.pb(s[i]);
			i++;
		}
		char curr = s[i];
		lli len = 0;
		if(aux.empty())
			len++;
		else if(aux.size() > 6)
			return "unfeasible";
		else
		{
			lli x = stoll(aux);
			len = x;
		}
		tot_len += len;
		if(tot_len > k)
			return "unfeasible";
		forn(j,len)
			ans.pb(curr);
		i++;
	}
	return ans;
}

int main () {
	fastIO();
	int t;
	cin >> t;
	while(t--){
		cin >> s >> k;
		cout << solve() << endl;
	}
	return 0;
}
