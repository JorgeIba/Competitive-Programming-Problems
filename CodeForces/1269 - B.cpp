#include <bits/stdc++.h>
#define lli long long int

using namespace std;
    
vector<lli> a;
vector<lli> b;
set<lli> maybe;
lli n, m;

bool check(lli may)
{
    vector<lli> proposA = a;
    for(int i=0; i<n; i++)
    {
        proposA[i] = (proposA[i] +  may)%m;;
    }
    sort(proposA.begin(), proposA.end());
    for(int i=0; i<n; i++)
    {
        //cout<<proposA[i]<<" ";
        if (proposA[i] != b[i])
        {
            return false;
        }
    }

    return true;
}



int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    a.resize(n);
    b.resize(n);
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    for(int i=0; i<n; i++)
    {
        cin>>b[i];
    }

    sort(b.begin(), b.end());

    for(int i=0; i<n; i++)
    {
        lli may = b[0] - a[i];
        if( may < 0 )
        {
            may += m;
        }
        maybe.insert(may);
    }

    for(auto x: maybe)
    {
        //cout<<"Maybe: "<<x<<endl;
        if (check(x))
        {
            cout<<x<<endl;
            return 0;
        }
    }
    return 0;
}