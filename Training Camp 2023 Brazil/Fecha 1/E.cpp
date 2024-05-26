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
#define var(x) #x << " = " << x

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

struct Node{
	vi idxs;
	int childs[30];
};

const int MAXN = 100*100 + 10;

Node Trie[MAXN];
int _size = 1;
bool vis[105][MAXN];

void push(string cad, int idx){
	int act = 0;
	forn(i, cad.size()){
		if(Trie[act].childs[cad[i]-'a'] != 0){
			act = Trie[act].childs[cad[i]-'a'];
		}
		else{
			Trie[act].childs[cad[i]-'a'] = _size++;
			act = Trie[act].childs[cad[i]-'a'];
		}
	}
	Trie[act].idxs.pb(idx);
}

void find(int idx, int act, const string& cad, vi& ans){
	if(vis[idx][act]) return;
	vis[idx][act] = true;
	if(idx >= cad.size()){
		for(auto i:Trie[act].idxs)
			ans.pb(i);
		return;
	}
	if(cad[idx] == '*'){
		forr(i, 'a', '{'){
			int nxt = Trie[act].childs[i-'a'];
			if(nxt != 0){
				find(idx, nxt, cad, ans);
				find(idx + 1, nxt, cad, ans);
			}
		}
		find(idx + 1, act, cad, ans);
	}
	else{
		if(Trie[act].childs[cad[idx] - 'a'] != 0)
			find(idx + 1, Trie[act].childs[cad[idx] - 'a'], cad, ans);
	}
}

int main () {
	fastIO();
	string p, re;
	cin >> p;
	for(auto c:p){
		if(c == '.')
			re += "{";
		else
			re += c;
	}
	/* cout << re << endl; */
	int n;
	cin >> n;
	vector<string> texts;
	forn(i, n){
		string s;
		cin >> s;
		texts.pb(s);
		forn(i, s.size()){
			if(s[i] == '.')
				s[i] = '{';
		}
		push(s, i);
	}
	vi ans;
	find(0, 0, re, ans);
	sort(all(ans));
	for(auto i:ans) cout << texts[i] << endl;
	return 0;
}

