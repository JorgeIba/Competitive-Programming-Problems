#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n; cin>>n;
    vector<lli> a(n);
    vector<lli> b(n);
    for(int i = 0; i<n; i++)
        cin>>a[i];
    for(int i = 0; i<n; i++)
        cin>>b[i];

    map<lli,lli> idx;

    for(int i = 0; i<n; i++ )
    {
        idx[ b[i]  ] = i;
    }

    map<lli,lli> frequency;
    for(int i =0; i<n; i++)
    {
        lli num = a[i];
        lli getidx = idx[num];
        if(getidx > i)
        {
            frequency[ i +  (n - getidx  ) ]++;
        }
        else
        {
            frequency[ i - getidx ]++;
        }
        
    }
    lli res = -1;
    for(auto x: frequency)
    {
        res = max(res, x.second);
        //cout<<x.first<<" "<<x.second<<endl;
    }
    cout<<res<<endl;

    return 0;
}