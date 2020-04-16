#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

const lli INF = 1000000000000LL;

struct Node
{
    lli total = 0, maximo = -INF, pref = -INF, suf = -INF;
};

vector<Node> ST;
vector<Node> nums;
lli n;

Node Merge(Node a, Node b)
{
    Node res;
    res.total = a.total + b.total;
    res.maximo = max( a.suf + b.pref, max(a.maximo, b.maximo)  );
    res.pref = max( a.pref, a.total + b.pref   );
    res.suf = max( b.suf, b.total + a.suf   );
    return res;

}

void build()
{
    for(lli i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(lli i = n-1; i>0; i--)
    {
        ST[i] = Merge(ST[i<<1], ST[i<<1|1]);
    }
}

void printNode(Node a)
{
    cout<<a.total<<" "<<a.maximo<<" "<<a.pref<<" "<<a.suf<<endl;
}

Node query(lli l, lli r)
{
    Node MAX1;
    Node MAX2;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        
        if(l&1)
        {
            //cout<<"l: ";
            MAX1 = Merge(MAX1, ST[l++]);
            //printNode(MAX1);
        }
        if(~r&1)
        {
            //cout<<"r: ";
            //printNode(ST[r]);
            MAX2 = Merge(ST[r--],MAX2);
            //printNode(MAX2);
        }
    }
    return Merge(MAX1, MAX2);
}

lli maxNode(Node a)
{
    return max({a.total, a.maximo, a.pref, a.suf});
}

void update(lli index, lli value)
{
    Node a;
    a.total = a.maximo = a.pref = a.suf = value;
    for(ST[index+=n] = a; index>1; index>>=1 )
    {
        if(index&1)
        {
            ST[index>>1] = Merge( ST[index^1], ST[index]);
        }
        else
        {
            ST[index>>1] = Merge( ST[index], ST[index^1]  );
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    nums.resize(n);
    for(auto &x: nums)
    {
        cin>>x.total;
        x.maximo = x.pref = x.suf = x.total;
    }
    //n = pow(2,ceil(log2(n)));
    //nums.resize(n);
    ST.resize(2*n);

    build();

    lli q; cin>>q;
    while(q--)
    {
        lli t; cin>>t;
        if(t==1)
        {
            lli l, r; cin>>l>>r;
            cout<<maxNode(( query(l-1, r-1) ))<<endl;
        }   
        else
        {
            lli index, value; cin>>index>>value;
            update(index-1, value);
        }
    }



    return 0;
}