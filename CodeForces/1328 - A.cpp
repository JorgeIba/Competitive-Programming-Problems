#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli t; cin>>t;
    while(t--)
    {
        lli a, b; cin>>a>>b;
        if(a % b == 0) 
        {
            cout<<0<<endl;
        }
        else
        {
            lli aux = a%b;
            cout<<  b-aux << endl;
        }
        
        
    }


}