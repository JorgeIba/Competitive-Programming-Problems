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

mt19937 rr(20101010);

struct TreapNode{
	TreapNode *left, *right;
	int value;
	int key, size;

	//fields for queries
	bool rev;

	TreapNode(int value = 0): value(value), key(rr()), size(1), left(NULL), right(NULL), rev(false){}
};


TreapNode *root;

inline int nodeSize(TreapNode* t){return t ? t->size: 0;}

//OPERATIONS FOR IMPLICIT TREAP
inline void push(TreapNode* t){
    if(!t) return;
    if(t->rev){
        swap(t->left, t->right);
        if(t->left) t->left->rev ^= true;
        if(t->right) t->right->rev ^= true;
        t->rev = false;
    }
}

inline void update(TreapNode* &t){
    if(!t) return;
    t->size = 1 + nodeSize(t->left) + nodeSize(t->right);
    push(t->left), push(t->right); //push changes to child nodes
}

void split2(TreapNode* t, int i, TreapNode* &t1, TreapNode* &t2){
    if(!t)
        return void(t1 = t2 = NULL);
    push(t);
    int curr = nodeSize(t->left);
    if(i <= curr)
        split2(t->left, i, t1, t->left), t2 = t;
    else
        split2(t->right, i - curr - 1, t->right, t2), t1 = t;
    update(t);
}

inline int aleatorio(){
    return rr();
}

void merge2(TreapNode* &t, TreapNode* t1, TreapNode* t2){
    push(t1), push(t2);
    if(!t1) t = t2;
    else if(!t2) t = t1;
    else if(aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
        merge2(t1->right, t1->right, t2), t = t1;
    else
        merge2(t2->left, t1, t2->left), t = t2;
    update(t);
}

//insert the element "x" at position "i"
void insert_at(int x, int i){
    if(i > nodeSize(root)) return;
    TreapNode *t1 = NULL, *t2 = NULL;
    split2(root, i, t1, t2);
    merge2(root, t1, new TreapNode(x));
    merge2(root, root, t2);
}


//reverse [l, r]
void reverse_update(int l, int r){
    TreapNode *t1 = NULL, *t2 = NULL, *t3 = NULL;
    split2(root, l, t1, t2);
    split2(t2, r - l + 1, t2, t3);
    t2->rev ^= true;
    merge2(root, t1, t2);
    merge2(root, root, t3);
}

void inorder(TreapNode* t){
    if(!t) return;
    push(t);
    inorder(t->left);
    cout << t->value << " ";
    inorder(t->right);
}


 
int main () {
	fastIO();
    int n, m; cin>>n>>m;
    for(int i = 1; i<=n; i++)
    {
        insert_at(i, i-1);
    }
    while(m--)
    {
        int l, r; cin>>l>>r; l--, r--;
        reverse_update(l, r);
    }
    inorder(root);
    cout << endl;

	return 0;
}