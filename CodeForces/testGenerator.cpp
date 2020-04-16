#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{   
    cout<<2000<<" "<<1000000000<<endl;
    for(int i=0; i<2000; i++)
    {
        lli as = rand();
        as *= 100000;
        as %= 1000000000;
        cout<<as<<" ";
    }
    for(int i=2000; i<4001; i++)
    {
        int as = rand();
        as *= 100000;
        as %= 1000000000;
        cout<<as<<" ";
    }

    return 0;
}
