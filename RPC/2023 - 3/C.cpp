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

struct TrieNode {
	map<char,TrieNode*> dictionary;
	int howMuchWords = 0;
	int isWord = 0;
};

struct Trie{
	TrieNode *root = new TrieNode();
	bool exist(TrieNode* curr, char c){
		return curr->dictionary.count(c);
	}
	void insert(const string& s){
		TrieNode* curr = root;
		curr->howMuchWords++;
		for(auto c:s){
			if(!exist(curr, c))
				curr->dictionary[c] = new TrieNode();
			curr = curr->dictionary[c];
			curr->howMuchWords++;
		}
		curr->isWord++;
	}
	int find(const string& s){
		return find(root, 0, s);
	}
	int find(TrieNode* curr, int i, const string& s){
		/* cout << var(i) << endl; */
		if(i >= SZ(s)) return curr->isWord;
		int ans = 0;
		if(s[i] == '?'){
			forr(c, '0', '9'){
				if(exist(curr, c))
					ans += find(curr->dictionary[c], i + 1, s);
			}
		}
		else{
				if(exist(curr, s[i]))
					ans += find(curr->dictionary[s[i]], i + 1, s);
		}
		return ans;
	}
};

map<plli,lli> cnt[10][10];

void add(const string& s){
	vlli pref(SZ(s) + 1, 0);
	forn(i, SZ(s)){
		lli aux = 10 * pref[i];
		pref[i + 1] = aux + (s[i] - '0');
	}
	vlli suf(SZ(s) + 1, 0);
	for(lli i = SZ(s) - 1, pot = 1; i >= 0; i--){
		lli aux = suf[i + 1];
		suf[i] = pot * (s[i] - '0') + aux;
		pot *= 10;
	}
	forr(i, 0, SZ(s)){
		forr(j, 0, SZ(s)){
			/* cout << var(i) << ' ' << var(j) << " -> " << pref[i - 1] << ' ' << suf[j - 1] << endl; */
			cnt[i][j][{pref[i], suf[SZ(s) - (j)]}]++;
		}
	}
}

int main () {
	fastIO();
	int n;
	cin >> n;
	Trie trie;
	set<string> words;
	forn(i, n){
		string s;
		cin >> s;
		trie.insert(s);
		add(s);
		words.insert(s);
	}
	int q;
	cin >> q;
	while(q--){
		string s;
		cin >> s;
		int type = 0;
		for(auto c:s){
			if(c == '?') type = 1;
			if(c == '*') type = 2;
		}
		if(type == 1){
			cout << trie.find(s) << endl;
		}
		else if(type == 2){
			lli pref = 0;
			lli suf = 0;
			int len_p = 0;
			int len_s = 0;
			bool flg = false;
			forn(i, SZ(s)){
				char c = s[i];
				if(c == '*'){
					flg = true;
					continue;
				}
				if(!flg){
					pref *= 10;
					pref += (c - '0');
					len_p++;
				}
				if(flg){
					suf *= 10;
					suf += (c - '0');
					len_s++;
				}
			}
			/* cout << var(len_p) << ' ' << var(len_s) << endl; */
			/* cout << var(pref) << ' ' << var(suf) << endl; */
			cout << cnt[len_p][len_s][{pref, suf}] << endl;
		}
		else{
			cout << words.count(s) << endl;
		}
	}
	return 0;
}

