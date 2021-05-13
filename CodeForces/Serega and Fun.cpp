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

template<typename T=lli>
struct TreapNode{
	TreapNode<T> *left, *right;
	T value;
	int key, size;
    map<int, int> fr;

	//fields for queries
	bool rev;
	T sum, add;

	TreapNode(T value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL), sum(value), add(0), rev(false){ fr[value] = 1; }
};

typedef map<int,int> mp;

template<typename T=lli>
struct Treap{
	TreapNode<T> *root;

	Treap(): root(NULL) {}

	inline int nodeSize(TreapNode<T>* t){return t ? t->size: 0;}

    inline map<int,int> nodeSet(TreapNode<T> *t){return t? t->fr :map<int,int>(); }

    inline map<int,int> combine(int v, mp fr2, mp fr3)
    {
        if(fr2.size() < fr3.size()) swap(fr2, fr3);
        for(auto p: fr3) fr2[p.first] += p.second;
        fr2[v] += 1;
        return fr2;
    }

	inline void update(TreapNode<T>* &t){
		if(!t) return;
		t->size = 1 + nodeSize(t->left) + nodeSize(t->right);
        t->fr = combine(t->value, nodeSet(t->left), nodeSet(t->right));
	}

	int size(){return nodeSize(root);}



	void split2(TreapNode<T>* t, int i, TreapNode<T>* &t1, TreapNode<T>* &t2){
		if(!t)
			return void(t1 = t2 = NULL);
		int curr = nodeSize(t->left);
		if(i <= curr)
			split2(t->left, i, t1, t->left), t2 = t;
		else
			split2(t->right, i - curr - 1, t->right, t2), t1 = t;
		update(t);
	}

	inline int aleatorio(){
		return (rand() << 15) + rand();
	}

	void merge2(TreapNode<T>* &t, TreapNode<T>* t1, TreapNode<T>* t2){
		if(!t1) t = t2;
		else if(!t2) t = t1;
		else if(aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
			merge2(t1->right, t1->right, t2), t = t1;
		else
			merge2(t2->left, t1, t2->left), t = t2;
		update(t);
	}

	//insert the element "x" at position "i"
	void insert_at(T x, int i){
		if(i > nodeSize(root)) return;
		TreapNode<T> *t1 = NULL, *t2 = NULL;
		split2(root, i, t1, t2);
		merge2(root, t1, new TreapNode<T>(x));
		merge2(root, root, t2);
	}

    void rotate_update(int k, int l, int r){
		TreapNode<T> *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL;
		split2(root, l, t1, t2);
		split2(t2, r - l + 1, t2, t3);
		k %= nodeSize(t2);
		split2(t2, nodeSize(t2) - k, t2, t4);
		merge2(root, t1, t4);
		merge2(root, root, t2);
		merge2(root, root, t3);
	}

    lli getCount(int l, int r, int k)
    {
        TreapNode<T> *L=NULL, *MID=NULL, *R=NULL;
        split2(root, r, MID, R);
        split2(MID, l-1, L, MID);
        lli ans = MID->fr[k];
        root = NULL;
        merge2(root, L, MID);
        merge2(root, root, R);
        return ans;
    }

	void inorder(TreapNode<T>* t){
		if(!t) return;
		inorder(t->left);
		cout << t->value << " ";
		inorder(t->right);
	}

	void inorder(){inorder(root);}
};



int main () {
	fastIO();
	int n; cin>>n;
    Treap<lli> *T = new Treap<lli>();
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        T->insert_at(x, i);
    }
    int lastAns = 0;
    int q; cin>>q;
    while(q--)
    {
        int t, li, ri, l, r; cin>>t>>li>>ri;
        l = ((li + lastAns - 1)%n) + 1;
        r = ((ri + lastAns - 1)%n) + 1;
        if(l>r) swap(l,r);
        //cout << l << "----" << r << endl;
        if(t == 1)
        {    
            T->rotate_update(1, l-1, r-1);
            //T->inorder(); cout << endl;
        }
        else
        {
            int ki, k; cin>>ki;
            k = ((ki + lastAns - 1)%n)+1;
            lastAns = T->getCount(l, r, k);
            cout << lastAns << endl;
        }
        
    }

    /*
    while(true)
    {
        lli l, r, k; cin>>l>>r>>k;
        cout << T->getCount(l, r, k) << endl;
    }
    */


    
	return 0;
}