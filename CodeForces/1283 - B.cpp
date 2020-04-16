#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli t; cin>>t;
    while(t--)
    {
        lli n, k; cin>>n>>k;
        lli res = n/k;
        lli mitad = k/2;
        //cout<<res<<" "<<mitad<<endl;
        res = res*k + mitad  ;
        res = min(res, n);
        cout<<res<<endl;
    }
    return 0;
}