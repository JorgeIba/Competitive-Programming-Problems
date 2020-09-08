#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;

void solve()
{
    lli n;
    cin>>n;
    lli suma=0;
    lli sumaXOR=0;
    for(int i=0; i<n; i++)
    {
        lli x; cin>>x;
        suma+=x;
        sumaXOR^=x;
    }
    bool flag = false;
     
    if(suma == (2 * sumaXOR))
    {
        cout<<0<<endl<<endl;;
        return;
    }

    if(suma&1)
    {
        flag = true;
        suma+=1;
        sumaXOR^=1;
    }
   

    if(flag)
    {
        cout<<3<<endl;
        cout<<1<<" "<<sumaXOR<<" "<<(suma+sumaXOR)<<endl;
    }
    else
    {
        cout<<2<<endl;
        cout<<sumaXOR<<" "<<(suma+sumaXOR)<<endl;
    }



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