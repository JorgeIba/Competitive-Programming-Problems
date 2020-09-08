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
    map< string, lli > howMuch;
    lli maximum=0;
    string stringMax;
    bool isWord=false;
};
 
map<pair<lli,lli>, string> deshash;
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
            curr->howMuch[s]++;
            lli how = curr->howMuch[s];
            if(how > curr->maximum)
            {
                curr->maximum = how;
                curr->stringMax = s;
            }
            else if(how == curr->maximum)
            {
                if( curr->stringMax > s )
                {
                    curr->stringMax = s;
                }
            }
            //curr->howMuch++;
        }
        curr->isWord = true;
    }
 
    pair<lli,string> search(const string &word)
    {
        TrieNode *curr = root;
        for(auto c: word)
        {
            if(curr->dictionary.find(c) == curr->dictionary.end())
            {
                return {-1, "-1"};
            }
            curr = curr->dictionary[c];
            //ans = curr->howMuch;
        }
        return {curr->maximum, curr->stringMax};
    }
};
 
/*
lli getHash(string &s, lli p, lli MOD)
{
    lli hash = p;
    for(char c: s)
    {
        assert((c-'0'+1) > 0);
        hash = ((hash*p)%MOD + (c-'0'+ 1))%MOD;
    }
    return hash;
}
*/
 
//map<string, lli> hash;
 
int main()
{
    fastIO();
    lli n; cin>>n;
    Trie T;
    for(int i = 0; i<n; i++)
    {  
        string s; cin>>s;
        pair<lli,lli> hashes;
        //hashes.first = getHash(s, 37, 1e8+7);
        //hashes.second = getHash(s, 31, 1e9+7);
        //deshash[hashes] = s;
        //T.insert(s, hashes);
        T.insert(s);
    }
 
    lli q; cin>>q;
    while(q--)
    {
        string pref; cin>>pref;
        auto hasheo = T.search(pref);
        if(hasheo.first == -1)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << hasheo.second << " " << hasheo.first << endl;
        }
    }
 
    return 0;
} 