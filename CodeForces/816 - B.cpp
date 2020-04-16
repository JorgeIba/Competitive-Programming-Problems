#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

lli n, k, q;

const lli MAX = 200010;

vector<lli> ST(2*MAX);
lli arreglo[MAX];

void build()
{
    for(int i = MAX; i<2*MAX; i++)
    {
        if(arreglo[i-MAX] >= k)
        {
            ST[i] = 1;    
        }
    }

    for(int i = MAX-1; i; i--)
    {
        ST[i] = ST[i<<1] + ST[i<<1|1];
    }
}

lli query(lli l, lli r)
{
    lli res = 0;
    for(l += MAX, r+=MAX; l<=r; l>>=1, r>>=1)
    {
        if(l&1)
        {
            res+=ST[l++];
        }
        if(~r&1)
        {
            res+=ST[r--];
        }
    }
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k>>q;
    memset(arreglo, 0, sizeof(arreglo));
    for(int i=0; i<n; i++)
    {
        lli l, r; cin>>l>>r;
        arreglo[l]++;
        arreglo[r+1]--;
    }
    lli aux = 0;
    for(int i=0; i<MAX; i++)
    {
        aux += arreglo[i];
        arreglo[i] = aux;
    }
    build();
    while(q--)
    {
        lli l, r;cin>>l>>r;
        cout<<query(l,r)<<endl;
    }

    return 0;
}