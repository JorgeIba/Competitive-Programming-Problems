#include <bits/stdc++.h>
#define lli long long int 

using namespace std;

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    return (a.first - a.second) > (b.first - b.second);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector< pair<lli,lli> > pairs(n);
    for(auto &x: pairs)
    {
        cin>>x.first>>x.second;
    }
    sort(pairs.begin(), pairs.end(), compare);
    lli suma = 0;
    lli act = 0;
    for(int i = 0; i<n; i++)
    {
        if(act < pairs[i].first)
        {
            suma += (pairs[i].first  - act);
            act = pairs[i].first;
        }
        act -= pairs[i].second;
    }
    cout<<suma<<endl;


    return 0;
}