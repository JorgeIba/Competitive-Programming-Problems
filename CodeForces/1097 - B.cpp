#include <bits/stdc++.h>
#define lli long long int

using namespace std;
vector<lli> rotaciones;
lli n; 

lli funcion(lli indice, lli suma)
{
    if( indice == n )
    {
        if(suma%360 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    lli pos = funcion(indice + 1, suma+rotaciones[indice]);
    lli neg = funcion(indice + 1, suma-rotaciones[indice]);
    
    return max(pos, neg);
}



int main()
{
    cin>>n;
    rotaciones.resize(n);
    for(auto &x: rotaciones)
    {
        cin>>x;
    }
    lli res = funcion(0,0);
    //cout<<res<<endl;
    if(res)
    {
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
    }

    return 0;
}