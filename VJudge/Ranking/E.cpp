#include <bits/stdc++.h>
#define lli long long

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, k; cin>>n>>k;
    vector< pair<lli,lli> > songs(n);

    for(auto &x: songs)
    {
        cin>>x.second>>x.first;
    }

    sort(songs.begin(), songs.end());

    lli l = n-1, r = n, res = -1, auxSuma=0;
    multiset<lli> current;
    set<lli> asd;
    while(l>=0)
    {
        auxSuma += songs[l].second;
        current.insert( songs[l].second  );
        if(current.size() > k)
        {
            auto itr = current.begin();
            auxSuma -= (*itr);
            current.erase(itr);
        }
        res = max( res,  auxSuma*songs[l].first);
        l--;
    }
    cout<<res<<endl;
    return 0;
}