#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cout << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


template<typename T>
struct TreapNode{
	T value;
	int key, size;
    TreapNode<T> *left, *right, *parent;
    
	//fields for queries
	T left_v, right_v, best_left, best_right;
    T best;

	TreapNode(T value = 0): value(value), key(rand()), size(1), left(0), right(0), parent(0), left_v(value), right_v(value), best_left(1), best_right(1), best(1) {}
};


template<typename T>
inline int nodeSize (TreapNode<T>* t) { return t ? t->size : 0; }

template<typename T>
void inorder(TreapNode<T>* t){
    if(!t) return;
    inorder(t->left);
    cout << t->value << " ";
    inorder(t->right);
}

template<typename T>
inline void merge_nodes(TreapNode<T>* &parent, TreapNode<T>* left, TreapNode<T>* right) {

    int left_v = left->left_v;
    int best_left = left->best_left;
    int right_v = right->right_v;
    int best_right = right->best_right;
    int best = max(left->best, right->best);
    int sizee = left->size + right->size;
    
    if(left->right_v == right->left_v) {
        best = max(best, left->best_right + right->best_left);
        
        bool right_full = (right->best_left == right->size);
        bool left_full  = (left->best_right == left->size);

        if(left_full && right_full) {
            assert(left_v == right_v);
            best_left = left->size + right->size;
            best_right = left->size + right->size;
        } else if(left_full && !right_full) {
            best_left = left->size + right->best_left;
        } else if(!left_full && right_full){
            best_right = left->best_right + right->size;
        }
    }

    parent->size = sizee;
    parent->left_v = left_v;
    parent->best_left = best_left;
    parent->best = best;
    parent->right_v = right_v;
    parent->best_right = best_right;    

    // DO NOT TOUCH VALUE parent->value because for Reset
}

template<typename T>  
inline void update(TreapNode<T>* &t){
    if(!t) return;

    // Reset
    t->size = 1;
    t->best_left = t->best = t->best_right = 1;
    t->left_v = t->right_v = t->value;

    if(t->left) {
        t->left->parent = t;
        merge_nodes(t, t->left, t);
    }

    if(t->right) {
        t->right->parent = t;
        merge_nodes(t, t, t->right);
    }
}

template<typename T>
inline void push (TreapNode<T>* &t) {
	if (!t) return;
	if (t->left) t->left->parent = 0;
	if (t->right) t->right->parent = 0;
}
 
template<typename T>
void split (TreapNode<T>* t, int i, TreapNode<T>* &t1, TreapNode<T>* &t2) {
	if (!t) return void(t1 = t2 = NULL);
	push(t);
 
	int curr = nodeSize(t->left);
 
	if (i <= curr)
		split(t->left, i, t1, t->left), t2 = t;
	else
		split(t->right, i - curr - 1, t->right, t2), t1 = t;
 
	update(t1);
	update(t2);
	if (t1) t1->parent = 0;
	if (t2) t2->parent = 0;
}
 
inline int aleatorio() {
	return (rand() << 15) + rand();
}
 
template<typename T>
void merge (TreapNode<T>* &t, TreapNode<T>* t1, TreapNode<T>* t2) {
	if (!t1) t = t2;
	else if (!t2) t = t1;
	else if (aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
		merge(t1->right, t1->right, t2), t = t1;
	else
		merge(t2->left, t1, t2->left), t = t2;
 
	update(t);
};
 
template<typename T>
pair<TreapNode<T>*, int> find_root (TreapNode<T> *t) {
	int izq = nodeSize(t->left);
	while (t->parent) {
		TreapNode<T> *ant = t;
		t = t->parent;
		if (ant == t->right) {
			izq += nodeSize(t->left) + 1;
		}
	}
	return {t, izq};
}


typedef TreapNode<int> Node;


int main () {
	fastIO();
	
    int n, q; cin>>n>>q;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector< Node* > node_treaps(n + q);

    Node *root = NULL;

    for(int i = 0; i < n; i++) {
        auto node = new Node(nums[i]);
        node_treaps[i] = node;
        merge(root, root, node);
    }

    auto get_ans = [&](Node* &root_t){
        if(root_t->left_v != root_t->right_v) return root_t->best;
        if(root_t->best_left == root_t->size) return root_t->best;


        return max(root_t->best_left + root_t->best_right, root_t->best);
    };

    multiset<int> anss;
    anss.insert(get_ans(root));

    forn(test, q){
        int t, d; cin>>t>>d;

        auto node = new Node(d);
        node_treaps[n + test] = node;


        if(t == 1) {
            int a, b; cin>>a>>b; a--, b--;

            auto [parent_a, idx_a] = find_root(node_treaps[a]);
            auto [parent_b, idx_b] = find_root(node_treaps[b]);

            assert(parent_a == parent_b);

            if(idx_a > idx_b) {
                swap(a, b);
                swap(idx_a, idx_b);
            }        

            int old_ans = get_ans(parent_a);
                
            if(idx_a == 0 && idx_b == nodeSize(parent_a)-1) {
                merge(parent_a, parent_a, node);
            } else {
                assert(idx_a == idx_b-1);

                Node *left = NULL, *right = NULL;

                split(parent_a, idx_a+1, left, right);

                merge(parent_a, left, node);
                merge(parent_a, parent_a, right);
            }

            int new_ans = get_ans(parent_a);

            anss.extract(old_ans);
            anss.insert(new_ans);
        } else {

            int a; cin>>a; a--;

            auto node_a = node_treaps[a];
            auto [parent, idx_a] = find_root(node_a);

            int old_ans = get_ans(parent);

            if(idx_a == nodeSize(parent) - 1) {
                split(parent, idx_a, parent, node_a);

                merge(node_a, node_a, node);
            } else {
                Node *left = NULL, *middle = NULL, *right = NULL;

                split(parent, idx_a, left, right);
                split(right, 1, middle, right);

                merge(parent, left, right);
                merge(node_a, middle, node);
            }

            int new_ans_a = get_ans( node_a  );
            int new_ans_prev = get_ans( parent );

    
            anss.extract(old_ans);
            anss.insert(new_ans_a);
            anss.insert(new_ans_prev);
        }


        auto root_d = find_root(node_treaps[n+test]).first;
        cout << get_ans(root_d) << " ";
        cout << *anss.rbegin() << endl;
    }


	return 0;
}

