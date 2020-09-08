#include <bits/stdc++.h>
#define lli long long int

using namespace std;

pair<lli,lli> diff(pair<lli,lli> a, pair<lli,lli> b)
{
    return {a.first - b.first, a.second - b.second};
}


lli cross(pair<lli,lli> a, pair<lli,lli> b)
{
    return a.first*b.second - a.second*b.first;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector< pair<lli,lli> > points(n);
    lli contx = 0, conty = 0;
    for(int i = 0; i< n; i++)
    {
        lli u,d; cin>>u>>d;
        points[i].first = contx + u;
        contx += d + u;
        points[i].second = conty + u;
        conty += -d + u;
    }
    /*
    for(auto x: points)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }*/

    vector< vector<lli> > res(n);
    for(int i = n-1; i>=1; i--)
    {
        pair<lli,lli> current = diff(points[i-1], points[i]);
        for(int j = i-1; j>=0; j--)
        {
            pair<lli,lli> possible = diff(points[j], points[i]);
            //cout<<cross(current, possible)<<" ";
            if( cross(current, possible) <= 0)
            {
                res[i].push_back(j+1);
                current = possible;
            }
        }
        //res[i].push_back(i);
    }
    for(auto x: res)
    {
        cout<<x.size()<<" ";
        sort(x.begin(), x.end());
        for(auto i: x)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }


    

    

    return 0;
}