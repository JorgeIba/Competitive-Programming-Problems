#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    lli key, size, priority;
    Node *l, *r;
    Node(lli key): key(key), priority(rand()), size(1), l(NULL), r(NULL) {}
};

int nodeSize(Node *T){ return (T ? T->size : 0); }

void update(Node *T)
{
    if(!T) return;
    T->size = 1 + nodeSize(T->r) + nodeSize(T->l);
}

pair<Node*,Node*> split(Node* T, lli x)
{
    if(!T)
    {
        return;
    }
    lli curr = nodeSize(T->l);
    if(x<=curr)
    {
        split(T->l, x, T1, T->l); T2 = T;
    }
    else
    {
        split(T->r, x - curr - 1, T->r, T2); T1 = T;
    }
    update(T);
}

Node* merge(Node* T, Node *T1, Node *T2)
{
    if(!T1) T = T2;
    else if(!T2) T = T1;
    else if (T1->priority > T2->priority)
    {
        merge(T1->r, T1->r, T2); T = T1;
    }
    else
    {
        merge(T2->l, T1, T2->l); T = T2;
    }
    update(T);
}

void insert(Node* &T, lli x)
{
    Node *TN = new Node(x);
    Node *T1=NULL, *T2=NULL;
    split(T, x, T1, T2);

    T = merge(T, T1, TN);
    T = merge(T, T, T2);
}


void inorder(Node *T)
{
    if(!T) return;
    inorder(T->l);
    cout<<T->key<<" ";
    inorder(T->r);
}


int main()
{
    //fastIO();
    lli n; cin>>n;
    Node *root = NULL;
    forn(i,0,n)
    {
        lli x; cin>>x;
        insert(root, x);
        inorder(root);
        cout<<endl;
    }
    cout<<root->size<<endl;

    return 0;
}