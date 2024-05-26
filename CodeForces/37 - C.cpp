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
    int isWordChildren = 0;
    bool isWord = false;
};

struct Trie
{
    TrieNode *root = new TrieNode;
    
    bool exist(TrieNode* curr, int c) {
        return curr->dictionary[c] != NULL;
    }

    bool insert(TrieNode* curr, int x, string &ans) {
        if(curr->isWord || curr->isWordChildren == 2) return false;

        if(x == 0) {
            curr->isWord = true;
            return true;
        }

        for(int i = 0; i <= 1; i++) {
            if(!exist(curr, i)) 
                curr->dictionary[i] = new TrieNode();

            ans.push_back(i + '0');
            if( insert(curr->dictionary[i], x-1, ans) ){
                if(x == 1)
                    curr->isWordChildren++;
                return true;
            }
            ans.pop_back();
        }

        return false;
    }    
};



int main () {
	//fastIO();

    lli n; cin>>n;
    vector<pair<int,int>> nums(n);
    for(int i = 0; i < n; i++) {
        cin>>nums[i].first;
        nums[i].second = i;
    }

    sort(all(nums));

    Trie *root = new Trie();
    vector<string> ans(n);
    bool is_ans = true;
    for(auto [num, idx]: nums) {
        string ans_s;

        auto flag = root->insert(root->root, num, ans_s);

        is_ans = is_ans && flag;
        ans[idx] = ans_s;
    }

    if(!is_ans) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(auto s: ans) cout << s << endl;
    }


	return 0;
}

