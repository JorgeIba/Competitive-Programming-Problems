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
    TrieNode* dictionary[2] = {NULL, NULL};
    lli howMuchLeafs = 0;
    bool isWord;
};

const lli maxLOG = 25;

struct Trie
{
    TrieNode *root = new TrieNode;
    bitset<maxLOG> flips;
    
    bool exist(TrieNode* curr, int c) {
        return curr->dictionary[c] != NULL;
    }

    void insert(const string s)
    {
        TrieNode *curr = root;
        for(auto ch: s)
        {
            int c = (ch == '0' ? 0 : 1);
            if(!exist(curr, c))
                curr->dictionary[c] = new TrieNode();
            curr = curr->dictionary[c];
            curr->howMuchLeafs++;
        }
        curr->isWord = true;
    }

    bool isComplete(TrieNode *curr, int height) {
        if(curr == NULL) return false;
        return curr->howMuchLeafs == (1LL << height);
    }

    void doXor(const string x_string) {
        for(int i = 0; i < maxLOG; i++) {
            int val_i = x_string[i] - '0';
            if(val_i)
                flips[i].flip();
        }
    }

    lli queryMex(TrieNode *curr, int height = maxLOG, int mex = 0, int idx_flip = 0){
        if(curr == NULL) return mex;

        TrieNode *l = curr->dictionary[0];
        TrieNode *r = curr->dictionary[1];

        if(flips[idx_flip]) {
            swap(l, r);
        }

        if(isComplete(l, height-1)) {
            return queryMex(r, height-1, mex + (1LL << (height-1)), idx_flip+1);
        } else {
            return queryMex(l, height-1, mex, idx_flip+1);
        }
    }

};




int main () {
	fastIO();
	

    
    lli n, q; cin>>n>>q;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    sort(all(nums));
    nums.erase(unique(all(nums)), nums.end());

    
    
    Trie *root = new Trie();
    for(auto x: nums) root->insert(bitset<maxLOG>(x).to_string());

    while(q--) {
        lli x; cin>>x;
        root->doXor(bitset<maxLOG>(x).to_string());
        cout << root->queryMex(root->root) << endl;
    }




	return 0;
}

