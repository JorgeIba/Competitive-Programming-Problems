#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


template <typename T> struct TreapNode {
    T value;
    int key, size;
    TreapNode<T> *left, *right, *parent;


    TreapNode(T value = 0)
        : value(value), key(rand()), size(1), left(0), right(0), parent(0) {}
};

template <typename T> inline int nodeSize(TreapNode<T> *t) {
    return t ? t->size : 0;
}

template <typename T> void inorder(TreapNode<T> *t, vector<int> &ans) {
    if (!t)
        return;
    inorder(t->left, ans);
    ans.push_back(t->value);
    // cout << t->value << " ";
    inorder(t->right, ans);
}

template <typename T> inline void update(TreapNode<T> *&t) {
    if (!t)
        return;

    t->size = 1;

    if (t->left) {
        t->left->parent = t;
        t->size += nodeSize(t->left);
    }

    if (t->right) {
        t->right->parent = t;
        t->size += nodeSize(t->right);
    }
}

template <typename T> inline void push(TreapNode<T> *&t) {
    if (!t)
        return;
    if (t->left)
        t->left->parent = 0;
    if (t->right)
        t->right->parent = 0;
}

template <typename T>
void split(TreapNode<T> *t, int i, TreapNode<T> *&t1, TreapNode<T> *&t2) {
    if (!t)
        return void(t1 = t2 = NULL);
    push(t);

    int curr = nodeSize(t->left);

    if (i <= curr)
        split(t->left, i, t1, t->left), t2 = t;
    else
        split(t->right, i - curr - 1, t->right, t2), t1 = t;

    update(t1);
    update(t2);
    if (t1)
        t1->parent = 0;
    if (t2)
        t2->parent = 0;
}

inline int aleatorio() { return (rand() << 15) + rand(); }

template <typename T>
void merge(TreapNode<T> *&t, TreapNode<T> *t1, TreapNode<T> *t2) {
    if (!t1)
        t = t2;
    else if (!t2)
        t = t1;
    else if (aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
        merge(t1->right, t1->right, t2), t = t1;
    else
        merge(t2->left, t1, t2->left), t = t2;

    update(t);
};

template <typename T> pair<TreapNode<T> *, int> find_root(TreapNode<T> *t) {
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


using Node = TreapNode<int>;
const int MAXN = 2e5 + 100;
const int MAXQ = 2e5 + 100;
Node *root = NULL;


int main () {
	// fastIO();

    int n; cin>>n;
    
    vector< Node* > x_to_root(MAXN + MAXQ);

    map<int,int> mapp;
    map<int,int> return_mapp;
    auto mapping = [&](int x) {
        if(!mapp.count(x)) {
            mapp[x] = SZ(mapp);
            return_mapp[mapp[x]] = x;
        }
        return mapp[x];
    };
    
    forn(i, n) {
        int x; cin>>x;
        x = mapping(x);
        Node *node = new Node(x);
        x_to_root[x] = node;
        merge(root, root, node);
    }

    int q; cin>>q;
    while(q--) {
        int t; cin>>t;
        if(t == 1) {
            int x, y; cin>>x>>y;
            x = mapping(x);
            y = mapping(y);

            auto [root, pos] = find_root(x_to_root[x]);
            Node *left = NULL, *right = NULL;
            split(root, pos+1, left, right);

            Node *node = new Node(y);
            x_to_root[y] = node;
            merge(root, left, node);
            merge(root, root, right);
            ::root = root;
        } else {
            int x; cin>>x;
            x = mapping(x);

            auto [root, pos] = find_root(x_to_root[x]);
            Node *left = NULL, *middle = NULL, *right = NULL;

            split(root, pos, left, right);
            split(right, 1, middle, right);

            merge(root, left, right);
            ::root = root;
        }
    }


    vector<int> ans;
    inorder(root, ans);
    for(auto x: ans) {
        cout << return_mapp[x] << " ";
    }
    cout << endl;




	return 0;
}

