#include <bits/stdc++.h>

#define lli long long int
#define li long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    li value;
    Node *izq, *der;
};

void extendIzq(Node *id)
{
    if(id->izq == NULL)
    {
        id->izq = new Node();
    }
}

void extendDer(Node *id)
{
    if(id->der == NULL)
    {
        id->der = new Node();
    }
}

void update(Node *id, int l, int r, int begin, int end, int value)
{
    if(end < l || r < begin) return;
    if(begin <= l && r <= end)
    {
        id->value = value;
    }
    else
    {
        assert(l!=r);
        int mid = l + ((r-l)>>1);
        if(begin <= mid)
        {
            extendIzq(id);
            update(id->izq, l, mid, begin, end, value );
        }
        else
        {
            extendDer(id);
            update(id->der, mid + 1, r, begin, end, value);
        }
        id->value = (id->izq != NULL? id->izq->value: 0) + (id->der != NULL? id->der->value: 0);
    }
}

lli query(Node *id, int l, int r, int begin, int end)
{
    if( end < l || r < begin) return 0;

    if(begin <= l && r<= end) 
    {
        return id->value;
    }
    else
    {
        assert(l!=r);
        lli res = 0;
        int mid = l + ((r-l)>>1);
        if(l<=mid)
        {
            //extendIzq(id);
            res += id->izq!=NULL?query(id->izq, l, mid, begin, end):0;
        }
        if(r>mid)
        {
            //extendDer(id);
            res += id->der!=NULL?query(id->der, mid+1, r, begin, end):0;
        }
        return res;
    }
}


int main()
{
    fastIO();
    lli P = 91, Q = 47, MOD = 1e9 + 7;
    li n, m; cin>>n>>m;
    Node *root = new Node();
    while(m--)
    {
        char t; cin>>t;
        li a, b; cin>>a>>b;
        a = (a + P);
        b = (b + Q);
        if(t == '!')
        {
            a %= n;
            b %= MOD;
            //debug2(a,b);
            if(b==0) continue;
            update(root, 0, n-1, a, a, b);
        }
        else
        {
            a %= n;
            b %= n;
            if(a > b) swap(a,b);
            //debug2(a,b);
            lli z = query(root, 0, n-1, a, b);
            cout<<z<<endl;
            P = ((P*31) + z)%MOD;
            Q = ((Q*29) + z)%MOD;
        }
    }

    return 0;
}