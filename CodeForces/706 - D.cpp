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
    int howMuch = 0;
    int howMuchEnds = 0;
};

const int LOG = 31;

struct Trie{
    TrieNode *root = new TrieNode;

    bool exist(TrieNode* curr, int c) {
        return curr->dictionary[c] != NULL;
    }

    void insert(int x)
    {
        TrieNode *curr = root;
        for(int i = LOG; i >= 0; i--){
            int c = ((1LL << i) & x) != 0;

            if(!exist(curr, c))
                curr->dictionary[c] = new TrieNode();

            curr = curr->dictionary[c];
            curr->howMuch++;
        }
        curr->howMuchEnds++;
    }

    int query(int x)
    {
        TrieNode *curr = root;
        lli ans = 0;
        for(int idx = LOG; idx >= 0; idx--){
            int c = ((1LL << idx) & x) != 0;

            if(c == 0) {
                if(exist(curr, 1)) {
                    ans |= (1LL << idx);
                    curr = curr->dictionary[1];
                } else {
                    curr = curr->dictionary[0];
                }
            } else {
                if(exist(curr, 0)) {
                    ans |= (1LL << idx);
                    curr = curr->dictionary[0];
                } else {
                    curr = curr->dictionary[1];
                }
            }
        }
        return ans;
    }

    void remove(int x) {
        TrieNode *curr = root;

        for(int i = LOG; i >= 0; i--){
            int c = ((1LL << i) & x) != 0;

            auto next = curr->dictionary[c];

            if(next->howMuch == 1) {
                curr->dictionary[c] = NULL;
            }

            next->howMuch--;
            curr = next;
        }


        return;
    }
};



int main () {
	fastIO();

    lli q; cin>>q;

    Trie *root = new Trie();

    root->insert(0);
    while(q--) {
        char t;
        lli x;
        cin>>t>>x;

        if(t == '+') {
            root->insert(x);
        } else if(t == '-') {
            root->remove(x);
        } else {
            lli ans = root->query(x);
            cout << ans << endl;
        }
    }



	return 0;
}

