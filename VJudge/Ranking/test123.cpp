#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cout<<1500<<endl;
    for(int i = 0; i<1500; i++)
    {
        lli aux = rand()%100000;
        lli signo = rand();
        if(signo%2)
        {
            aux = -1*aux;
        }
        cout<<aux<<" ";
    }

    return 0;
}