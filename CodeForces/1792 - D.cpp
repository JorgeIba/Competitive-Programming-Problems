#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

struct TrieNode{
    map<char, TrieNode*> dictionary;
    int isWord = 0;
};

struct Trie{
    TrieNode *root = new TrieNode;
    
    bool exist(TrieNode* curr, char c) {
        return curr->dictionary.count(c);
    }

    void insert(const string &s){
        TrieNode *curr = root;
        for(auto c: s)
        {
            if(!exist(curr, c))
                curr->dictionary[c] = new TrieNode();
            curr = curr->dictionary[c];
        }
        curr->isWord++;
    }

    lli search(const string &word){
        TrieNode *curr = root;
        int ans = 0;
        for(auto c: word){
            if(!exist(curr, c)){
                break;
            }
            curr = curr->dictionary[c];
            ans++;
        }
        return ans;
    }
};



void main_(){
    int n, m; cin>>n>>m;

    vector< vector<int> > perms(n, vector<int>(m));
    for(auto &perm: perms) {
        for(auto &x: perm) {
            cin>>x;
            x--;
        }
    }

    auto transform = [&](const vector<int> &perm) {
        string trans;
        for(int d = 0; d <= m-1; d++){
            for(int i = 0; i < m; i++){
                if(perm[i] != d) continue;

                trans.push_back(i + '0');
            }
        }
        return trans;
    };


    Trie *T = new Trie();

    for(auto &perm: perms) {
        // cout << transform(perm) << endl;
        T->insert(transform(perm));
    }



    vector<int> answers;
    for(auto &perm: perms) {
        vector<int> looking(m);
        for(int j = 0; j <= m-1; j++) {
            looking[ perm[j] ] = j;
        }
        answers.push_back(  T->search(transform(looking))    );
    }

    for(auto x: answers) cout << x << " ";
    cout << endl;

}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

