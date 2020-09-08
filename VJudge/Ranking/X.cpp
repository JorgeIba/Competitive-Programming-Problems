#include<bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    lli tablas[n+1][3]; //1 -> acumulado  , 2->productos

    memset(tablas, 0, sizeof(tablas));

    for(int i=0; i<n; i++)
    {
        cin>>tablas[i][0];
    }

    for(int i=n-1; i>=0; i--)
    {
        tablas[i][1] = tablas[i+1][1] + tablas[i][0];
    }

    for(int i=n-1; i>=0; i--)
    {
        tablas[i][2] = tablas[i][0]*tablas[i][1] + tablas[i+1][2];
    }
    /*
    for (int i = 0; i < n; i++)
    {
        cout<<tablas[i][2]<<" ";
    }
    */

   lli t; cin>>t;
   while(t--)
   {
        lli l,r; cin>>l>>r;
        lli res = (tablas[l][2]-tablas[r+1][2]) - tablas[r+1][1]*(  tablas[l][1] - tablas[r+1][1]      );
        cout<<res<<endl;
   }
    
    return 0;
}