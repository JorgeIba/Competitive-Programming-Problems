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
    bool isWord=false, isLeaf = false;
    bool win = false, lose = false;
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
        //curr->isLeaf = true;
    }

    lli search(const string &word)
    {
        TrieNode *curr = root;
        lli ans = -1;
        for(auto c: word)
        {
            //curr->isLeaf = false;
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

//const lli maxN = 1e5+10;
//bool win[maxN], lose[maxN];

void dfs(TrieNode* u)
{
    u->isLeaf = true;
    for(auto x: u->dictionary)
    {
        u->isLeaf = false;
        dfs(x.second);
        u->win = u->win || (!(x.second->win));
        u->lose = u->lose || (!(x.second->lose));
    }
    if(u->isLeaf)
    {
        u->win = false;
        u->lose = true;
        return;
    }
}

int main()
{
    fastIO();
    lli n, k; cin>>n>>k;
    Trie T;
    for(int i = 0; i<n; i++){
        string s; cin>>s;
        T.insert(s);
    }

    dfs(T.root);
    
    cerr << T.root->win << " " << T.root->lose << endl;

    if(T.root->win && T.root->lose)
    {
        cout << "First\n";
    }
    else if(T.root->win && !(T.root->lose))
    {
        cout << (k&1==1?"First":"Second") << endl;
    }
    else if(!(T.root->win) && (T.root->lose))
    {
        cout << "Second\n";
    }
    else
    {
        cout << "Second\n";
    }

    return 0;
}