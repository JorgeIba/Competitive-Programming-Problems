#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    if( a.second <= b.second  )
    {
        return true;
    }
    else
    {
        return a.first <= b.first;
    }
    


}


int main()
{
    lli n; cin>>n;
    vector< pair<lli,lli> > numeros(n);


    for(auto &x: numeros)
    {
        cin>>x.first>>x.second;
    }

    sort(numeros.begin(), numeros.end(), compare);

    for(auto x: numeros)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }





    return 0;
}