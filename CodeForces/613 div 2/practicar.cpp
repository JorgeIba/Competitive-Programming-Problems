#include <bits/stdc++.h>
#define lli long long int
using namespce std;

int main()
{
    lli n;
    cin>>n;
    vector<lli> a(n);
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    lli atras = 0, best = 0;
    for(int i=0; i<n; i++)
    {
        atras = max(a[i], atras + a[i]);
        best = max(best, atras);
    }
    cout<<best<<endl;

    return 0;    
}