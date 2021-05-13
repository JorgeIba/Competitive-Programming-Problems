#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

struct Trie{
	vector<map<char,int>> trie;
	vi id;
	int cont;
	Trie(int N): trie(N), cont(0), id(N, -2){}
	void add(string& s, int _id){
		int act = 0;
		for(char c : s){
			if(trie[act].find(c) == trie[act].end())
				trie[act][c] = ++cont;
			act = trie[act][c];
			if((id[act] != -2 && id[act] != _id) || id[act] == -1) 
				id[act] = -1;
			else
				id[act] = _id;
		}
	}
	int search(string& s){
		int act = 0;
		for(char c : s){
			if(trie[act].find(c) == trie[act].end())
				return -1;
			act = trie[act][c];
		}
		return id[act];
	}
};
int main(){
	fastIO();
	int T;
	cin >> T;
	while(T--){
		int p, r;
		cin >> p >> r;
		Trie tr(p*40*40);
		forn(i,p){
			int c;
			cin >> c;
			forn(j,c){
				string s;
				cin >> s;
				tr.add(s,i);
			}
		}
		forn(i,r){
			set<int> ans;
			int c;
			cin >> c;
			forn(i,c){
				string s;
				cin >> s;
				int ret = tr.search(s);
				//cout << "id: " << ret << '\n'; 
				if(ret == -1 || ret == -2)
					continue;
				ans.insert(ret);
			}
			cout << ans.size() << '\n';
		}
	}
	return 0;
}

