#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct TrieNode
{
    map< char, TrieNode* > dictionary;
    lli howMuch = 0;
    bool isWord=false;
};

struct Trie
{
    TrieNode *root = new TrieNode;
    
    void insert(const string &s)
    {
        TrieNode *curr = root;
        int index = 0;
        for(auto c: s)
        {
            if(curr->dictionary.find(c) == curr->dictionary.end())
                curr->dictionary[c] = new TrieNode();
            curr = curr->dictionary[c];
            curr->howMuch++;
        }
        curr->isWord = true;
    }

    lli search(const string &word)
    {
        TrieNode *curr = root;
        lli ans = -1;
        for(auto c: word)
        {
            if(curr->dictionary.find(c) == curr->dictionary.end())
            {
                return 0;
            }
            curr = curr->dictionary[c];
            ans = curr->howMuch;
        }
        return ans;
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

int main()
{
    fastIO();
    lli n, q; cin>>n>>q;
    Trie T;

    while(n--)
    {
        string s; cin>>s;
        T.insert(s);
    }
    while(q--)
    {
        string prefix; cin>>prefix;
        cout << T.search(prefix) << endl;
    }
    
    return 0;
}