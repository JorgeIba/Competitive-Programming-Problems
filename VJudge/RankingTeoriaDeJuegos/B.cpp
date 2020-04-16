#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n, a, b; cin>>n>>a>>b;
    if((b-a)%2==0)
    {
        cout<<"Alice\n";
    }
    else
    {
        cout<<"Borys\n";
    }

    return 0;
}