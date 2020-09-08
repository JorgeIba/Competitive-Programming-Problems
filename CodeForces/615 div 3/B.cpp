#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector< pair<lli, lli> > puntos(n);
    for(int i=0; i<n; i++)
    {
        cin>>puntos[i].first>>puntos[i].second;
    }
    sort(puntos.begin(), puntos.end());
    string res = "";
    lli Xcor = 0, Ycor = 0;
    for(auto x: puntos)
    {
        if(x.first >= Xcor)
        {
            lli diff = x.first - Xcor ;
            while(diff--)
            {
                res= res + "R";
            }
            Xcor = x.first;
        }
        else
        {
            cout<<"NO\n";
            return;
        }
        if(x.second >= Ycor)
        {
            lli diff = x.second - Ycor ;
            while(diff--)
            {
                res= res + "U";
            }
            Ycor = x.second;
        }
        else
        {
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
    cout<<res<<endl;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}