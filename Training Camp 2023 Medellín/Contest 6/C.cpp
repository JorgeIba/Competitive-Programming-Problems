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



const int maxLOG = 30;
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

    int query(const string &q, const string &l) {
        // cout << q << endl << l << endl;
        int ans = 0;
        TrieNode* curr = root;
        for(int i = 0; i < maxLOG; i++) {
            int bit_q = (q[i] == '1' ? 1 : 0);
            int bit_l = (l[i] == '1' ? 1 : 0);

            auto left = curr->dict[0];
            auto right = curr->dict[1];

            // cout << bit_q << " " << bit_l << endl;
            // debugg(ans);

            if(!bit_q && bit_l){
                ans += (left ? left->howMuchWords : 0);

                if(!right) break;
                curr = right;
            } else if(bit_q && bit_l){
                ans += (right ? right->howMuchWords : 0);

                if(!left) break;
                curr = left;
            } else if(!bit_q && !bit_l) {

                if(!left) break;
                curr = left;
            } else{
                assert(bit_q && !bit_l);
                if(!right) break;
                curr = right;
            }
        }
        return ans;
    }
};


int main () {
	//fastIO();
	
	int q; cin>>q;


    Trie *T = new Trie();
    while(q--){
        int t; cin>>t;
        if(t == 1){
            int x; cin>>x;
            auto s = bitset<maxLOG>(x).to_string();
            // cout << s << endl;
            T->insert(s);
        } else if(t == 2){
            int x; cin>>x;
            auto s = bitset<maxLOG>(x).to_string();
            // cout << s << endl;
            T->remove(T->root, s);
        } else {   
            int p, l; cin>>p>>l;
            auto s_p = bitset<maxLOG>(p).to_string();
            auto s_l = bitset<maxLOG>(l).to_string();
            auto ans = T->query(s_p, s_l);
            cout << ans << endl;
        }

        // T->printWords();

    }


	return 0;
}

