#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n;
    cin>>n;
    if (n%2 == 0)
    {
        cout<<(n+4)<<" "<<4<<endl;
    }
    else
    {
        cout<<(n+9)<<" "<<9<<endl;
    }
    return 0;
}