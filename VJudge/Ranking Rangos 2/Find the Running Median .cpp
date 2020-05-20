#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


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

	void merge(TreapNode<T>* &t, TreapNode<T>* t1, TreapNode<T>* t2){
		if(!t1) t = t2;
		else if(!t2) t = t1;
		else if(t1->key > t2->key)
			merge(t1->right, t1->right, t2), t = t1;
		else
			merge(t2->left, t1, t2->left), t = t2;
		update(t);
	}

	void split(TreapNode<T>* t, T & x, TreapNode<T>* &t1, TreapNode<T>* &t2){
		if(!t)
			return void(t1 = t2 = NULL);
		if(x < t->value)
			split(t->left, x, t1, t->left), t2 = t;
		else
			split(t->right, x, t->right, t2), t1 = t;
		update(t);
	}

	void insert(TreapNode<T>* &t, TreapNode<T>* x){
		if(!t) t = x;
		else if(x->key > t->key)
			split(t, x->value, x->left, x->right), t = x;
		else
			insert(x->value < t->value ? t->left : t->right, x);
		update(t);
	}

	TreapNode<T>* search(T & x){
		TreapNode<T> *t = root;
		while(t){
			if(x == t->value) break;
			t = (x < t->value ? t->left : t->right);
		}
		return t;
	}

	void erase(TreapNode<T>* &t, T & x){
		if(!t) return;
		if(t->value == x)
			merge(t, t->left, t->right);
		else
			erase(x < t->value ? t->left : t->right, x);
		update(t);
	}

	void insert(T & x){insert(root, new TreapNode<T>(x));}

	void erase(T & x){erase(root, x);}

	void updateVal(T & old, T & New){
		if(search(old))
			erase(old), insert(New);
	}

	T kth(int i){
		assert(0 <= i && i < nodeSize(root));
		TreapNode<T> *t = root;
		while(i != nodeSize(t->left)){
			if(i < nodeSize(t->left)){
				t = t->left;
			}else{
				i -= nodeSize(t->left) + 1;
				t = t->right;
			}
		}
		return t->value;
	}

	int lessThan(T & x){
		int ans = 0;
		TreapNode<T> *t = root;
		while(t){
			if(x > t->value){
				ans += nodeSize(t->left) + 1;
				t = t->right;
			}else{
				t = t->left;
			}
		}
		return ans;
	}

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
	void insert_at(T & x, int i){
		if(i > nodeSize(root)) return;
		TreapNode<T> *t1 = NULL, *t2 = NULL;
		split2(root, i, t1, t2);
		merge2(root, t1, new TreapNode<T>(x));
		merge2(root, root, t2);
	}

	//delete element at position "i"
	void erase_at(int i){
		if(i >= nodeSize(root)) return;
		TreapNode<T> *t1 = NULL, *t2 = NULL, *t3 = NULL;
		split2(root, i, t1, t2);
		split2(t2, 1, t2, t3);
		merge2(root, t1, t3);
	}

	void update_at(TreapNode<T>* t, T & x, int i){
		push(t);
		assert(0 <= i && i < nodeSize(t));
		int curr = nodeSize(t->left);
		if(i == curr)
			t->value = x;
		else if(i < curr)
			update_at(t->left, x, i);
		else
			update_at(t->right, x, i - curr - 1);
		update(t);
	}

	T nth(TreapNode<T>* t, int i){
		push(t);
		assert(0 <= i && i < nodeSize(t));
		int curr = nodeSize(t->left);
		if(i == curr)
			return t->value;
		else if(i < curr)
			return nth(t->left, i);
		else
			return nth(t->right, i - curr - 1);
	}

	//update value of element at position "i" with "x"
	void update_at(T & x, int i){update_at(root, x, i);}

	//ith element
	T nth(int i){return nth(root, i);}

	//add "val" in [l, r]
	void add_update(T & val, int l, int r){
		TreapNode<T> *t1 = NULL, *t2 = NULL, *t3 = NULL;
		split2(root, l, t1, t2);
		split2(t2, r - l + 1, t2, t3);
		t2->add += val;
		merge2(root, t1, t2);
		merge2(root, root, t3);
	}

	//reverse [l, r]
	void reverse_update(int l, int r){
		TreapNode<T> *t1 = NULL, *t2 = NULL, *t3 = NULL;
		split2(root, l, t1, t2);
		split2(t2, r - l + 1, t2, t3);
		t2->rev ^= true;
		merge2(root, t1, t2);
		merge2(root, root, t3);
	}

	//rotate [l, r] k times to the right
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

	//sum query in [l, r]
	T sum_query(int l, int r){
		TreapNode<T> *t1 = NULL, *t2 = NULL, *t3 = NULL;
		split2(root, l, t1, t2);
		split2(t2, r - l + 1, t2, t3);
		T ans = nodeSum(t2);
		merge2(root, t1, t2);
		merge2(root, root, t3);
		return ans;
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

int main()
{
    fastIO();
    lli n; cin>>n;
    Treap<lli> *T = new Treap<lli>();
    forn(i,0,n)
    {
        lli x; cin>>x;
        T->insert(x);
        if(~i&1)
        {
            lli mid = T->root->size / 2;
            //cout<<T->root->size<<" "<<mid<<endl;
            cout<<T->kth(mid)<<".0\n";
        }
        else
        {
            lli mid = T->root->size / 2;
            double res = double(T->kth(mid) + T->kth(mid-1))/2;
            cout<<fixed<<setprecision(1)<<res<<endl;
        }
    }
}