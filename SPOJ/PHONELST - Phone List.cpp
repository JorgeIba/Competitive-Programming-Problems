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

struct TrieNode
{
    map< char, TrieNode* > dictionary;
    lli howMuch = 0;
    bool isWord = false;
};

struct Trie
{
    TrieNode *root = new TrieNode;

    bool exist(TrieNode* curr, char c) {
        return curr->dictionary.count(c);
    }    
    
    bool insert(const string &s)
    {
        TrieNode *curr = root;
        bool isNew = false;
        bool flag = true;
        for(auto c: s)
        {
            if(!exist(curr, c)) {
                isNew = true;
                curr->dictionary[c] = new TrieNode();
            }
                
            curr = curr->dictionary[c];
            curr->howMuch++;

            if(curr->isWord) flag = false;
        }

        if(!isNew) flag = false;

        curr->isWord = true;
        return flag;
    }
};



int main () {
	//fastIO();

    lli t; cin>>t;

    while(t--) {
        lli n; cin>>n;

        Trie *root = new Trie();

        bool flag = true;
        for(int i = 0; i < n; i++) {
            string s; cin>>s;
            if( !root->insert(s) )
                flag = false;
        }

        cout << (flag ? "YES" : "NO") << endl;

    }

	return 0;
}

