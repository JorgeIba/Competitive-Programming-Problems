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

lli p = 37, MOD = 1e9+9;

vector<lli> powsP(1e6, 1);

void precPows()
{
    for(int i = 1; i<1e6; i++)
        powsP[i] = (powsP[i-1]*p)%MOD;
}



template<typename T>
struct TreapNode{
	TreapNode<T> *left=NULL, *right=NULL;
	T value;
	int key, size;

	//fields for queries
	T Hash, revHash;

	TreapNode(T value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL), Hash(value*p), revHash(value*p){}
};

template<typename T>
struct Treap{
	TreapNode<T> *root;

	Treap(): root(NULL) {}

	inline int nodeSize(TreapNode<T>* t){return t ? t->size: 0;}

    inline T getHash(TreapNode<T>* t){return t ? t->Hash : 0;}
    inline T getRevHash(TreapNode<T>* t){return t ? t->revHash : 0;}

    inline pair<lli,lli> combineHashing(lli value, TreapNode<T>* &L, TreapNode<T>* &R)
    {
        lli sizeL = nodeSize(L), sizeR = nodeSize(R);
        lli Hash = getHash(L), revHash = getRevHash(R);
        assert((sizeL + 1 < 1e6) && (sizeR + 1 < 1e6));
        assert(value > 0);
        Hash = (Hash + ((value*powsP[sizeL+1])%MOD) + ((getHash(R)*powsP[sizeL+1])%MOD) )%MOD;
        revHash = (revHash + ((value*powsP[sizeR+1])%MOD) + ((getRevHash(L)*powsP[sizeR+1])%MOD) )%MOD;
        return {Hash, revHash};
    }

	inline void update(TreapNode<T>* &t){
		if(!t) return;
		t->size = 1 + nodeSize(t->left) + nodeSize(t->right);
        tie(t->Hash, t->revHash) = combineHashing(t->value, t->left, t->right);
        
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

    void erase_range(int l, int r)
    {
        TreapNode<T> *L = NULL, *R = NULL, *MID = NULL;
        split2(root, r, L, R);
        split2(L, l-1, L, MID); MID = NULL;
        merge2(root, L, R);
    }

    /*
    void test(int l, int r)
    {
        TreapNode<T> *L = NULL, *R = NULL, *Segment = NULL;
        split2(root, r, L, R);
        split2(L, l-1, L, Segment);
        inorder(Segment); cout << endl;
        cout << Segment->Hash << " " << Segment->revHash << endl;
        merge2(root, L, Segment);
        merge2(root, root, R);
    }
    */

    bool isPalindromo(int l, int r)
    {
        int size = r - l + 1;
        if(~size & 1)
        {
            bool ans = false;
            TreapNode<T> *L = NULL, *R = NULL, *Segment = NULL;
            split2(root, r, L, R);
            split2(L, l-1, L, Segment);

            assert(size == nodeSize(Segment));
            TreapNode<T> *Left = NULL, *Right = NULL;
            split2(Segment, size/2, Left, Right);

            //cout << "Comparando: "; inorder(Left); cout << " y "; inorder(Right); cout << endl;

            if(getHash(Left) == getRevHash(Right)) ans = true;
            merge2(Segment, Left, Right);
            
            merge2(root, L, Segment);
            merge2(root, root, R);
            return ans;
        }
        else
        {
            bool ans = false;
            TreapNode<T> *L = NULL, *R = NULL, *Segment = NULL;
            split2(root, r, L, R);
            split2(L, l-1, L, Segment);

            assert(size == nodeSize(Segment));
            TreapNode<T> *Left = NULL, *Right = NULL, *Mid = NULL;

            split2(Segment, size/2 + 1, Left, Right);
            split2(Left, size/2, Left, Mid);

            //cout << "Comparando: "; inorder(Left); cout << " y "; inorder(Right); cout << "En medio "; inorder(Mid); cout << endl;

            if(getHash(Left) == getRevHash(Right)) ans = true;

            merge2(Segment, Left, Mid);
            merge2(Segment, Segment, Right);
            
            merge2(root, L, Segment);
            merge2(root, root, R);
            return ans;
        }
        
    }

	void inorder(TreapNode<T>* t){
		if(!t) return;
		inorder(t->left);
		cerr << t->value << " ";
		inorder(t->right);
	}

	void inorder(){inorder(root);}
};



int main () {
	fastIO();
    precPows();
    int n, q; cin>>n>>q;
    string s; cin>>s;
    Treap<lli> *T = new Treap<lli>();

    for(int i = 0; i<n; i++)
    {
        T->insert_at((int)s[i], i);
    }
    T->inorder(); cerr << endl << endl;
    for(int i = 0; i<q; i++)
    {
        int t; cin>>t;
        if(t == 1)
        {
            int l, r; cin>>l>>r;
            T->erase_range(l, r);
        }
        else if(t == 2)
        {
            char c; int p; cin>>c>>p; p--;
            T->insert_at((int)c, p);
        }
        else
        {
            int l, r; cin>>l>>r;
            if(T->isPalindromo(l, r))
            {
                cout << "yes\n";
            }
            else
            {
                cout << "no\n";
            }
        }
        T->inorder(); cerr << endl << endl;
    }

    
	return 0;
}