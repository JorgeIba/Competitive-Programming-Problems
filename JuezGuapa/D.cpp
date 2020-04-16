#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    lli a,b; cin>>a>>b;
    lli res = 0;
    while(a>b)
    {
        if(a%2==0)
        {
            a/=2;
        }
        else
        {
            a++;
        }
        res++;
    }
    res += (b-a);
    cout<<res<<endl;



    return 0;
}