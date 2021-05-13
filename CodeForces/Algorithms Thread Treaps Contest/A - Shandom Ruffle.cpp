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

template<typename T>
struct TreapNode{
	TreapNode<T> *left, *right;
	T value;
	int key, size;

	//fields for queries
	bool rev;
	T sum, add;

	TreapNode(T value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL), sum(value), add(0), rev(false){}
};

template<typename T>
struct Treap{
	TreapNode<T> *root;

	Treap(): root(NULL) {}

	inline int nodeSize(TreapNode<T>* t){return t ? t->size: 0;}

	inline T nodeSum(TreapNode<T>* t){return t ? t->sum : 0;}

	inline void update(TreapNode<T>* &t){
		if(!t) return;
		t->size = 1 + nodeSize(t->left) + nodeSize(t->right);
		t->sum = t->value; //reset node fields
		push(t->left), push(t->right); //push changes to child nodes
		t->sum = t->value + nodeSum(t->left) + nodeSum(t->right); //combine(left,t,t), combine(t,right,t)
	}

	int size(){return nodeSize(root);}



	//OPERATIONS FOR IMPLICIT TREAP
	inline void push(TreapNode<T>* t){
		if(!t) return;
		//add in range example
		if(t->add){
			t->value += t->add;
			t->sum += t->add * nodeSize(t);
			if(t->left) t->left->add += t->add;
			if(t->right) t->right->add += t->add;
			t->add = 0;
		}
		//reverse range example
		if(t->rev){
			swap(t->left, t->right);
			if(t->left) t->left->rev ^= true;
			if(t->right) t->right->rev ^= true;
			t->rev = false;
		}
	}

	void split2(TreapNode<T>* t, int i, TreapNode<T>* &t1, TreapNode<T>* &t2){
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
		return (rand() << 15) + rand();
	}

	void merge2(TreapNode<T>* &t, TreapNode<T>* t1, TreapNode<T>* t2){
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
	void insert_at(T x, int i){
		if(i > nodeSize(root)) return;
		TreapNode<T> *t1 = NULL, *t2 = NULL;
		split2(root, i, t1, t2);
		merge2(root, t1, new TreapNode<T>(x));
		merge2(root, root, t2);
	}

	void doChange(int l1, int r1, int l2, int r2) // L1 S1 R1 S2 R2
	{
		TreapNode<T> *L1=NULL, *R1=NULL, *segment1=NULL, *segment2=NULL, *mid = NULL;
		split2(root, r2, L1, R1); // L1 L1 L1 L1 R1
		//cout << nodeSize(root) << " " << nodeSize(L1) << " " << nodeSize(R1) << endl;
		split2(L1, l2-1, L1, segment2); // R2 R2 R2 segment2 R1
		split2(L1, r1, L1, mid);
		split2(L1, l1-1, L1, segment1); //L2 L2 segment1 Segment2 R2 R2
		//inorder(L1); cout << endl; inorder(segment1);
		root = NULL;
		merge2(root, L1, segment2);
		merge2(root, root, mid);
		merge2(root, root, segment1);
		merge2(root, root, R1);
		//inorder(root);
	}

	void inorder(TreapNode<T>* t){
		if(!t) return;
		push(t);
		inorder(t->left);
		cout << t->value << " ";
		inorder(t->right);
	}

	void inorder(){inorder(root);}
};





int main () {
	fastIO();
	lli n; cin>>n;
	Treap<lli> *T = new Treap<lli>();
	for(int i = 1; i<=n; i++)
	{
		T->insert_at(i, i-1);
	}
	for(int i = 0; i<n; i++)
	{
		int l, r; cin>>l>>r; 
		if(l >= r) continue;
		int size1 = r - l - 1, size2 = n - r;
		size1 = min(size1, size2);
		//cerr << l << "---" << l+size1 << " " << r << "---" << r+size1 << endl;
		T->doChange(l, l+size1, r, r + size1);
		//cout << T->size() << endl;
		//T->inorder(); cout << endl;
	}

	T->inorder();


    
	return 0;
}