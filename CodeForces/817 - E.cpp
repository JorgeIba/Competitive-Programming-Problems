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

const int maxLOG = 31;

struct TrieNode{
    TrieNode *dict[2] = {NULL, NULL};
    int howMuchWords = 0;
    int isWord = 0;
};

struct Trie{
    TrieNode *root = new TrieNode;
    
    bool exist(TrieNode* curr, int c) {
        return curr->dict[c] != NULL;
    }

    // s = bitset.to_string
    void insert(const string &s){
        TrieNode *curr = root;
        curr->howMuchWords++;
        for(auto ch: s)
        {
            int c = (ch == '1');
            if(!exist(curr, c))
                curr->dict[c] = new TrieNode();
            curr = curr->dict[c];
            curr->howMuchWords++;
        }
        curr->isWord++;
    }
    
    // Assume word exists
    void remove(TrieNode* curr, const string &word, int idx = 0) {
        curr->howMuchWords--;

        if(idx == SZ(word)) {
            curr->isWord--;
            return;
        }


        auto c = (word[idx] == '1');
        auto next = curr->dict[c];
        remove(next, word, idx+1);

        if(!next->howMuchWords) {
            delete(next);
            next = NULL;
            curr->dict[c] = NULL;
        }
    }

    int query(const string xorX, const string lowerL) {
        int ans = 0;
        TrieNode* curr = root;
        for(int i = 0; i < maxLOG; i++) {
            int bit_l = (lowerL[i] == '1' ? 1 : 0);
            int bit_xor = (xorX[i] == '1' ? 1 : 0);


            if(bit_l) {
                auto left = curr->dict[0];
                auto right = curr->dict[1];

                if(bit_xor) swap(left, right);

                ans += (left ? left->howMuchWords : 0);

                if(!right) break;
                curr = right;
            }else {
                auto left = curr->dict[0];
                auto right = curr->dict[1];

                if(bit_xor) swap(left, right);

                if(!left) break;
                curr = left;
            }
        }
        return ans;
    }



    void Rec(TrieNode *root, const string &s){
        
        for(int c = 0; c <= 1; c++){
            if(!exist(root, c)) continue;

            string aux = s;
            auto ch = (c == 1? '1' : '0');
            aux.push_back(ch);

            assert(root->dict[c] != NULL);
            Rec(root->dict[c], aux);
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

    lli q; cin>>q;

    Trie *root = new Trie();

    while(q--) {
        int t; cin>>t;
        if(t == 1) {
            lli p; cin>>p;
            root->insert(bitset<maxLOG>(p).to_string());
        } else if(t == 2) {
            lli p; cin>>p;
            string aux = bitset<maxLOG>(p).to_string();
            root->remove(root->root, aux);
        } else {
            lli x, l; cin>>x>>l;
            bitset<maxLOG> x_bs(x), l_bs(l);

            lli ans = root->query(x_bs.to_string(), l_bs.to_string());
            cout << ans << endl;
        }


        // root->printWords();
    }


	return 0;
}
