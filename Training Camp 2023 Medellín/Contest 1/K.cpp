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

struct Hash {
    lli MOD = 1824261409, P = 53, PI = 1411221090; 
	vector<lli> h,pi;
	Hash(const string& s){
		assert((P*PI)%MOD==1);
		h.resize(s.size()+1);
		pi.resize(s.size()+1);
		h[0] = 0;
		pi[0] = 1;
		lli p = 1;
		forr(i,1,SZ(s)){
			h[i] = (h[i-1] + p*s[i-1]%MOD) %MOD;
			pi[i] = pi[i-1] * PI %MOD;
			p = p*P %MOD;
		}
	}
	//returns the hash of substring [s,e)
	lli get(int s, int e){
		return ((h[e] - h[s] + MOD) % MOD)*pi[s] % MOD;
	}
};



struct TrieNode{
    map<char, TrieNode*> dictionary;
    int howMuchWords = 0;
    int isWord = 0;
    map<lli, lli> frq_suffix;
    vector<pair<int,lli>> queries;
};


const int MAXQ = 2e5+10;
lli ans[MAXQ];

struct Trie{
    TrieNode *root = new TrieNode;
    
    bool exist(TrieNode* curr, char c) {
        return curr->dictionary.count(c);
    }

    void insert(const string &s){
        TrieNode *curr = root;
        curr->howMuchWords++;
        for(auto c: s)
        {
            if(!exist(curr, c))
                curr->dictionary[c] = new TrieNode();
            curr = curr->dictionary[c];
            curr->howMuchWords++;
        }

        Hash H(s);
        for(int i = 0; i < SZ(s); i++){
            curr->frq_suffix[  H.get(i, SZ(s)) ]++;
        }

        curr->isWord++;
    }

    void mark(const string &word, int idx, lli hash){
        TrieNode *curr = root;
        for(auto c: word){
            if(!exist(curr, c)){
                return;
            }
            curr = curr->dictionary[c];
        }
        curr->queries.push_back({idx, hash});
    }

    void go(TrieNode *curr){

        for(auto [c, nextt]: curr->dictionary){
            go(nextt);
            if(SZ(curr->frq_suffix) <  SZ(nextt->frq_suffix)){
                swap(curr->frq_suffix, nextt->frq_suffix);
            }

            for(auto [suff, frq]: nextt->frq_suffix){
                curr->frq_suffix[suff] += frq;
            }
        }

        for(auto [idx, hash_suff]: curr->queries){
            ans[idx] += curr->frq_suffix[hash_suff];
        }
    }


    void Rec(TrieNode *root, const string &s)
    {
        for(auto c: root->dictionary)
        {
            string aux = s;
            aux.push_back(c.first);
            Rec(c.second, aux);
        }
        if(root->isWord)
            cout << s << endl;
    }

    void printWords()
    {
        string aux;
        Rec(root, aux);
    }
};





int main () {
	fastIO();
	
    int n; cin>>n;

    vector< string > ss(n);
    for(auto &s: ss) cin>>s;

    int q; cin>>q;
    assert(q < MAXQ);
    vector<string> pref(q), suff(q);

    forn(i, q){
        cin>>pref[i]>>suff[i];
    }

    Trie T;
    for(auto &s: ss){
        T.insert(s);
    }


    forn(i, q){
        Hash H(suff[i]);
        T.mark(pref[i], i, H.get(0, SZ(suff[i])));
    }


    T.go(T.root);


    forn(i, q){
        cout << ans[i] << endl;
    }


	return 0;
}

