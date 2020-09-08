#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{   
    lli n; cin>>n;
    string x; cin>>x;
    string a(n,'1'), b(n,'1'); //a -> min
    bool flag = false;
    for(int i = 1; i<n; i++)
    {
        char c = x[i];
        if(!flag)
        {
            if(c=='2')
            {
                a[i] = b[i] = '1';
            }
            else if(c=='1')
            {
                a[i] = '1', b[i] = '0';
                flag = true;
            }
            else
            {
                a[i] = b[i] = '0';
            }
        }
        else
        {
            if(c=='2')
            {
                a[i] = '0', b[i] = '2';
            }
            else if(c=='1')
            {
                a[i] = '0', b[i] = '1';
            }
            else
            {
                a[i] = b[i] = '0';
            }
        }
    }
    cout<<a<<endl<<b<<endl;

}


int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}

