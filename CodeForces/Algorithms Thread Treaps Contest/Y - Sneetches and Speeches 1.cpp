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
	bool toXor;
	pair<int,int> maxLeft, maxRight, maxMid;
	//int noZeros=0, noOnes=0, prefixZero=0, prefixOne=0, suffixZero=0, suffixOne = 0;

	TreapNode(T value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL), toXor(false) { maxLeft={1,value}; maxRight={1,value}; 
																														 maxMid={1,value}; }
};

typedef pair<int,int> pii;

template<typename T>
struct Treap{
	TreapNode<T> *root;

	Treap(): root(NULL) {}

	inline int nodeSize(TreapNode<T>* t){return t ? t->size: 0;}

	inline T nodeSum(TreapNode<T>* t){return t ? t->sum : 0;}

	inline T getMaxLeft(TreapNode<T> *t){return t? t->maxLeft.first: 0;} //rango, tipo
	inline T getMaxMid(TreapNode<T> *t){return t? t->maxMid.first: 0;}
	inline T getMaxRight(TreapNode<T> *t){return t? t->maxRight.first: 0;}
	inline pii getLeft(TreapNode<T> *t){return t? t->maxLeft: make_pair(-1, -1);}
	inline pii getMid(TreapNode<T> *t){return t? t->maxMid: make_pair(-1, -1);}
	inline pii getRight(TreapNode<T> *t){return t? t->maxRight: make_pair(-1, -1);}

	pii getMax(vector<pii> a)
	{
		int maximum = -1;
		for(auto p: a)
			maximum = max(maximum, p.first);
		for(auto p: a)
		{
			if(maximum == p.first) return p;
		}
	}

	void combineXor(TreapNode<T>* &t, TreapNode<T> *L, TreapNode<T> *R)
	{
		if(L) 
		{
			if(L->maxLeft.first == nodeSize(L) && L->maxLeft.second == t->value) //Si L es todo del mismo y ademas es igual que mi valor
			{
				t->maxLeft.first += nodeSize(L);
				t->maxMid = t->maxRight = t->maxLeft;
			}
			else
			{
				if(L->maxRight.second == t->value) //Si el lado derecho de L es igual que yo
				{
					t->maxRight.first += L->maxRight.first;
				}
				t->maxLeft = L->maxLeft;
			}
			t->maxMid = getMax({t->maxMid, L->maxMid, L->maxRight, t->maxLeft, t->maxRight}); //Saco el maximo entre todos
			t->size += nodeSize(L);
		}

		if(R)
		{
			if(R->maxRight.first == nodeSize(R) && R->maxRight.second == t->value) //Si el R es todo del mismo y ademas es igual que el valor
			{
				t->maxRight.first += nodeSize(R); //Si ya me combine antes, suma el tamaño de R a mi mejor sufijo
				if((t->maxLeft.first == nodeSize(t))) //Si todo yo soy de un solo valor
				{
					t->maxMid = t->maxLeft = t->maxRight;
				}
				t->maxMid = getMax({t->maxMid, t->maxRight});
			}
			else
			{
				if(t->value == R->maxLeft.second) // Si la parte izquierda de R es igual que la parte derecha de L+t (L posiblemente vacio)
				{
					lli aux = R->maxLeft.first + t->maxRight.first; //Uno el mejor sufijo de T con el mejor prefijo de R
					if((t->maxLeft.first == nodeSize(t)) ) //Si soy todo del mismo color entonces esa cosa es el mejor prefijo de t+R
					{
						t->maxLeft.first = aux;
					}
					t->maxMid = getMax({t->maxMid, {aux, t->value}});
				}
				t->maxRight = R->maxRight;
			}
			t->maxMid = getMax({t->maxMid, R->maxMid, R->maxLeft, R->maxRight, t->maxLeft, t->maxRight});
			t->size += nodeSize(R);
		}

		t->maxMid = getMax({t->maxLeft, t->maxMid, t->maxRight});
	}

	inline void update(TreapNode<T>* &t){
		if(!t) return;
		//t->sum = t->value; //reset node fields
		t->maxLeft = {1, t->value};
		t->maxMid = {1, t->value};
		t->maxRight = {1, t->value};
		t->size = 1;
		push(t->left), push(t->right); //push changes to child nodes
		combineXor(t, t->left, t->right);
	}

	int size(){return nodeSize(root);}

	//OPERATIONS FOR IMPLICIT TREAP
	inline void push(TreapNode<T>* t){
		if(!t) return;

		if(t->toXor)
		{
			t->value ^= 1;
			t->maxLeft.second ^= 1;
			t->maxRight.second  ^= 1;
			if(t->left) t->left->toXor ^= 1;
			if(t->right) t->right->toXor ^= 1;
			t->toXor = false;
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

    void insert_at(T x, int i){
		if(i > nodeSize(root)) return;
		TreapNode<T> *t1 = NULL, *t2 = NULL;
		split2(root, i, t1, t2);
		merge2(root, t1, new TreapNode<T>(x));
		merge2(root, root, t2);
	}

	void update_xor(int l, int r)
	{
		TreapNode<T> *L = NULL, *R = NULL, *MID = NULL;
		split2(root, r, L, R);
		split2(L, l-1, L, MID);
		MID->toXor ^= 1;
		merge2(root, L, MID);
		merge2(root, root, R);
	}

	int getMaxRange()
	{
		return max({root->maxLeft.first, root->maxMid.first, root->maxRight.first});
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
	int n, q; cin>>n>>q;
	string s; cin>>s;
	Treap<lli> *T = new Treap<lli>();
	for(int i = 0; i<n; i++)
	{
		if(s[i]=='0') T->insert_at(0, i);
		else T->insert_at(1, i);
	}
	
	while(q--)
	{
		int t, l, r; cin>>t>>l>>r;
		T->update_xor(l, r);
		cout << T->getMaxRange() << endl;
		//T->inorder(); cout << endl;
	}
	

	return 0;
}