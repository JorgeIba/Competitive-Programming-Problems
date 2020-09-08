#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    return a.first*b.second < b.first*a.second;
}


int main()
{
    lli x, y; cin>>x>>y;
    pair<lli,lli> inicio(x,y);
    
    lli n; cin>>n;
    vector< pair< pair<lli,lli>, lli> > p(n);
    for(auto &x: p)
    {
        cin>>x.first.first>>x.first.second>>x.second;
    }

    vector< pair<lli,lli> > distances(n); // fir = d, sec = v
    for(int i = 0; i<n; i++)
    {
        distances[i].first = (inicio.first - p[i].first.first)*(inicio.first - p[i].first.first) + (inicio.second - p[i].first.second)*(inicio.second - p[i].first.second);
        distances[i].second = p[i].second*p[i].second;
    }
    
    sort(distances.begin(), distances.end(), compare);
    pair<double,double> res;
    res.first = sqrt(distances[0].first);
    res.second = sqrt(distances[0].second);
    cout<<fixed<< setprecision(7) <<  (res.first / res.second)<<endl;


    return 0;
}