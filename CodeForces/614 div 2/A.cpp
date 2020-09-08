#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n,d; cin>>n>>d;
    for(int i=0; i<d; i++)
    {
        double I = i, D = d;
        
        cout<<(I + ceil(D/(I+1)))<<" ";
    }
    cout<<endl;
}


int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}