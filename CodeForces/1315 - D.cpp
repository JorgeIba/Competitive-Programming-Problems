#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

set<lli> past;
vector< pair<lli,lli> > pubs;

int main()
{
    lli n; cin>>n;
    vector<lli> auxArri(n);
    vector<lli> auxAb(n);
    pubs.resize(n);

    for(auto &x: auxArri)
    {
        cin>>x;
    }
    for(auto &x: auxAb)
    {
        cin>>x;
    }
    for(int i=0; i<n; i++)
    {
        pubs[i].first = auxArri[i];
        pubs[i].second = auxAb[i];
        past.insert(auxArri[i]);
    }
    sort(pubs.begin(), pubs.end());




}