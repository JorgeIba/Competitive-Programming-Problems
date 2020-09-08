#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

map< pair<lli,lli> , lli > idx;
vector< pair<lli,string> > ans;

bool fun(vector< pair<lli,lli> > domino, lli last)
{
    if(domino.size() == 0) 
    {
        return true;
    }

    for(int i = 0; i<domino.size(); i++)
    {
        vector<pair<lli,lli>> aux = domino;
        lli x = domino[i].first;
        lli y = domino[i].second;

        if(x == last || y == last)
        {
            aux.erase( aux.begin() + i);
            if(x == last)
            {
                if(fun(aux, y))
                {
                    //cout<<idx[{x,y}]<<" a"<<endl;
                    lli indx = idx[{x,y}];
                    ans.push_back({indx, "b"});
                    return true;
                }
            }
            if(y == last)
            {
                if(fun(aux, x))
                {
                    lli indx = idx[{x,y}];
                    ans.push_back({indx, "a"});
                    return true;
                }
            }
        }
    }
    return false;

}



int main()
{
    fastIO();
    lli n; cin>>n;
    vector< pair<lli,lli> > domino(n);
    for(int i = 0; i<n; i++)
    {
        lli x, y; cin>>x>>y;
        domino[i].first = x;
        domino[i].second = y;
        idx[{x,y}] = i+1;
    }

    for(int i = 0; i<n; i++)
    {
        vector<pair<lli,lli>> aux = domino;
        lli x = domino[i].first, y = domino[i].second;
        aux.erase( aux.begin() + i );
        
        if(fun(aux, x))
        {
            lli indx = idx[{x,y}];
            ans.push_back({indx, "a"});
            break;
        }
        if(fun(aux, y))
        {
            lli indx = idx[{x,y}];
            ans.push_back({indx, "b"});
            break;
        }
    }

    for(auto x: ans)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }

    return 0;
}