#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

const lli INF = 100000000000000LL;

struct Node
{
    lli maximum = 0;
    pair<lli, lli> pref = {-INF, 0};
    pair<lli, lli> suf = {-INF, 0};
};

vector<Node> nums;
vector<Node> ST;
lli n; 


Node Merge(Node a, Node b)
{
    Node ans;
    lli auxPref = -INF, auxSuf = -INF, auxSuma = -INF;
    if( a.pref.first == b.pref.first )
    {
        auxPref = a.pref.second + b.pref.second;
    }
    if( a.suf.first == b.suf.first )
    {
        auxSuf = a.suf.second + b.suf.second;
    }
    if( a.suf.first == b.pref.first )
    {
        auxSuma = a.suf.second + b.pref.second;
    }

    ans.maximum = max( auxSuma, max(a.maximum, b.maximum) );
    ans.pref.first = a.pref.first;
    ans.pref.second = max(auxPref, a.pref.second);
    ans.suf.first = b.suf.first;
    ans.suf.second = max(auxSuf, b.suf.second);

    return ans;
}

void build()
{
    for(lli i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(lli i = n-1; i>0; i--)
    {
        ST[i] = Merge( ST[i<<1], ST[i<<1|1] );
    }
}

void printNode(Node a)
{
    cout<<a.maximum<<" "<<a.pref.first<<" -> "<<a.pref.second<<" "<<a.suf.first<<" -> "<<a.suf.second<<endl;
}


Node query(lli l, lli r)
{
    Node MAX;
    for(l += n, r += n; l<=r; l>>=1, r>>=1)
    {
        if(l&1)
        {
            MAX = Merge(MAX, ST[l++]);
        }
        if(~r&1)
        {
            MAX = Merge(ST[r--], MAX);
        }
    }
    return MAX;

}

lli maxNode(Node a)
{
    return max( {a.maximum, a.pref.second, a.suf.second}  );
}


void solve(lli t)
{
    n = t;
    lli q; cin>>q;
    nums.resize(n);
    for(auto &x: nums)
    {
        cin>>x.suf.first;
        x.pref.first = x.suf.first;
        x.pref.second = x.suf.second = x.maximum= 1;
    }
    ST.resize(2*n);
    build();


    while(q--)
    {
        lli l, r; cin>>l>>r;
        cout<< maxNode(query(l-1, r-1)) <<endl;;
        //printNode(  query(l-1,r-1)   );
    }

    return;
}


int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    lli t;
    while(true)
    {
        cin>>t;
        if(t==0)
        {
            return 0;
        }
        ST.clear();
        nums.clear();
        solve(t);
    }

    return 0;
}
